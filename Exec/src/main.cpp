#include <iostream>
#include "HashQueue.hpp"
using namespace std;

int main() {

    HashQueue<int> hq;
    hq.push(1);
    hq.push(2);
    hq.push(3);
    hq.display_list();
    std::cout<<hq.top()<<std::endl;
    hq.display_list();
    hq.pop();
    hq.display_list();
    while(!hq.is_empty()) {
        hq.pop();
    }


    hq.display_list();


    return 0;
}