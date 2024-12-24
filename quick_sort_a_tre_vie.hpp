#ifndef STRUTTURE_DATI_QUICK_SORT_A_TRE_VIE_HPP
#define STRUTTURE_DATI_QUICK_SORT_A_TRE_VIE_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

/* quick sort a tre vie (three-way quick sort) */

/*
 * siccome la quick sort normale, randomizzata e con pivot mediana di 3 elementi non sono altro che modi diversi per scegliere il pivot xche di per se l'implementazione delgi algoritmi
 * non cambia, allora useremo quella normale per semplicita. si potrebbe dire che due vie e tre vie sono un super tipo di poi la normale, la randomizzata e cosi via.
 */
/*
 * quindi la variante della quick sort a due vie, di nome quick sort a tre vie, è molto simile alla sua contraparte in quasi tutta la logica dell'algoritmo pero ci sono delle differenze.
 * sulla quick sort a tre vie abbiamo che la funzione ricorsivamente ordinera la struttura dati chiamandosi su sotto strutture dati da ordinare, ordinarle e poi metterle insieme a quella che era la parte ordinata
 * (indentico alla quick sort a due vie in questo senso) e sappiamo che non lo fa con un processo di merge_ ma semplicemente sfruttando la propieta delle divisioni date dal pivot.
 * nella quick sort a tre vie si sceglie un pivot (nel modo piu comodo possibile) come per esempio l'elemento in ultima posizione e poi si separa l'array (dico array xche mi scoccia dire struttura dati ogni volta)
 * in 3 porzioni quella di sinistra che sono gli elementi minori del pivot (<), quella di mezzo che sono gli elementi uguali al pivot (==) e quella di destra che sono gli elementi maggiori del pivot (>), su quella a due
 * vie avevamo solo sinistra minori o uguali al pivot (<=), il pivot e a destra gli elementi maggiori del pivot (>). facendo cosi, tutte le occorrenze di un stesso elemento che sono gia ordinate
 * di natura saranno direttamente nel centro, quindi basta ordinare la porzione dei minori e maggiori e poi mettere insieme (identico come quando avevamo solo il pivot come elemento di mezzo ma
 * in questo caso raggruppiamo piu lementi rendendo il tutto piu efficiente).
 * questa procedura viene realizzata dalla partition che non ritorna piu un unico indice ma una coppia di questi.
 * abbiamo gli elementi da ordinare di A[l ... r] la partition ritornera una coppia di indici <q, t> che delimitano la porzione in cui gli elemnti compresi tra q e t inclusi sono uguali al pivot (x). l <= q <= t <= r
 * tutti gli elementi di A[q ... t] sono uguali al pivot (x), quelli di A[l ... q-1] sono minori del pivot (x) A[q] e quelli di A[t+1 ... r] sono maggiori del pivot (x) A[q].
 * la partition_ btw ha complessita Θ(r - l)
 */
/*
 * per capire meglio l'implementazione di questo algoritmo, aiuta molto visualizzare che cosa fanno gli indici della partition durante l'esecuzione.
 * durante l'esecuzione dell'algoritmo della partition_ l'array viene diviso in 5 porzioni. x è il pivot [<x][==x][?][>x][x]
 *                                                                                                      |   |    |  |    |
 *                                                                                                      l  min  eq max   r
 * 1. da l a min non compreso sono presenti tutti gli elementi strettamente minori del pivot.
 * 2. da min a eq non compreso sono presenti tutti gli elementi uguali al pivot.
 * 3. da eq a max non compreso sono presenti tutti gli elementi che non sappiamo ancora in che partizione appartengono, perché vengono comparati man mano che procede l’algoritmo
 * alla fine della procedura, infatti, eq e max avranno lo stesso valore.
 * 4. da max a r non compreso sono presenti tutti gli elementi strettamente maggiori del pivot.
 * 5. in posizione r è presente il pivot.
 * da notare che all'inizio dell'esecuzione le cose sono un po' sovrapposte
 */
/*
 * per quanto riguarda l'analisi della complessita, simile alla quick sort a due vie abbiamo che caso migliore ha complessita Θ(n) che si presenta solo se l'array contiene tutti elementi occorrenze dello
 * stesso elemento, per caso medio Θ(nlogn) e per caso peggiore Θ(n2) (ma meno probabile rispetto al quick sort classico). diciamo che l'implmentazione è un po' piu complessa ma il raggruppamento di elementi
 * ci aiuta a rendere l'algoritmo piu efficiente (anche se assintoticamente è uguale ma in realta non l è) ma questo solo su array che possono contenere tante occorrenze per diversi elementi, se l'array
 * non contiene occorrenze multiple degli elementi o ci sono poche, a sto punto tanto vale la due vie.
 */

namespace alg {
    std::pair<int, int> partition_tre_vie_(std::vector<int>& a, int l, int r) {
        int x = a.at(r);
        int min, max, eq;
        min = eq = l;
        max = r;
        while (eq < max) {
            if (a.at(eq) < x) {
                std::swap(a.at(eq), a.at(min));
                min++;
                eq++;
            } else if (a.at(eq) == x) {
                eq++;
            } else {
                max--;
                std::swap(a.at(eq), a.at(max));
            }
        }
        std::swap(a.at(r), a.at(max));
        return std::pair{min, max};

    }
    void quick_sort_tre_vie_(std::vector<int>& a, int l, int r) {
        if (l < r) {
            std::pair<int, int> temp = partition_tre_vie_(a, l, r);
            int q = temp.first;
            int t = temp.second;
            quick_sort_tre_vie_(a, l, q - 1);
            quick_sort_tre_vie_(a, t + 1, r);
        }
    }
    void quick_sort_tre_vie(std::vector<int>& a) {
        quick_sort_tre_vie_(a, 0, a.size() - 1);
    }
}

#endif //STRUTTURE_DATI_QUICK_SORT_A_TRE_VIE_HPP