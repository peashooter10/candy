#include "../include/config.h"
#include "../include/linie.h"
#include "../include/formaT.h"
#include "../include/formaL.h"
#include "../include/punct.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//definesc matricea a
int a[DIM][DIM];

//funcția generare îmi generează o matrice random
void generare(int a[][DIM]) {
    srand(time(0));//srand este o funcție care asigură ca rezultatele random să fie determinate de timp
    int i, j;
    //pe măsură ce parcurg matricea
    for (i = 0; i < DIM; i++)
        for (j = 0; j < DIM; j++)
            a[i][j] = (rand()) % 4 + 1; //generez valori de la 1 la 4
}
//funcția afișare îmi afișează matricea
void afisare(int a[][DIM]) {
    int i, j;
    for (i = 0; i < DIM; i++) {
        cout << '\n';
        for (j = 0; j < DIM; j++)
            cout << a[i][j] << ' ';
    }
    cout << '\n';
}

//funcția gravitatie_si_reumplere aplică gravitația și reumplerea matricei
void gravitatie_si_reumplere(int a[][DIM]) {
    for (int j = 0; j < DIM; j++) {//parcurg matricea pe coloane
        int index_inserare = DIM - 1;
        for (int i = DIM - 1; i >= 0; i--) {//parcurg fiecare coloană de jos în sus
            if (a[i][j] != 0) {
                //pentru fiecare element nenul (a[i][j] != 0), îl mut în poziția index_inserare și golesc poziția veche
                a[index_inserare][j] = a[i][j];
                if (index_inserare != i)
                    a[i][j] = 0;
                index_inserare--;//scad index_inserare după fiecare mutare
            }
        }
        for (int k = index_inserare; k >= 0; k--) {
            a[k][j] = rand() % 4 + 1;//generez un element random
        }
    }
}

//funcția verifică dacă există linii pe tablă
bool exista_formatiuni() {
    Linie linie;//creez un obiect de tip linie
    linie.gaseste_linii();//caut linii orizontale și verticale
    bool exista = (Linie::dimo > 0 || Linie::dimv > 0);// verific dacă sunt linii
    Linie::sterge_toate_liniile();//șterg liniile pentru următoarea verificare
    return exista;
}

//funcția face un swap între 2 elemente
void efectueaza_swap(int x1, int y1, int x2, int y2) {
    int aux;
    aux = a[x1][y1];a[x1][y1] = a[x2][y2];a[x2][y2] = aux;
}

//detectează și elimin liniile și formele L și T de pe tablă și adaug punctaj
int detecteaza_si_elimina_formatiuni() {
    int punctaj = 0;
    Linie linie;//creez un obiect Linie pentru a găsi linii
    linie.gaseste_linii();//găsesc liniile orizontale și verticale

    //inițializez dimensiunea
    FormaT::dimt = 0;
    FormaL::diml = 0;

    //parcurge tabla pentru a detecta forme de tip T și L
    for (int i = Linie::dimo - 1; i >= 0; i--) {
        for (int j = Linie::dimv - 1; j >= 0; j--) {
            Punct intersectie = linie.intersectie(Linie::linii_orizontale,
                                                 Linie::linii_verticale, i, j);
            if (intersectie.getX() != -1) {  //dacă există o intersecție validă
                int dimt_inainte = FormaT::dimt;
                FormaT formaT;
                formaT.gasesteT(intersectie, i, j);//caut forma T
                if (FormaT::dimt == dimt_inainte) {
                    FormaL formaL;
                    formaL.gasesteL(intersectie, i, j);//caut forma L
                }
            }
        }
    }

    //elimin formele T și L și adaug punctaj
    for (int i = 0; i < FormaT::dimt; i++) {
        FormaT formaT;
        formaT.inlocuiesteT(a, i);//adaug 0
        punctaj += 30;
    }

    for (int i = 0; i < FormaL::diml; i++) {
        FormaL formaL;
        formaL.inlocuiesteL(a, i); //adaug 0
        punctaj += 20;
    }

    //elimin linii orizontale și verticale și adaug punctaj
    for (int i = 0; i < Linie::dimo; i++) {
        int len = Linie::linii_orizontale[i].getLungime();
        if (len == 5) punctaj += 50;
        else if (len == 4) punctaj += 10;
        else if (len == 3) punctaj += 5;
        Linie linie_temp;
        linie_temp.inlocuiesteLinie(a, Linie::linii_orizontale,Linie::linii_verticale, true, i);
    }

    for (int i = 0; i < Linie::dimv; i++) {
        int len = Linie::linii_verticale[i].getLungime();
        if (len == 5) punctaj += 50;
        else if (len == 4) punctaj += 10;
        else if (len == 3) punctaj += 5;
        Linie linie_temp;
        linie_temp.inlocuiesteLinie(a, Linie::linii_orizontale,Linie::linii_verticale, false, i);
    }

    Linie::sterge_toate_liniile();//șterge toate liniile
    FormaT::sterge_toate_T();//șterg formele T
    FormaL::sterge_toate_L();//șterg formele L

    return punctaj;
}

//funcția identifică_densitate calculează densitatea celulelor de aceeași culoare din jurul unei celule
int identifica_densitate(int x, int y, int culoare) {
    int densitate = 0;
    //parcurge un pătrat de 5x5 și număr celulele de aceeași culoare
    for (int dx = -2; dx <= 2; dx++) {
        for (int dy = -2; dy <= 2; dy++) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < DIM && ny >= 0 && ny < DIM) {
                if (a[nx][ny] == culoare) {
                    densitate++;
                }
            }
        }
    }
    return densitate;
}

//funcția evaluează_swap vede
SwapCandidat evalueaza_swap(int x1, int y1, int x2, int y2) {
    SwapCandidat candidat;
    candidat.x1 = x1; candidat.y1 = y1;
    candidat.x2 = x2; candidat.y2 = y2;
    candidat.scor_potential = 0;
    candidat.numar_formatiuni = 0;
    candidat.densitate = 0;

    efectueaza_swap(x1, y1, x2, y2);

    Linie linie;
    linie.gaseste_linii();

    FormaT::dimt = 0;
    FormaL::diml = 0;

    //verific dacă sunt formate formațiuni T și L și adaug punctaj
    for (int i = 0; i < Linie::dimo; i++) {
        for (int j = 0; j < Linie::dimv; j++) {
            Punct intersectie = linie.intersectie(Linie::linii_orizontale,
                                                 Linie::linii_verticale, i, j);
            if (intersectie.getX() != -1) {
                int dimt_inainte = FormaT::dimt;
                FormaT formaT;
                formaT.gasesteT(intersectie, i, j);
                if (FormaT::dimt > dimt_inainte) {
                    candidat.scor_potential += 30;
                    candidat.numar_formatiuni++;
                } else {
                    FormaL formaL;
                    formaL.gasesteL(intersectie, i, j);
                    if (FormaL::diml > 0) {
                        candidat.scor_potential += 20;
                        candidat.numar_formatiuni++;
                    }
                }
            }
        }
    }

    //verific și adaugă punctaj pentru linii
    for (int i = 0; i < Linie::dimo; i++) {
        int len = Linie::linii_orizontale[i].getLungime();
        if (len == 5) candidat.scor_potential += 50;
        else if (len == 4) candidat.scor_potential += 10;
        else if (len == 3) candidat.scor_potential += 5;
        candidat.numar_formatiuni++;
    }

    for (int i = 0; i < Linie::dimv; i++) {
        int len = Linie::linii_verticale[i].getLungime();
        if (len == 5) candidat.scor_potential += 50;
        else if (len == 4) candidat.scor_potential += 10;
        else if (len == 3) candidat.scor_potential += 5;
        candidat.numar_formatiuni++;
    }

    //calculează densitatea pentru celulele schimbate
    int culoare1 = a[x1][y1];
    int culoare2 = a[x2][y2];
    candidat.densitate = identifica_densitate(x1, y1, culoare1) + identifica_densitate(x2, y2, culoare2);

    Linie::sterge_toate_liniile();  //șterg linii
    FormaT::sterge_toate_T();       //șterg forme T
    FormaL::sterge_toate_L();       //șterg forme L

    efectueaza_swap(x1, y1, x2, y2);

    return candidat;
}

//funcția găsește_swap_optim returnează cel mai bun swap
bool gaseste_swap_optim(int &x1, int &y1, int &x2, int &y2) {
    vector<SwapCandidat> candidati; //vector dinamic pentru opțiuni

    //încep căutarea de jos pentru a maximiza cascadele
    for (int i = DIM - 1; i >= 0; i--) {
        for (int j = 0; j < DIM; j++) {
            //swap orizontal
            if (j < DIM - 1) {
                SwapCandidat c = evalueaza_swap(i, j, i, j + 1);
                if (c.scor_potential > 0) {
                    candidati.push_back(c);//adaug candidatul
                }
            }
            //swap vertical
            if (i < DIM - 1) {
                SwapCandidat c = evalueaza_swap(i, j, i + 1, j);
                if (c.scor_potential > 0) {
                    candidati.push_back(c);//adaug candidatul
                }
            }
        }
    }

    //dacă nu sunt swapuri
    if (candidati.empty()) {
        return false;
    }

    //sortez candidații
    sort(candidati.begin(), candidati.end());

    //aleg cel mai bun candidat pentru swap
    x1 = candidati[0].x1;
    y1 = candidati[0].y1;
    x2 = candidati[0].x2;
    y2 = candidati[0].y2;

    return true;//am găsit un swap
}

//funcția care rulează un joc
date_iesire joaca_joc(int game_id) {

    date_iesire d;

    generare(a);//generez matricea

    int punctaj = 0;//inițializez punctajul
    int swaps = 0;//inițializez numărul de swap-uri
    int cascades = 0;
    bool reached_target = false;
    string stopping_reason = "";

    //cout << "\n=== JOC " << game_id + 1 << " ===" << endl;
    cout<<"progres: "<<game_id+1<<'\n';

    //parcurg formațiunile, adaug puncte și reumplu matricea pentru început
    while (exista_formatiuni()) {
        punctaj += detecteaza_si_elimina_formatiuni();
        gravitatie_si_reumplere(a);
        cascades++;
    }

    int protectie = 0;//protecție pentru a preveni buclele infinite
    //continui până la atingerea punctajului de 10.000 sau până când nu mai există mutări valabile
    while (punctaj < 10000 && protectie < 5000) {
        int x1, y1, x2, y2;

        //caut un swap
        if (!gaseste_swap_optim(x1, y1, x2, y2)) {
            stopping_reason = "NO_MOVES";//nu mai sunt mutări
            break;
        }

        efectueaza_swap(x1, y1, x2, y2);//fac un swap
        swaps++;


        //aplic gravitația, cresc punctajul
        int protectie_cascade = 0;
        while (exista_formatiuni() && protectie_cascade < 100) {
            punctaj += detecteaza_si_elimina_formatiuni();
            gravitatie_si_reumplere(a);
            cascades++;
            protectie_cascade++;
        }

        if (punctaj >= 10000) {
            reached_target = true;
            stopping_reason = "REACHED_TARGET";
            break;
        }

        protectie++;//cresc protecția împotriva buclelor infinite
    }

    d.game_id=game_id;
    d.punctaj=punctaj;
    d.swaps=swaps;
    d.reached_target=reached_target;
    d.stoping_reason=stopping_reason;
    d.moves=cascades;

    return d;
}

