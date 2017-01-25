//
// Created by ohad on 25-Jan-17.
//

#include "dry1.h"




int main() {
    std::vector<int> vec = std::vector<int>();
    vec.push_back(7);
    vec.push_back(2);
    vec.push_back(4);
    vec.push_back(8);
    vec.push_back(7);
    vec.push_back(6);
    vec.push_back(10);
    vec.push_back(9);

    std::vector<int> vec_sorted = std::vector<int>();
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(2);
    vec.push_back(4);
    vec.push_back(6);
    vec.push_back(6);
    vec.push_back(15);
    vec.push_back(15);

    std::set<int> new_set = dry1_algorithem<std::vector<int>::iterator, int,
            HighBeforeMe>(vec.begin(), vec.end());

    if (vec.size() == 0)
        std::cout << "first vector is sorted" << std::endl;
    else
        std::cout << "first vector is NOT sorted" << std::endl;


    if (vec_sorted.size() == 0)
        std::cout << "second vector is sorted" << std::endl;
    else
        std::cout << "second vector is NOT sorted" << std::endl;

    return 0;
}