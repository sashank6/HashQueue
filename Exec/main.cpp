#include <iostream>
#include "HashQueue.hpp"


int main() {

    HashQueue<int> hq;
    hq.push(1);
    hq.push(2);
    hq.push(3);
    hq.display_list();
    return 0;
}