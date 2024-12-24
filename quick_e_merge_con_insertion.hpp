#ifndef STRUTTURE_DATI_QUICK_E_MERGE_CON_INSERTION_HPP
#define STRUTTURE_DATI_QUICK_E_MERGE_CON_INSERTION_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

/* varianti della quick sort e della merge sort con insertion sort */
/*
 * l'idea è quella che la merge sort e la quick sort sono algoritmi estremamente efficienti e veloci ma di solito vengono utilizzati su array di grandi dimensioni, questo xche cosi
 * si sfruttano meglio le loro propieta. da un'altra parte abbiamo pure la insertion sort che è considerato uno dei migliori sorting per casi di array di piccole dimensioni.
 * quindi come gli mettiamo assieme? per implementare una specie di fusione dell'algoritmo di merge sort e di insertion sort o stessa cosa ma con la quick sort che sfrutti le propieta
 * e vantaggi di entrambi è abbastanza semplice e lo si puo fare in due modi.
 * 1. cambiare la condizione di continuazione if (l < r) { ... } con un caso base che if ((r - l + 1) <= M) { insertion_sort(A, l, r) }
 * quindi in questo caso quello che facciamo è che nei casi per cui (r - l + 1) <= M dove (r - l + 1) è il rango su cui stiamo sortando nella chiamata corrente e M è un qualsiasi numero tra 5 e 25 incluso
 * (questo xche la insertion sort è ideale per array di dimensioni <= 25 elementi), invece di contianuare con le ricorsioni e andare avanti noi fermiamo l'esecuzione e ritorniamo, ma prima ordinando l'array (o sotto array)
 * su cui ci trovivamo, che è esattamente quello che si aspetta la procedura nel return di una qualsiasi chiamata di merge_sort o quick_sort (sotto porzione ordinata o direttamente l'array se in prima chiamata).
 * 2. la seconda opzione è quasi identica alla prima, l'unica differenza è che invece di fare return chiamata, facciamo unicamente return, in questo modo la procedura va avanti dando per scontato che quella
 * parte sia stata ordinata, ma non è il caso, quindi finisce per produrre un array quasi ordinato ed è per questo che poi chiamiamo una wrapper function (insertion_sort su tutto l'array) per finire di ordinare,
 * ma le condizioni sono ideali dato che la insertion sort è efficiente con array quasi ordinati.
 */

namespace  alg {
    /* insertion sort con range */
    void insertion_sort(std::vector<int>& a, int l, int r) {
        for (int i = (l + 1); i != (r + 1); ++i) {
            int x = a.at(i);
            int j = i - 1;
            while (j > -1 && x < a.at(j)) {
                a[j + 1] = a[j];
                --j;
            }
            a[j + 1] = x;
        }
    }
    /* merge sort */
    void merge_with_insertion_(std::vector<int>& a, int l, int m, int r) {
        int size_one = m - l + 1;
        int size_two = r - m;
        std::vector<int> left, right;
        for(int i = l; i != (size_one + l); ++i) {
            left.push_back(a[i]);
        }
        for(int i = (m + 1); i != (size_two + m + 1); ++i) {
            right.push_back(a[i]);
        }
        left.push_back(std::numeric_limits<int>::max());
        right.push_back(std::numeric_limits<int>::max());

        int i, j;
        i = j = 0;
        for(int k = l; k <= r; ++k) {
            if (left.at(i) <= right.at(j)) {
                a[k] = left.at(i);
                i++;
            } else {
                a[k] = right.at(j);
                j++;
            }
        }

    }
    void merge_sort_with_insertion_(std::vector<int>& a, int l, int r) {
        // if ((r - l + 1) <= 25) { return insertion_sort(a, l, r); }
        if ((r - l + 1) <= 25) { return; }
        int m = l + (r - l) / 2;
        merge_sort_with_insertion_(a, l, m);
        merge_sort_with_insertion_(a, m + 1, r);
        merge_with_insertion_(a, l, m, r);
    }
    void merge_sort_with_insertion(std::vector<int>& a) {
        merge_sort_with_insertion_(a, 0, a.size() - 1);
        insertion_sort(a, 0, a.size() - 1); // wrapper function
    }
    /* quick sort */
    int partition_with_insertion_(std::vector<int>& a, int l, int r) {
        int x = a.at(r);
        int i = l;
        for (int j = l; j != r; j++) {
            if (a.at(j) <= x) {
                std::swap(a.at(i), a.at(j));
                i++;
            }
        }
        std::swap(a.at(i), a.at(r));
        return i;
        // da l a i non incluso ci sono gli elementi <= a x, da i a j non inlcuso ci sono gli elementi > di x, da j a r non incluso ci sono quelli ? e r è il pivot
    }
    void quick_sort_with_insertion_(std::vector<int>& a, int l, int r) {
        if ((r - l + 1) <= 25) { return insertion_sort(a, l, r); }
        // if ((r - l + 1) <= 25) { return; }
        int q = partition_with_insertion_(a, l, r);
        quick_sort_with_insertion_(a, l, q - 1);
        quick_sort_with_insertion_(a, q + 1, r);
    }
    void quick_sort_with_insertion(std::vector<int>& a) {
        quick_sort_with_insertion_(a, 0, a.size() - 1);
        // insertion_sort(a, 0, a.size() - 1); // wrapper function
    }
}

#endif //STRUTTURE_DATI_QUICK_E_MERGE_CON_INSERTION_HPP