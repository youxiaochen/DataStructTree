//
// Created by 77991 on 2020/7/26.
//

#ifndef DATASTRUCTTREE_COMPARABLE_HPP
#define DATASTRUCTTREE_COMPARABLE_HPP

template <class E>
struct Comparable {

    constexpr int operator()(const E &left, const E &right) const {
        if (left > right) return 1;
        if (left < right) return -1;
        return 0;
    }

};

#endif //DATASTRUCTTREE_COMPARABLE_HPP
