CANDY CRUSH AUTOMATIZAT IN A NUTSHELL

MODUL DE RULARE: Proiectul din **master** este format din fișierele _.idea, include, src și CMakeLists.txt_. Acestea se descarcă, se pun în același folder, se deschide proiectul într-un IDE pentru C/C++ (CLion de exemplu), iar proiectul se rulează din **main**. La final se obține fișierul _rezultate.csv_. Pentru fiecare rulare se va obține un fișier diferit întrucât matricea se generează aletor bazat pe timpul când se rulează codul.

CUM FUNCȚIONEAZĂ PROIECTUL:
Bucla de parcurgerea elementelor:
1) Parcurgerea matricei când are loc salvarea liniilor orizontale și verticale.
2) Vectorii de linii sunt parcurse și se caută intersecții între acestea, dacă există se vede dacă forma rezultată e de formă L sau T, iar elementele care participă în intersecție sunt eliminate pentru a evuta suprapunerile în acordarea punctajului.
3) Formele sunt punctate corespunzător, punctajul e adunat la puntajul total, iar formele sunt transformate în 0 pentru ca acestea să fie distruse, iar în matrice să se aplice gravitația.
4) Procesul este repetat cât timp există linii/forme în matrice.
5) Dacă nu sunt forme se caută posibile **SWAP-URI**(un swap este un interschimb între doi vecini ortogonali: a[x][y]<=>a[x+1] [y] sau a[x][y]<=>a[x] [y+1]).
6) Se salvează într-un vector toate combinațiile posibile care dau puncte, iar acestea sunt sortate și se alege cel mai bun candidat în funcție de numărul de puncte rezultat dintr-un swap, numărul de forme generate din efectuarea acelui swap și aplicarea gravitației și densitatea celulelor de aceeași culoare).
7) Se repetă procesul

FORMATUL FIȘIERELOR DIN _rezultate.csv_: Pe coloanele fișierului csv sunt următoarele categorii: 1) game_id, 2) punctaj, 3) numărul swap-urilor, 4) reached target(dacă s-a îndeplinit obiectivul de a ajunge la numărul minim de puncte), 5) stoping_reason(motivul pentru care programul s-a oprit, fie s-a îndeplinit obiectivul, fie nu mai sunt mutări disponibile) și 6) moves, numărul de cascade(numărul de forme create ca rezultat al unui swap și al efectului de gravitație din matrice).
