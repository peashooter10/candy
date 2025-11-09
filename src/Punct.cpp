#include "../include/Punct.h"
#include <iostream>
using namespace std;

Punct::Punct(int x, int y) : x(x), y(y) {}//inițializez punctul

//iau valorile din Punct
int Punct::getX() const {
    return x;
}
int Punct::getY() const {
    return y;
}

void Punct::afiseaza() const {
    cout << "(" << x << ", " << y << ")";
}
