/*
    În fișierul config.h declar câteva funcții pe care le voi folosi pentru a prelucra matricea
*/


#ifndef CANDY_CONFIG_H
#define CANDY_CONFIG_H

#include <iostream>
#include <cstring>
using namespace std;

#define DIM 11//definesc dimensiunea matricei de joc

extern int a[DIM][DIM];//definesc matricea ca o variabilă externă pentru a putea fi citită și prelucrată în toate fișierele

//îmi declar câteva funcții
void generare(int a[][DIM]);
void afisare(int a[][DIM]);
void gravitatie_si_reumplere(int a[][DIM]);

struct date_iesire {
    int game_id;
    int punctaj;
    int swaps;
    bool reached_target;
    string stoping_reason;
    int moves;
};

/* structura SwapCandidat este folosită pentru a reprezenta un candidat pentru un swap (schimb de celule)
   și pentru a evalua eficiența acestui swap pe baza mai multor criterii:
   scorul potențial, numărul de formațiuni și densitatea celulelor
*/
struct SwapCandidat {
    int x1, y1, x2, y2;//coordonatele celor 2 puncte
    int scor_potential;
    int numar_formatiuni;//numărul de formațiuni care se poate forma dacă se face acest swap
    int densitate;//numărul de celule de aceeași culoare în jurul celulelor ce se vor schimba)

    //operatorul < este suprascris pentru a permite compararea a două obiecte SwapCandidat
    //compararea se face în funcție de prioritate:
    // 1. Numărul de formațiuni detectate
    // 2. Scorul potențial
    // 3. Densitatea
    bool operator<(const SwapCandidat& other) const {
        if (numar_formatiuni != other.numar_formatiuni)
            return numar_formatiuni > other.numar_formatiuni;//prioritate mai mare pentru mai multe formațiuni
        if (scor_potential != other.scor_potential)
            return scor_potential > other.scor_potential;//apoi, prioritate pentru scorul mai mare
        return densitate > other.densitate;//în final, prioritate pentru densitatea mai mare
    }
};

bool exista_formatiuni();
void efectueaza_swap(int x1, int y1, int x2, int y2);
int identifica_densitate(int x, int y, int culoare);
SwapCandidat evalueaza_swap(int x1, int y1, int x2, int y2);
bool gaseste_swap_optim(int &x1, int &y1, int &x2, int &y2);
date_iesire joaca_joc(int game_id);


#endif // CANDY_CONFIG_H