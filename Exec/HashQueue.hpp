

#ifndef EXEC_HASHQUEUE_H
#define EXEC_HASHQUEUE_H
#include "Node.hpp"

template <class T>
class HashQueue {

private:
    unsigned long num_buckets;
    unsigned long bucket_size;
    Node<T> **hash_queue_heads;
    Node<T> **hash_queue_tails;
    Node<T> *list_head;
    Node<T> *list_tail;

    unsigned long get_bucket(T element);
    Node<T> *create_node(T element);
    void push_to_list(T element);


public:
    HashQueue(unsigned long num_buckets = 100, long bucket_size = -1);
    void push(T element);
    T top();
    void pop();
    bool is_empty();
    //Only for debugging
    void display_list();

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
HashQueue<T>::HashQueue(unsigned long num_buckets, long bucket_size) {
    this->bucket_size = bucket_size;
    this->num_buckets = num_buckets;
    this->hash_queue_heads = new Node<T> *[this->num_buckets];
    this->hash_queue_tails = new Node<T> *[this->num_buckets];
    memset(hash_queue_heads, 0, this->num_buckets);
    memset(hash_queue_tails, 0, this->num_buckets);
    this->list_head = 0;
    this->list_tail = 0;
}

template<class T>
void HashQueue<T>::push(T element) {

    push_to_list(element);
}

template<class T>
void HashQueue<T>::display_list() {

    Node<T> *t = this->list_head;
    while (t != 0) {
        std::cout << t->data << " ";
        t = t->next;
    }
}

template<class T>
T HashQueue<T>::top() {
    if (is_empty()) {
        //throw Exception;
    }
    return this->list_head->data;
}

template<class T>
void HashQueue<T>::pop() {
    if (is_empty()) {
        //throw Exception
    }
}
#endif //EXEC_HASHQUEUE_H
