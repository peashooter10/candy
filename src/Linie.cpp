#include "../include/Linie.h"
#include "../include/config.h"
#include <iostream>
using namespace std;

// definim elementele statice
Linie Linie::linii_orizontale[50];
Linie Linie::linii_verticale[50];
int Linie::dimo = 0;
int Linie::dimv = 0;


Linie::Linie() : start(Punct(0, 0)), lungime(0), orientare(true), culoare(0) {}//constructor

Linie::Linie(Punct start, int lungime, bool orizontala, int culoare)
    : start(start), lungime(lungime), orientare(orizontala), culoare(culoare) {}//inițializare

void Linie::afiseaza() const {
    cout << (orientare ? "Orizontala" : "Verticala")
            << " din (" << start.getX() << "," << start.getY() << ") lungime " << lungime
            << " culoare " << culoare << endl;
}//afisare

//funcția găsește_linii găsește liniile orizontale și verticale
void Linie::gaseste_linii() {
    //inițializez dimensiunile
    dimo = 0;
    dimv = 0;

    //caut linii orizontale
    for (int i = 0; i < DIM; i++) {
        int start_j = 0;
        int culoare_curenta = a[i][0];

        for (int j = 1; j <= DIM; j++) {
            //verific dacă s-a schimbat culoarea sau am ajuns la final
            if (j == DIM || a[i][j] != culoare_curenta) {
                int lungime_linie = j - start_j;

                //salvez doar linii cu lungime >= 3
                if (lungime_linie >= 3) {
                    if (dimo < 50)
                        linii_orizontale[dimo++] = Linie(Punct(i, start_j), lungime_linie, true, culoare_curenta);
                }

                //actualizare
                if (j < DIM) {
                    start_j = j;
                    culoare_curenta = a[i][j];
                }
            }
        }
    }

    //caut linii verticale
    for (int j = 0; j < DIM; j++) {
        int start_i = 0;
        int culoare_curenta = a[0][j];

        for (int i = 1; i <= DIM; i++) {
            if (i == DIM || a[i][j] != culoare_curenta) {
                int lungime_linie = i - start_i;

                //salvez doar linii cu lungime >= 3
                if (lungime_linie >= 3) {
                    if (dimv < 50)
                        linii_verticale[dimv++] = Linie(Punct(start_i, j), lungime_linie, false, culoare_curenta);
                }
                //actualizare
                if (i < DIM) {
                    start_i = i;
                    culoare_curenta = a[i][j];
                }
            }
        }
    }
}

//funcția intersecție vede dacă între două linii există intersecții și dacă da care este aceea
Punct Linie::intersectie(Linie linii_orizontale[], Linie linii_verticale[],
                         int indice_or, int indice_ve) {
    //verific daca liniile au aceeași culoare
    if (linii_orizontale[indice_or].culoare != linii_verticale[indice_ve].culoare) {
        return Punct(-1, -1);
    }

    Linie &lo = linii_orizontale[indice_or];
    Linie &lv = linii_verticale[indice_ve];

    //salvez în x și y intersecția
    int x_intersectie = lo.start.getX();
    int y_intersectie = lv.start.getY();

    //verificam daca punctul de intersectie e în ambele linii
    if (y_intersectie >= lo.start.getY() && y_intersectie < lo.start.getY() + lo.lungime &&
        x_intersectie >= lv.start.getX() && x_intersectie < lv.start.getX() + lv.lungime) {
        return Punct(x_intersectie, y_intersectie);
    }

    return Punct(-1, -1);
}

//funcția șterge_toate_liniile are rolul de a reseta vectorul static
void Linie::sterge_toate_liniile() {
    dimo = 0;
    dimv = 0;
    for (int i = 0; i < 50; i++) {
        linii_orizontale[i] = Linie();
        linii_verticale[i] = Linie();
    }
}

//funcțiile șterge_linie au rolul de a elimina un anumit element din vector
//în cazul în care s-a găsit o intersecție între 2 linii
void Linie::sterge_linie_orizontala(int indice) {
    if (indice < 0 || indice >= dimo) return;

    //mut toate liniile de după indice cu o poziție înapoi
    for (int i = indice; i < dimo - 1; i++) {
        linii_orizontale[i] = linii_orizontale[i + 1];
    }
    dimo--;
}
void Linie::sterge_linie_verticala(int indice) {
    if (indice < 0 || indice >= dimv) return;

    //mut toate liniile de după indice cu o poziție înapoi
    for (int i = indice; i < dimv - 1; i++) {
        linii_verticale[i] = linii_verticale[i + 1];
    }
    dimv--;
}

//funcția înlocuiește_linii are rolul de a transforma o linie în 0
void Linie::inlocuiesteLinie(int a[][DIM], Linie linii_orizontale[],
                             Linie linii_verticale[], bool careLinie, int indice) {
    if (careLinie) {
        //înlocuim linia orizontala
        Linie &lo = linii_orizontale[indice];
        for (int j = 0; j < lo.lungime; j++) {
            a[lo.start.getX()][lo.start.getY() + j] = 0;
        }
    } else {
        //înlocuim linia verticala
        Linie &lv = linii_verticale[indice];
        for (int i = 0; i < lv.lungime; i++) {
            a[lv.start.getX() + i][lv.start.getY()] = 0;
        }
    }
}
