//
// Created by Sashank Alladi on 8/10/17.
//

#ifndef EXEC_NODE_H
#define EXEC_NODE_H



template <class T>
struct Node {
    T data;
    Node *prev;
    Node *next;
    Node *next_hash;
    Node(T data):data(data),prev(0),next(0),next_hash(0){}
};
#endif //EXEC_NODE_H