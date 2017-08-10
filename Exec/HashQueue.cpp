//
// Created by Sashank Alladi on 8/10/17.
//

#include <cstring>
#include "HashQueue.h"
#include "Node.h"

template<class T>
HashQueue<T>::HashQueue(unsigned long num_buckets, unsigned long bucket_size) {
    this->bucket_size = bucket_size;
    this->num_buckets = num_buckets;
    hash_queue_heads = new Node *[bucket_size];
    hash_queue_tails = new Node *[bucket_size];
    memset(hash_queue_heads, 0, 100);
    memset(hash_queue_tails, 0, 100);
}