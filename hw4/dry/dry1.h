//
// Created by ohad on 25-Jan-17.
//

#ifndef MATAM_DRY1_H
#define MATAM_DRY1_H


#include <iostream>
#include <set>
#include <vector>





template <class iterator, typename stream_type, typename generic_stream ,typename obj_operator>
std::set<stream_type> dry1_algo (iterator begin, iterator end){
    std::set<stream_type> collection_set = std::set<stream_type>();

    iterator it = begin;
    int index = 0;
    for (;  it != end; it++) {
        generic_stream left(begin ,begin + index);
        generic_stream right(begin + index, end);
        if (obj_operator()(left,right))
            collection_set.insert(*it);
        index++;
    }

    return collection_set;
}



class LessThan {
public:
    LessThan() {}
    bool operator()(std::vector<int> m, std::vector<int> n) const {
        return m.size() >= n.size();
    }
};

#endif //MATAM_DRY1_H
