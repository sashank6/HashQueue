#include <iostream>
#include "HashQueue.hpp"

using namespace std;

int main() {

    HashQueue<double> hq;
    hq.push(0.9);
    hq.push(1.5);
    hq.push(2.5);
    hq.push(3.5);
    hq.push(7.5);
    hq.push(3.5);
    hq.push(8.5);
    hq.push(9.5);

    hq.display_list();
    std::cout << "Top of the Queue: "<<hq.top() << std::endl;
    std::cout << "Occurrences of 3.5: " << hq.get_count(3.5) << std::endl;
    std::cout << "Occurrences of 4.5: "<< hq.get_count(4.5) << std::endl;
    std::cout << "Elements in the Queue: "<<std::endl;
    hq.display_list();
    std::vector<double> v = hq.get_all_elements(3.5);

    std::cout<<"Nodes whose data element is 3.5: "<<std::endl;
    for(int i=0;i<v.size();i++)
      std::cout<<v[i]<<std::endl;



    return 0;
}