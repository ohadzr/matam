//
// Created by ohad on 24-Jan-17.
//

#ifndef MATAM_DRY2_H
#define MATAM_DRY2_H

#include <iostream>
using namespace std;



class A {
public:
    virtual void print() const {
        cout << "a" << endl;
    }
    virtual void print() {
        cout << "c" << endl;
    }
};

class B : public A{
public:
    void print() const {
        cout << "b" << endl;
    }
};

void f(A& a) {
    a.print();
}


#endif //MATAM_DRY2_H
