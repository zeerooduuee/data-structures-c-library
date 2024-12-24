#ifndef STRUTTURE_DATI_QUICK_SORT_RANDOM_HPP
#define STRUTTURE_DATI_QUICK_SORT_RANDOM_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
// #include <random>
#include <cstdlib>
#include <ctime>

/* quick sort a due vie (two-way quick sort) */
/* quick sort randomizzata */

/*
 * la quick sort randomizzata è una variante della quick sort che porta a miglioramenti. la complessita della quick sort randomizzata non cambia rispetto a quella della quick sort normale,
 * cioe entrambe sono Θ(n2) nel caso peggiore e Θ(nlogn) nei casi medi e migliore, quindi dove sta il miglioramento?
 * i vantaggi si possono vedere non dalla complessita assintotica ma dall'analisi di questa. la randomized quick sort fa si che il suo tempo di esecuzione non sia piu dipendente dal input
 * come nel caso della quick sort normale, ma l'input non ha nessun effeto sul tempo di esecuzione della randomized quick sort, piuttosto i casi peggiore, medio e migliore sono determinato solamente
 * dal generatore di numeri casuali, cosa che lo rende piu stabile e tranquillo.
 * bisogna dire che pero nella realta è vero che la quick sort randomizzata rende molto piu improbabile finire nel caso peggiore e quindi a tempi di esecuzioni medi piu bassi, comunque
 * non è probabilissimo finire nel caso peggiore neanche della quick sort normale e quindi questa non avendo da calcolare un indice random e poi scambiare elementi prima di chiamare
 * la partition_ a volte risulta piu veloce.
 */
// comunque sia resta ancora il problema del caso peggiore quando l'input ha tutti i suoi elementi come occorrenze di un elemento (tutti gli elementi uguali) xche
// random o meno si esegue n volte quindi caso peggiore Θ(n2). questo si puo risolvere vedendo la quick sort (randomizzata o anche no) a tre divisione piuttosto che due (altro file).

namespace alg {
    int partition_randomizzata_(std::vector<int>& a, int l, int r) {
        int random_q = l + rand() % (r - l + 1);
        std::swap(a[random_q], a[r]);
        return partition_(a, l, r);
        // un altro modo sarebbe
        /*
        int random_q = l + rand() % (r - l + 1);
        std::swap(a[random_q], a[r]);
        int x = a[r];
        int i = l;
        for(int j = l; j != r; ++j) {
            if (a.at(j) <= x) {
                std::swap(a.at(i), a.at(j));
                i++;
            }
        }
        std::swap(a.at(i), a.at(r));
        return i;
        */
    }
    void quick_sort_randomizzata_(std::vector<int>& a, int l, int r) {
        if (l < r) {
            int q = partition_randomizzata_(a, l, r);
            quick_sort_randomizzata_(a, l, q - 1);
            quick_sort_randomizzata_(a, q + 1, r);
        }
    }
    void quick_sort_randomizzata(std::vector<int>& a) {
        quick_sort_randomizzata_(a, 0, a.size() - 1);
    }
}

#endif //STRUTTURE_DATI_QUICK_SORT_RANDOM_HPP