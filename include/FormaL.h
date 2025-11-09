/*
    În fișierul FormaL.h definesc o formă de tip L
*/

#ifndef CANDY_FORMAL_H
#define CANDY_FORMAL_H

#include "Punct.h"
#include "config.h"

//clasa FormaL
class FormaL {
    Punct start;
    bool orizontal;// true- linia e sus, false- linia e jos
    bool vertical;//true- linia e la stânga, false- linia e la dreapta
    int culoare;

public:
    FormaL();//constructor
    FormaL(bool orizontal, bool vertical, Punct start, int culoare = 0);//inițializare
    ~FormaL() {}//destructor

    //vectorul static din forme L
    static FormaL forme_de_l[50];
    static int diml;


    static void sterge_toate_L();
    void gasesteL(Punct intersectie, int indice_or, int indice_ve);
    void inlocuiesteL(int a[][DIM], int indice);

    //clasă prietenă pentru a accesa variabile și metode
    friend class Linie;
};

#endif // CANDY_FORMAL_H