//
// Created by ohad on 25-Jan-17.
//

#ifndef MATAM_DRY1_H
#define MATAM_DRY1_H


#include <iostream>
#include <set>
#include <vector>


template <class iterator, typename stream_type ,typename obj_operator>
std::set<stream_type> dry1_algorithem (iterator begin, iterator end){
    std::set<stream_type> collection_set = std::set<stream_type>();

    iterator it = begin;
    int index = 0;
    for (;  it != end; it++) {
        if (obj_operator()(begin, begin+index, begin+index,end))
            collection_set.insert(*it);
        index++;
    }

    return collection_set;
}


class HighBeforeMe {
public:
    HighBeforeMe() {}
    bool operator()(std::vector<int>::iterator left_begin,
                    std::vector<int>::iterator left_end,
                    std::vector<int>::iterator right_begin,
                    std::vector<int>::iterator right_end) const {
        std::vector<int>::iterator it = left_begin;
        for ( ; it != left_end; it ++){
            if (*it > *right_begin)
                return true;
        }
        return false;
    }
};

#endif //MATAM_DRY1_H
