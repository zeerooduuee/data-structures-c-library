#ifndef STRUTTURE_DATI_ALGORITMO_MERGE_SORT_HPP
#define STRUTTURE_DATI_ALGORITMO_MERGE_SORT_HPP

#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>
#include <list>

/* merge sort */

/*
 * algoritmo di ordinamento appartenente a gli sorting algorithms per confronto con tecnica divide et impera, e' un algoritmo che si svolge in tre steps
 * divide (separa la strttura dati di input in due sottostrutture sinistra e destra contenenti "meta" delgi elementi), impera (ordina le due sottostrtture) e merge (mette insieme
 * le due sottostrtture che sappiamo essere ordinate in un'unica strttura ordinata).
 * per essere sinceri non e' propio cosi che funziona, ma l'idea dell'implementazione e' un po' diversa. tutto si svolge da due funzioni, la merge_sort e' la funzione di inizio che separa la strttura
 * in input in due sottostrutture che poi tramite la chiamata ricorsiva di questa saranno ordinate e messe assieme poi dalla merge (un'altra funzione), ma poi quello che succede e'
 * che queste chiamate come sappiamo, per il funzionamento di linguaggi come c, c++, c#, java e cosi non corrono tutte in contemporaneo, ma sfruttano lo stack (struttura dati che si usa per la ricorsione) per effetuare le chiamate,
 * per questo allora la parte di divide, impera e merge sara effetuatta piu di una volta in tante sottostrutture e poi eventualmente messa assieme per la struttura finale di output. un'altra cosa da considerare
 * e' che la parte di impera non esiste veramente, cioe in realta semplicemente si separa la struttura in due sottostrutture che una volta che sono piccole a sufficienza e per la ricorsione poii vengono mergiate in modo ordinato.
 * ultima cosa da notare, questo in realta per tutti gli algoritmi, non esiste un unico modo di implementarli, cioe una volta capita la logica ci possono essere molte varianti sull'implementazione a seconda
 * della idea che si vuole seguire, quindi non e' importante copiare parola per parola.
 */
/*
 * vantaggi:
 * 1. T(n) = Θ(n log n). sempre nlog(n) a prescindere dell'input, cosa che e' ottima dato il limite inferiore di O(n log n) per gli algoritmi di ordinamento basati sull confronto
 * 2. e' un metodo stabile. mantiene gli elementi con piu di una occorenza ordinati nello stesso modo che nell'input.
 * svantaggi:
 * 1. non è in loco (sul posto o in-place) xche utilizza un vettore ausiliario proporzionale al numero di elementi da ordinare. quindi la complessita spaziale non e' Θ(1) o costante
 * 2. il tempo di calcolo del mergesort dipende essenzialmente dal numero di elementi da ordinare e non trae beneficio da eventuali ordinamenti dell’input, come fa l’insertion sort o la bubble sort
 */

namespace alg {
    void merge(std::vector<int>& a, int l, int m, int r) {
        int size_one = m - l + 1;
        int size_two = r - m;
        // creare due vettori di appoggio, uno sinistro e uno destro
        std::vector<int> left;
        std::vector<int> right;
        /*
        for(int i = l; i != size_one; ++i) {
            left.push_back(a[i]);
        }
        for(int i = m + 1; i != size_two; ++i) {
            right.push_back(a[i]);
        }
         */
        for(int i = 0; i != size_one; ++i) {
            left.push_back(a[l + i]);
        }
        for(int i = 0; i != size_two; ++i) {
            right.push_back(a[m + 1 + i]);
        }
        left.push_back(std::numeric_limits<int>::max()); // left[size_one + 1]
        right.push_back(std::numeric_limits<int>::max()); // right[size_two + 1]
        int i = 0;
        int j = 0;
        for(int k = l; k <= r; ++k) {
            if(left[i] <= right[j]) {
                a[k] = left[i++];
            } else {
                a[k] = right[j++];
            }
        }
    }
    void merge_sort(std::vector<int>& a, int l, int r) {
        // if (l >= r) { return; }
        if (l < r) {
            int m = (l + r) / 2; // int m = l + (r - l) / 2;
            merge_sort(a, l, m);
            merge_sort(a, m + 1, r);
            merge(a, l, m, r);
        }
    }
    void merge_sort_(std::vector<int>& a) {
        merge_sort(a, 0, a.size() - 1);
    }

    void merge(std::list<int>& a, std::list<int>& l, std::list<int>& r) {
        auto it_l = l.begin();
        auto it_r = r.begin();

        // unire gli elementi delle due sottoliste ordinate
        while (it_l != l.end() && it_r != r.end()) {
            if (*it_l <= *it_r) {
                a.push_back(*it_l);
                ++it_l;
            } else {
                a.push_back(*it_r);
                ++it_r;
            }
        }

        // aggiungere eventuali elementi rimanenti nella lista sinistra
        while (it_l != l.end()) {
            a.push_back(*it_l);
            ++it_l;
        }

        // aggiungere eventuali elementi rimanenti nella lista destra
        while (it_r != r.end()) {
            a.push_back(*it_r);
            ++it_r;
        }
    }
    void merge_sort(std::list<int>& a) {
        if(a.size() <= 1) {
            return; // gia ordinata o vuota
        }
        std::list<int> l, r;
        auto m = std::next(a.begin(), a.size() / 2);
        l.splice(l.begin(), a, a.begin(), m);
        r.splice(r.begin(), a, a.begin(), a.end()); // first: a.begin() xche essendo che il metodo splice e' implementato tramite move scemantics, ora a.begin() sara il primo della seconda meta

        merge_sort(l);
        merge_sort(r);

        merge(a, l, r);
    }
}

#endif //STRUTTURE_DATI_ALGORITMO_MERGE_SORT_HPP