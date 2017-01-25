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

    std::set<int> new_set = dry1_algo<std::vector<int>::iterator, int,
            std::vector<int>,LessThan>(vec.begin(), vec.end());
    return 0;
}