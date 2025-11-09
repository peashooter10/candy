/*
    În fișierul Linie.h declar liniile orizontale și verticale
    După ce le găsesc le memorez
    Acestea vor fi folosite pentru detectarea formelor T și L
*/


#ifndef CANDY_LINIE_H
#define CANDY_LINIE_H

#include "Punct.h"
#include "config.h"
#include <iostream>
using namespace std;

//clasa Linie
class Linie {
    Punct start;
    int lungime;
    bool orientare; // true = orizontal, false = vertical
    int culoare;

public:
    Linie();//constructor
    Linie(Punct start, int lungime = 0, bool orizontala = true, int culoare = 0);//inițilizare
    ~Linie() {}//destructor

    //declar 2 vectori statici și dimensiunile acestora
    static Linie linii_orizontale[50];
    static Linie linii_verticale[50];
    static int dimo;
    static int dimv;

    //getters
    int getLungime() const { return lungime; }
    int getCuloare() const { return culoare; }
    Punct getStart() const { return start; }
    bool getOrientare() const { return orientare; }

    void afiseaza() const;

    //gaseste linii va găsi liniile orizontale și verticale
    void gaseste_linii();

    //găsim o intersecție și transformăm o linie în 0
    Punct intersectie(Linie linii_orizontale[], Linie linii_verticale[], int indice_or, int indice_ve);
    void inlocuiesteLinie(int a[][DIM], Linie linii_orizontale[], Linie linii_verticale[], bool careLinie, int indice);

    //funcții pentru prelucrarea matricei și a vectorilor statici
    static void sterge_toate_liniile();
    static void sterge_linie_orizontala(int indice);
    static void sterge_linie_verticala(int indice);

    //clase prietene, aceste clase pot accesa variabilele și metodele din această clasă
    friend class FormaL;
    friend class FormaT;
};

#endif // CANDY_LINIE_H