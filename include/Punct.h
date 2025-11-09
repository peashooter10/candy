/*
    În Punct.h îmi creez baza pentru memorarea datelor
*/

#ifndef CANDY_PUNCT_H
#define CANDY_PUNCT_H

//clasa Punct memorează coordonatele unui punct din matrice
class Punct {
    int x,y;

public:
    Punct(int x = 0, int y = 0);//constructor
    ~Punct() {}//destructor

    //metode getter cu care iau valorile dintr-un Punct
    int getX() const;
    int getY() const;

    void afiseaza() const;//afișez un punct
};

#endif // CANDY_PUNCT_H