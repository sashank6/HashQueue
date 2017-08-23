

#ifndef EXEC_HASHQUEUE_H
#define EXEC_HASHQUEUE_H

#include <iostream>
#include <vector>
#include<functional>
#include "Node.hpp"
#include "hashqueue_exceptions.hpp"

/*TODO:
 * 1. Catching Segmentation fault and throwing informative exception to the user.
 * 2. Performance optimization for get_all_elements* functions.
 * 3. Figure out pointer memory allocation  and use inbuilt function to reset memory
*/


template<class T, class Compare = std::equal_to<T>, class Hash = std::hash<T> >
class HashQueue {

private:
    unsigned long num_buckets;
    long bucket_size;
    Node<T> *hash_queue_heads[100];
    Node<T> *hash_queue_tails[100];
    Node<T> *list_head;
    Node<T> *list_tail;
    unsigned long int length;

    Node<T> *create_node(const T element);

    void push_to_queue(const T element);

    void push_to_list(Node<T> *&node);

    void push_to_hash_queue(Node<T> *&node, size_t bucket_index);

    void free_node(Node<T> *node);

    void update_head_next();

    void update_tail_prev();

    bool is_last_node();

    unsigned long int get_bucket_index(const T element);

    size_t get_count(const T element, Node<T> *bucket_head);

    std::vector<T> get_all_elements(const T element, size_t bucket_index);


public:
    HashQueue(unsigned long num_buckets = 100, long bucket_size = -1);

    void push(const T element);

    T top();

    void pop();

    bool is_empty();

    //Only for debugging
    void display_list();

    unsigned long int size();

    std::vector<T> get_all_elements();

    unsigned long int get_count(const T element);

    bool has_key(const T element);

    std::vector<T> get_all_elements(const T element);


};

template<class T, class Compare, class Hash>
Node<T> *HashQueue<T, Compare, Hash>::create_node(const T data) {
    Node<T> *node = new Node<T>(data);
    return node;
}

template<class T, class Compare, class Hash>
void HashQueue<T, Compare, Hash>::push_to_list(Node<T> *&node) {

    if (!node) {
        throw new InvalidPushException();
    }

    if (!(this->list_head)) {
        this->list_head = node;
        this->list_tail = node;
        return;
    }
    node->prev = this->list_tail;
    this->list_tail->next = node;
    this->list_tail = node;
}

template<class T, class Compare, class Hash>
void HashQueue<T, Compare, Hash>::push_to_hash_queue(Node<T> *&node, size_t bucket_index) {

    std::cout<<this->hash_queue_heads[bucket_index]<<std::endl;
    if (!node) {
        throw new InvalidPushException();
    }

    if (!(this->hash_queue_heads[bucket_index])) {
        this->hash_queue_heads[bucket_index] = node;
        this->hash_queue_tails[bucket_index] = node;
        return;
    }
    node->prev_hash = this->hash_queue_tails[bucket_index];
    this->hash_queue_tails[bucket_index]->next_hash = node;
    this->hash_queue_tails[bucket_index] = node;

}


template<class T, class Compare, class Hash>
void HashQueue<T, Compare, Hash>::push_to_queue(const T element) {
    Node<T> *node = create_node(element);
    push_to_list(node);
    size_t bucket_index = get_bucket_index(element);
    push_to_hash_queue(node, bucket_index);
}

template<class T, class Compare, class Hash>
bool HashQueue<T, Compare, Hash>::is_empty() {
    return !(this->list_head);
}

template<class T, class Compare, class Hash>
void HashQueue<T, Compare, Hash>::free_node(Node<T> *node) {
    delete node;
}

template<class T, class Compare, class Hash>
void HashQueue<T, Compare, Hash>::update_head_next() {
    if (is_empty()) {
        return;
    }
    Node<T> *next_head = this->list_head->next;
    free_node(this->list_head);
    this->list_head = next_head;
}

template<class T, class Compare, class Hash>
void HashQueue<T, Compare, Hash>::update_tail_prev() {
    if (is_empty()) {
        this->list_tail = 0;
        return;
    }
    Node<T> *prev_node = this->list_tail->prev;
    free_node(this->list_tail);
    this->list_tail = prev_node;
}

template<class T, class Compare, class Hash>
bool HashQueue<T, Compare, Hash>::is_last_node() {
    if (is_empty()) {
        return false;
    }
    return (this->list_head->next == 0);
}

template<class T, class Compare, class Hash>
unsigned long int HashQueue<T, Compare, Hash>::get_bucket_index(const T element) {
    std::hash<T> pdf;
    size_t hash_value = pdf(element);
    return (hash_value % this->num_buckets);
}

template<class T, class Compare, class Hash>
size_t HashQueue<T, Compare, Hash>::get_count(const T element, Node<T> *bucket_head) {

    size_t count = 0;
    Node<T> *bucket_node = bucket_head;
    while (bucket_node) {
        count += Compare()(bucket_node->data, element);
        bucket_node = bucket_node->next_hash;
    }
    return count;
}

/*
 * Used for fetching elements similar to specified element in a specific bucket.
 */
template<class T, class Compare, class Hash>
std::vector<T> HashQueue<T, Compare, Hash> :: get_all_elements(const T element, size_t bucket_index) {

    Node<T> *bucket_node = this->hash_queue_heads[bucket_index];
    std::cout<<bucket_node<<std::endl;
    std::cout<<bucket_node->data<<std::endl;
    std::cout<<bucket_node->next_hash->data<<std::endl;
    std::vector<T> all_elements;
    while(bucket_node) {
        if (Compare()(bucket_node->data, element)) {
            all_elements.push_back(bucket_node->data);
        }
        bucket_node = bucket_node->next_hash;
    }
    return all_elements;
};

//TODO: Pointer memory allocation
template<class T, class Compare, class Hash>
HashQueue<T, Compare, Hash>::HashQueue(unsigned long num_buckets, long bucket_size) {
    this->bucket_size = bucket_size;
    this->num_buckets = num_buckets;
    Node<T> *p[this->num_buckets];
    for(int i = 0;i<this->num_buckets;i++) {
        this->hash_queue_heads[i] = 0;
        this->hash_queue_tails[i] = 0;
    }

    this->list_head = 0;
    this->list_tail = 0;
    this->length = 0;
}

template<class T, class Compare, class Hash>
void HashQueue<T, Compare, Hash>::push(const T element) {

    this->length++;
    push_to_queue(element);
}

template<class T, class Compare, class Hash>
void HashQueue<T, Compare, Hash>::display_list() {

    if (is_empty()) {
        return;
    }
    Node<T> *t = this->list_head;
    while (t != 0) {
        std::cout << t->data << " ";
        t = t->next;
    }
    std::cout << std::endl;
}

template<class T, class Compare, class Hash>
T HashQueue<T, Compare, Hash>::top() {
    if (is_empty()) {
        throw QueueEmptyException();
    }
    return this->list_head->data;
}

template<class T, class Compare, class Hash>
void HashQueue<T, Compare, Hash>::pop() {
    if (is_empty()) {
        throw QueueEmptyException();
    }

    if (is_last_node()) {
        update_head_next();
        update_tail_prev();
    } else {
        update_head_next();
    }
    this->length--;
}

template<class T, class Compare, class Hash>
unsigned long HashQueue<T, Compare, Hash>::size() {
    return this->length;
}

//TODO: Performance improvement to be done.
template<class T, class Compare, class Hash>
std::vector<T> HashQueue<T, Compare, Hash>::get_all_elements() {
    std::vector<T> all_elements;
    Node<T> *temp_node = this->list_head;
    while (temp_node != 0) {
        all_elements.push_back(temp_node->data);
        temp_node = temp_node->next;
    }

    return all_elements;
}

template<class T, class Compare, class Hash>
unsigned long int HashQueue<T, Compare, Hash>::get_count(const T element) {
    unsigned long int bucket_index = get_bucket_index(element);
    return get_count(element, this->hash_queue_heads[bucket_index]);
}

template<class T, class Compare, class Hash>
bool HashQueue<T, Compare, Hash>::has_key(T element) {

  return get_count(element) > 0;
}

/*
 * Fetch all the elements that are equal when compared with specified element
 */

template<class T, class Compare, class Hash>
std::vector<T> HashQueue<T,Compare, Hash>::get_all_elements(const T element) {
    size_t bucket_index = get_bucket_index(element);
    std::cout<<bucket_index<<std::endl;
    return get_all_elements(element, bucket_index);
}

#endif //EXEC_HASHQUEUE_H
