#include <iostream>
#include "HashQueue.hpp"


int main() {

    HashQueue<int> hq(100,-1);
    hq.push(1);
    hq.display_list();
    return 0;
}