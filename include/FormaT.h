/*
    În fișierul FormaT.h definesc formele de tip T
*/


#ifndef CANDY_FORMAT_H
#define CANDY_FORMAT_H

#include "Punct.h"
#include "config.h"

//clasa de forme T
class FormaT {
    Punct start;
    bool baza;
    bool varf;
    int culoare;

public:
    FormaT();//constructor
    FormaT(bool baza, bool varf, Punct start, int culoare = 0);
    ~FormaT() {}//destructor

    //declar vectorul static de forme T
    static FormaT forme_de_t[50];
    static int dimt;

    static void sterge_toate_T();
    void gasesteT(Punct intersectie, int indice_or, int indice_ve);
    void inlocuiesteT(int a[][DIM], int indice);

    friend class Linie;
};

#endif // CANDY_FORMAT_H