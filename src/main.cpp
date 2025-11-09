#include <iostream>
#include <fstream>
#include <ctime>
#include "../include/config.h"

using namespace std;

int main() {
    int total_puncte = 0;
    int total_swaps = 0;
    float avg_puncte;
    float avg_swaps;

    date_iesire d;
    ofstream fout("rezultate.csv"); // fișierul CSV de ieșire

    // scriem antetul (o singură dată)
    fout << "GameID,Punctaj,Swaps,ReachedTarget,StopReason,MovesTo10000\n";

    time_t time_inceput;
    time(&time_inceput);


    cout << "CANDY CRUSH\n";

    for (int i = 0; i < 100; i++) {
        d = joaca_joc(i);

        if (d.reached_target==true)
            total_puncte += d.punctaj;total_swaps += d.swaps;

        //scriu rezultatele în fișierul csv
        fout << d.game_id +1 << ","
             << d.punctaj << ","
             << d.swaps << ","
             << d.reached_target << ","
             << d.stoping_reason << ","
             << d.moves
             << "\n";
    }

    avg_puncte = total_puncte * 1.0;
    avg_puncte /= 100;
    avg_swaps = total_swaps * 1.0;
    avg_swaps /= 100;

    fout<<"Average Puncte: "<<avg_puncte<<','<<"Average Swaps: "<<avg_swaps;

    fout.close();
    cout << "Rezultatele au fost salvate în fisierul rezultate.csv\n";

    time_t time_sfarsit;
    time(&time_sfarsit);

    cout << ctime(&time_inceput)<<'\n';
    cout << ctime(&time_sfarsit);
    return 0;
}
