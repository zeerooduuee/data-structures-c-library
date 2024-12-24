#ifndef STRUTTURE_DATI_BUBBLE_SORT_HPP
#define STRUTTURE_DATI_BUBBLE_SORT_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>

/* bubble sort */

/*
 * gli algoritmi di ordinamento possono essere progettati per avere logiche di ordinamento strettamente crescente, strettamente decrescente, crescente e decrescente, ma siccome la logica non cambia quasi niente, ma
 * sono solo delle piccole modifiche noi faremo algoritmi di ordinamento in ordine crescente.
 * un'altra cosa da notare e che si puo ordinare una qualunque struttura dati, sempre che il tipo di questa supporti gli operatori di confronto e una logica applicabile per distinguere un ordine, ma in questo caso
 * useremo interi per rendere tutto piu semplice.
 */

/*
 * l'algoritmo di ordinamento "bubble sort" è molto simile al algoritmo "insertion sort" visto che anche questo è di tipo sul posto con complessita spaziale di O(1) e complessita
 * computazionale di O(n) nel caso migliore (quando l'input è gia ordinato) e complessita nel caso peggiroe di O(n2) (quando l'input è ordinato in ordine inverso) quidni complessita dell'algoritmo sarebbe O(n2).
 */

// come l'insertion sort anche il bubble sort è consigliato per input di dimensioni ridotte

namespace alg {
    void bubble_sort(std::vector<int>& w) {
        bool swapped;

        for (int i = 0; i < w.size() - 1; ++i) {
            swapped = false;
            for (int j = 0; j < w.size() - i - 1; ++j) {
                if (w[j] > w[j + 1]) {
                    std::swap(w[j], w[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }

    void bubble_sort(std::list<int>& l) {
        if (l.empty() || l.size() == 1) { return; }

        auto end = l.end(); // auto sta per std::list<int>::iterator
        bool swapped;

        do {
            swapped = false;
            auto it = l.begin();

            while (std::next(it) != end) {
                if (*it > *std::next(it)) {
                    std::swap(*it, *std::next(it));
                    swapped = true;
                }
                ++it;
            }

            end = std::prev(end);
        } while(swapped);
    }
}

#endif //STRUTTURE_DATI_BUBBLE_SORT_HPP