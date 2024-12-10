#ifndef STRUTTURE_DATI_ALGORITMO_INSERTION_SORT_HPP
#define STRUTTURE_DATI_ALGORITMO_INSERTION_SORT_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>

/* insertion sort */

/*
 * gli algoritmi di ordinamento possono essere progettati per avere logiche di ordinamento strettamente crescente, strettamente decrescente, crescente e decrescente, ma siccome la logica non cambia quasi niente, ma
 * sono solo delle piccole modifiche noi faremo algoritmi di ordinamento in ordine crescente.
 * un'altra cosa da notare e che si puo ordinare una qualunque struttura dati, sempre che il tipo di questa supporti gli operatori di confronto e una logica applicabile per distinguere un ordine, ma in questo caso
 * useremo interi per rendere tutto piu semplice.
 */

/*
 * l'algoritmo di ordinamento "insertion sort" e' di tipo in loco (sul posto o in-place) cioe che ha una complessita spaziale di O(1), questo
 * per che e' un algoritmo che usa una quantita costante di memoria per la sua impementazione (come alcune variabili ausiliari) a prescindere dell'input.
 * in altre parole ordina gli elementi direttamente all'interno della struttura dati fornita, senza richiedere spazio significativo per strutture aggiuntive.
 */

/*
 * vantaggi:
 * 1. sul posto
 * 2. si tratta di un metodo stabile, cioe i numeri che riceve in input con lo stesso valore si presentano nell’array di output nello stesso ordine in cui si trovano in quello di input.
 * 3. e' sensibile all’ordinamento dell’input, cioe se trova un elemento maggiore dell’array già ordinato, lo capisce e non va ad eseguire il ciclo interno.
 *
 * svantaggi:
 * la complessita dell'algoritmo e' O(n) nel caso migliore (quando l'input e' gia ordinato), ma O(n2) quando l'input e' ordinato in ordine inverso, per cio la complessita computazionale sarebbe O(n2)
 */

// detto questo di solito l'insertion sort viene usato come algoritmo per ordinare input di piccole dimensioni o come algoritmo ausiliario, altre opzioni come il merge sort o quick sort potrebbero essere piu efficienti

namespace alg {
    namespace v {
        void insertion_sort(std::vector<int>& w) {
            for(int i = 1; i != w.size(); ++i) {
                int key = w[i];
                int j = i - 1;
                while(j > -1 && key < w[j]) {
                    w[j + 1] = w[j];
                    --j;
                }
                w[j + 1] = key;
            }
        }
    }
    namespace l {
        /*
         * da notare che std::next e std::prev non modificano l'iteratore ma restituiscono uno successivo o precedente rispettivamente
         * e che l'operatore * sull'iteratori della std restituisce una reference del valore del elemento puntato dall'iteratore.
         * inoltre da considerare anche che questi algoritmi sono implementati sulla base della strttura dati completamente realizzata e con base alla interfaccia che questa espone, altrimenti
         * sarebbe da operare direttamente sulla strttura dati all'interno della sua implementazione
         */
        void insertion_sort(std::list<int>& l) {
            auto it_one = std::next(l.begin()); // auto sta per std::list<int>::iterator
            for (; it_one != l.end(); ++it_one) {
                int key = *it_one;
                auto it_two = std::prev(it_one); // auto sta per std::list<int>::iterator

                while (it_two != l.begin() && key < *it_two) { // it_two != l.begin() non guarda il primo elemento
                    *std::next(it_two) = *it_two;
                    it_two = std::prev(it_two);
                }

                if (key < *it_two) { // questo per verificare nel caso sia uscito senza controllare il primo lemento della lista
                    *std::next(it_two) = *it_two;
                    *it_two = key;
                } else {
                    *std::next(it_two) = key;
                }
            }
        }
    }
}

#endif //STRUTTURE_DATI_ALGORITMO_INSERTION_SORT_HPP