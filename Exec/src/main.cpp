#include <iostream>
#include "HashQueue.hpp"

using namespace std;

int main() {

    HashQueue<double> hq;
    hq.push(1.5);
    hq.push(2.5);
    hq.push(3.5);
    hq.push(7.5);
    hq.push(3.5);
    hq.push(8.5);
    hq.push(9.5);

    hq.display_list();
    std::cout << hq.top() << std::endl;
    std::cout << hq.get_count(3.5) << std::endl;
    std::cout << hq.get_count(4.5) << std::endl;
    hq.display_list();
    hq.pop();
    hq.display_list();
    while (!hq.is_empty()) {
        hq.pop();
    }


    hq.display_list();


    return 0;
}