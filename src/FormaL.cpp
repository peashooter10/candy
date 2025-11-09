#include "../include/config.h"
#include "../include/Punct.h"
#include "../include/FormaL.h"
#include "../include/Linie.h"
//definesc SAFE_ZERO pentru a schimba un element în 0 fără a depăși DIM matricei
#define SAFE_ZERO(x, y) if ((x)>=0 && (x)<DIM && (y)>=0 && (y)<DIM) a[x][y]=0;

int FormaL::diml = 0;
FormaL FormaL::forme_de_l[50];

FormaL::FormaL() : start(Punct(0, 0)), orizontal(true), vertical(true), culoare(0) {}//constructor

FormaL::FormaL(bool orizontal, bool vertical, Punct start, int culoare)
    : start(start), orizontal(orizontal), vertical(vertical), culoare(culoare) {}//inițializare

//resetez vectorul de forme L
void FormaL::sterge_toate_L() {
    diml = 0;
    for (int i = 0; i < 50; i++) {
        forme_de_l[i] = FormaL();
    }
}

//funcția găseșteL găsește ce fel de L
void FormaL::gasesteL(Punct intersectie, int indice_or, int indice_ve) {
    int i = intersectie.getX();
    int j = intersectie.getY();
    int culoare_curenta = a[i][j];

    bool gasit_L = false;

    //verific forma |¯ (orizontal = true, vertical = true)
    if (i < DIM - 2 && j >= 2) {
        if (a[i][j] == culoare_curenta &&
            a[i+1][j] == culoare_curenta &&
            a[i+2][j] == culoare_curenta &&
            a[i][j-1] == culoare_curenta &&
            a[i][j-2] == culoare_curenta) {
            forme_de_l[diml] = FormaL(true, true, Punct(i, j), culoare_curenta);
            diml++;
            gasit_L = true;
        }
    }

    //verific forma |_ (orizontal = true, vertical = false)
    if (!gasit_L && i < DIM - 2 && j < DIM - 2) {
        if (a[i][j] == culoare_curenta &&
            a[i+1][j] == culoare_curenta &&
            a[i+2][j] == culoare_curenta &&
            a[i][j+1] == culoare_curenta &&
            a[i][j+2] == culoare_curenta) {
            forme_de_l[diml] = FormaL(true, false, Punct(i, j), culoare_curenta);
            diml++;
            gasit_L = true;
        }
    }

    //verific forma ¯| (orizontal = false, vertical = true)
    if (!gasit_L && i >= 2 && j >= 2) {
        if (a[i][j] == culoare_curenta &&
            a[i-1][j] == culoare_curenta &&
            a[i-2][j] == culoare_curenta &&
            a[i][j-1] == culoare_curenta &&
            a[i][j-2] == culoare_curenta) {
            forme_de_l[diml] = FormaL(false, true, Punct(i, j), culoare_curenta);
            diml++;
            gasit_L = true;
        }
    }

    //verific forma _| (orizontal = false, vertical = false)
    if (!gasit_L && i >= 2 && j < DIM - 2) {
        if (a[i][j] == culoare_curenta &&
            a[i-1][j] == culoare_curenta &&
            a[i-2][j] == culoare_curenta &&
            a[i][j+1] == culoare_curenta &&
            a[i][j+2] == culoare_curenta) {
            forme_de_l[diml] = FormaL(false, false, Punct(i, j), culoare_curenta);
            diml++;
            gasit_L = true;
        }
    }

    //dacă am găsit formă L, șterg liniile care au fost folosite
    if (gasit_L) {
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
void FormaL::inlocuiesteL(int a[][DIM], int indice) {
    if (indice < 0 || indice >= diml) return;

    FormaL aux = FormaL::forme_de_l[indice];
    int x = aux.start.getX();
    int y = aux.start.getY();

    //orizontal este true  - vertical este true  =) |¯
    if (aux.orizontal==true && aux.vertical==true) {
        SAFE_ZERO(x,y);SAFE_ZERO(x+1,y);SAFE_ZERO(x+2,y);SAFE_ZERO(x,y-1);SAFE_ZERO(x,y-2);
    }
    //orizontal este true  - vertical este false =) |_
    if (aux.orizontal==true && aux.vertical==false) {
        SAFE_ZERO(x,y);SAFE_ZERO(x+1,y);SAFE_ZERO(x+2,y);SAFE_ZERO(x,y+1);SAFE_ZERO(x,y+2);
    }
    //orizontal este false - vertical este true  =) ¯|
    if (aux.orizontal==false && aux.vertical==true) {
        SAFE_ZERO(x,y);SAFE_ZERO(x-1,y);SAFE_ZERO(x-2,y);SAFE_ZERO(x,y-1);SAFE_ZERO(x,y-2);
    }
    //orizontal este false - vertical este false =) _|
    if (aux.orizontal==false && aux.vertical==false) {
        SAFE_ZERO(x,y);SAFE_ZERO(x-1,y);SAFE_ZERO(x-2,y);SAFE_ZERO(x,y+1);SAFE_ZERO(x,y+2);
    }
}