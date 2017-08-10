//
// Created by Sashank Alladi on 8/10/17.
//

#ifndef EXEC_HASHQUEUE_H
#define EXEC_HASHQUEUE_H
#include "Node.h"

template <class T>
class HashQueue {

private:
    unsigned long num_buckets;
    unsigned long bucket_size;
    Node **hash_queue_heads;
    Node **hash_queue_tails;


public:
    HashQueue(unsigned long num_buckets = 100, unsigned long bucket_size = -1);
    void push(T element);

};


#endif //EXEC_HASHQUEUE_H
