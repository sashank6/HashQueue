

#ifndef EXEC_HASHQUEUE_H
#define EXEC_HASHQUEUE_H

#include <iostream>
#include <vector>
#include "Node.hpp"
#include "hashqueue_exceptions.hpp"

template <class T>
class HashQueue {

private:
    unsigned long num_buckets;
    unsigned long bucket_size;
    Node<T> **hash_queue_heads;
    Node<T> **hash_queue_tails;
    Node<T> *list_head;
    Node<T> *list_tail;
    unsigned long int length;

    unsigned long get_bucket(T element);
    Node<T> *create_node(T element);
    void push_to_list(T element);
    void free_node(Node<T> *node);
    void update_head_next();
    void update_tail_prev();
    bool is_last_node();



public:
    HashQueue(unsigned long num_buckets = 100, long bucket_size = -1);
    void push(T element);
    T top();
    void pop();
    bool is_empty();
    //Only for debugging
    void display_list();
    unsigned long int size();
    std::vector<T> get_all_elements();

};

template<class T>
Node<T>* HashQueue<T>::create_node(T data) {
    Node<T> *node = new Node<T>(data);
    return node;
}

template<class T>
void HashQueue<T>::push_to_list(T element) {
    Node<T> *node = create_node(element);
    if(!(this->list_head)) {
        this->list_head = node;
        this->list_tail = node;
        return;
    }
    node->prev = this->list_tail;
    this->list_tail->next = node;
    this->list_tail = node;
}

template<class T>
bool HashQueue<T>::is_empty() {
    return !(this->list_head);
}

template<class T>
void HashQueue<T>::free_node(Node<T> *node) {
    delete node;
}

template<class T>
void HashQueue<T>::update_head_next() {
    if(is_empty()) {
        return;
    }
    Node<T> *next_head = this->list_head->next;
    free_node(this->list_head);
    this->list_head = next_head;
}

template<class T>
void HashQueue<T>::update_tail_prev() {
    if(is_empty()) {
        this->list_tail = 0;
        return;
    }
    Node<T> *prev_node = this->list_tail->prev;
    free_node(this->list_tail);
    this->list_tail = prev_node;
}

template<class T>
bool HashQueue<T>::is_last_node() {
    if(is_empty()) {
        return false;
    }
    return (this->list_head->next == 0);
}



template<class T>
HashQueue<T>::HashQueue(unsigned long num_buckets, long bucket_size) {
    this->bucket_size = bucket_size;
    this->num_buckets = num_buckets;
    this->hash_queue_heads = new Node<T> *[this->num_buckets];
    this->hash_queue_tails = new Node<T> *[this->num_buckets];
    memset(hash_queue_heads, 0, this->num_buckets);
    memset(hash_queue_tails, 0, this->num_buckets);
    this->list_head = 0;
    this->list_tail = 0;
    this->length = 0;
}

template<class T>
void HashQueue<T>::push(T element) {

    this->length++;
    push_to_list(element);
}

template<class T>
void HashQueue<T>::display_list() {

    if(is_empty()) {
        return;
    }
    Node<T> *t = this->list_head;
    while (t != 0) {
        std::cout << t->data << " ";
        t = t->next;
    }
    std::cout<<std::endl;
}

template<class T>
T HashQueue<T>::top() {
    if (is_empty()) {
        throw QueueEmptyException();
    }
    return this->list_head->data;
}

template<class T>
void HashQueue<T>::pop() {
    if (is_empty()) {
        throw QueueEmptyException();
    }

    if(is_last_node()) {
        update_head_next();
        update_tail_prev();
    } else {
        update_head_next();
    }
    this->length--;
}

template<class T>
unsigned long HashQueue<T>::size() {
    return this->length;
}

template<class T>
std::vector<T> HashQueue<T>::get_all_elements() {
    std::cout<<this->length<<std::endl;
    std::vector<T> all_elements;
    Node<T> *temp_node = this->list_head;
    while(temp_node != 0) {
        all_elements.push_back(temp_node->data);
        temp_node = temp_node->next;
    }

    return all_elements;
}
#endif //EXEC_HASHQUEUE_H
