//
//
//
#include<exception>
#ifndef EXEC_EXCEPTIONS_H
#define EXEC_EXCEPTIONS_H

struct QueueEmptyException:public std::exception {
    const char* what() const throw() {
        return "Queue is Empty";
    }

};

struct InvalidPushException:public std::exception {
    const char* what() const throw() {
        return "Cannot push null memory bad_alloc";
    }

};

#endif //EXEC_EXCEPTIONS_H
