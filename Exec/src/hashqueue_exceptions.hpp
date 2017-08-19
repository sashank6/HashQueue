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

#endif //EXEC_EXCEPTIONS_H
