#include "../include/config.h"
#include "../include/Punct.h"
#include "../include/FormaT.h"
#include "../include/Linie.h"
#include <iostream>
using namespace std;
//definesc SAFE_ZERO pentru a schimba un element în 0 fără a depăși DIM matricei
#define SAFE_ZERO(x, y) if ((x)>=0 && (x)<DIM && (y)>=0 && (y)<DIM) a[x][y]=0;

int FormaT::dimt = 0;
FormaT FormaT::forme_de_t[50];

FormaT::FormaT() : start(Punct(0, 0)), baza(true), varf(true), culoare(0) {}//inițializare

FormaT::FormaT(bool baza, bool varf, Punct start, int culoare)
    : start(start), baza(baza), varf(varf), culoare(culoare) {}

//resetez vectorul de forme T
void FormaT::sterge_toate_T() {
    dimt = 0;
    for (int i = 0; i < 50; i++) {
        forme_de_t[i] = FormaT();
    }
}

//funcția găseșteL găsește ce fel de T
void FormaT::gasesteT(Punct intersectie, int indice_or, int indice_ve) {
    int i = intersectie.getX();
    int j = intersectie.getY();
    int culoare_curenta = a[i][j];

    bool gasit_T = false;

    //verific forma ⟂ (baza = true, varf = true)
    if (i >= 1 && i < DIM - 1 && j < DIM - 2) {
        if (a[i-1][j] == culoare_curenta &&
            a[i][j] == culoare_curenta &&
            a[i+1][j] == culoare_curenta &&
            a[i][j+1] == culoare_curenta &&
            a[i][j+2] == culoare_curenta) {
            forme_de_t[dimt] = FormaT(true, true, Punct(i, j), culoare_curenta);
            dimt++;
            gasit_T = true;
        }
    }

    //verific forma |− (baza = false, varf = true)
    if (!gasit_T && i >= 1 && i < DIM - 1 && j >= 2) {
        if (a[i-1][j] == culoare_curenta &&
            a[i][j] == culoare_curenta &&
            a[i+1][j] == culoare_curenta &&
            a[i][j-1] == culoare_curenta &&
            a[i][j-2] == culoare_curenta) {
            forme_de_t[dimt] = FormaT(false, true, Punct(i, j), culoare_curenta);
            dimt++;
            gasit_T = true;
        }
    }

    //verific forma T (baza = true, varf = false)
    if (!gasit_T && i < DIM - 2 && j >= 1 && j < DIM - 1) {
        if (a[i][j-1] == culoare_curenta &&
            a[i][j] == culoare_curenta &&
            a[i][j+1] == culoare_curenta &&
            a[i+1][j] == culoare_curenta &&
            a[i+2][j] == culoare_curenta) {
            forme_de_t[dimt] = FormaT(true, false, Punct(i, j), culoare_curenta);
            dimt++;
            gasit_T = true;
        }
    }

    //verific forma -| (baza = false, varf = false)
    if (!gasit_T && i >= 2 && j >= 1 && j < DIM - 1) {
        if (a[i][j-1] == culoare_curenta &&
            a[i][j] == culoare_curenta &&
            a[i][j+1] == culoare_curenta &&
            a[i-1][j] == culoare_curenta &&
            a[i-2][j] == culoare_curenta) {
            forme_de_t[dimt] = FormaT(false, false, Punct(i, j), culoare_curenta);
            dimt++;
            gasit_T = true;
        }
    }

    //dacă am găsit formă T, șterg liniile care au fost folosite
    if (gasit_T) {
        if (indice_or > indice_ve) {
            Linie::sterge_linie_orizontala(indice_or);
            Linie::sterge_linie_verticala(indice_ve);
        } else {
            Linie::sterge_linie_verticala(indice_ve);
            Linie::sterge_linie_orizontala(indice_or);
        }
    }
}

//înlocuiesc cu 0
void FormaT::inlocuiesteT(int a[][DIM], int indice) {
    if (indice < 0 || indice >= dimt) return;

    FormaT aux = FormaT::forme_de_t[indice];
    int x = aux.start.getX();
    int y = aux.start.getY();

    // ⟂ (baza = true, varf = true)
    if (aux.baza && aux.varf) {
        SAFE_ZERO(x-1, y);
        SAFE_ZERO(x, y);
        SAFE_ZERO(x+1, y);
        SAFE_ZERO(x, y+1);
        SAFE_ZERO(x, y+2);
    }
    // |− (baza = false, varf = true)
    else if (!aux.baza && aux.varf) {
        SAFE_ZERO(x-1, y);
        SAFE_ZERO(x, y);
        SAFE_ZERO(x+1, y);
        SAFE_ZERO(x, y-1);
        SAFE_ZERO(x, y-2);
    }
    // T (baza = true, varf = false)
    else if (aux.baza && !aux.varf) {
        SAFE_ZERO(x, y-1);
        SAFE_ZERO(x, y);
        SAFE_ZERO(x, y+1);
        SAFE_ZERO(x+1, y);
        SAFE_ZERO(x+2, y);
    }
    // -| (baza = false, varf = false)
    else {
        SAFE_ZERO(x, y-1);
        SAFE_ZERO(x, y);
        SAFE_ZERO(x, y+1);
        SAFE_ZERO(x-1, y);
        SAFE_ZERO(x-2, y);
    }
}