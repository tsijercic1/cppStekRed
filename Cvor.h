//
// Created by tsijercic1 on 1/29/2019.
//

#ifndef STEKREDCPP_CVOR_H
#define STEKREDCPP_CVOR_H


template <typename tip>
struct Cvor {
    tip element;
    Cvor<tip> *next;
};


#endif //STEKREDCPP_CVOR_H
