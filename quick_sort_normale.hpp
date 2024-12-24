#ifndef STRUTTURE_DATI_QUICK_SORT_NORMALE_HPP
#define STRUTTURE_DATI_QUICK_SORT_NORMALE_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>

/* quick sort a due vie (two-way quick sort) */
/* quick sort (normale) */ // variante standard con pivot sempre il primo o ultimo elemento e senza considerare piu occorrenze

/*
 * si tratta di un algoritmo di ordinamento basato sulla tecnica del divide et impera. serve per ordinare un vettore A[p ... r], in cui inizialmente p = 1 e r = A.length.
 * passi dell’algoritmo sarebbero divide che nel merge_ sort era banale perché andava a prendere l’indice dell’elemento in mezzo all’array, mentre ora fa un’operazione diversa. il quick
 * sort partiziona l’array di partenza A[p ... r] in due sottoarray A[p ... q - 1] e A[q + 1 ... r], due partizioni che possono essere eventualmente vuote e in cui,
 * appunto, l’elemento alla posizione q non è compreso. queste partizioni sono tali che ogni elemento di A[p ... q - 1] è minore o uguale a A[q] che a sua volta è minore o uguale ad ogni elemento di A[q + 1 ... r].
 * l’indice q è il risultato di questa procedura di partizionamento e l’elemento A[q] è chiamato pivot. poi c'è impera, ordino i due sottoarray A[p ... q - 1] e A[q + 1 ... r]
 * chiamando ricorsivamente la procedura quicksort. se il problema è sufficientemente piccolo si risolve direttamente. e l'ultimo step è combina, questo è triviale, poiché i sottoarray
 * sono ordinati sul posto, non occorre altro lavoro per combinarli. L’intero array A[p ... r] è ordinato.
 */
/*
 * da notare che l'implementazione per i vettori (array) è quella piu standard, mentre quella per le liste è una variante che si puo usare ma non sono sicuro sia completamente 1:1
 */
/*
 * comunque come piccola spiegazione piu semplice, che magari è piu utile
 */
/*
 * vantaggi:
 * 1. è un algoritmo di ordinamento in loco (sul posto o in-place).
 * svantaggi:
 * in realta ci sono diversi svantaggi e sono tutti dovuti alla complessita e ai casi in qui questa si presenta
 * complessita nel caso migliore: Θ(nlogn), questo si presenta quando il pivot riesce sempre a dividere la strttura dati in due sotto strutture perfettamente bilanciate (quindi meta degli elementi da una parte e meta dall'altra)
 * con dimensione n/2.
 * complessita nel caso medio: Θ(nlogn), simile alla complessita nel caso migliore. si presenta quando il pivot scelto divide l'array in due sotto-array di dimensione abbastanza bilanciata, ad esempio 40%-60% o 30%-70%.
 * e quindi se il pivot riesce a dividere l'array in modo abbastanza bilanciato (anche approssimativamente) la ricorsione diventa T(n) = 2T(n/2) + O(n) e questa di nuovo diventa Θ(nlogn).
 * complessita nel caso peggiore: Θ(n2) si verifica quando il pivot scelto è sempre il minimo o il massimo elemento del vettore.
 * questo accade se l'array è già ordinato (crescente o decrescente) e il pivot viene scelto sempre come primo o ultimo elemento. o se tutti gli elementi del vettore sono occorrenze dello stesso elemento.
 * come la merge sort e diverso dal bubble sort o insertion sort, il quick sort non ha modo di sapere se la struttura in input è ordinata o meno, quindi la procedura continua
 * fino a non finire la ricorsione piuttosto che uscire appena ordinato la struttura dati.
 * se siamo nel caso peggiore e semplice capire che l'algoritmo per ogni volta che viene eseguito non divide l'array in modo bilanciato, lasciando uno dei due sotto-array vuoto e l'altro di dimensione n - 1
 * e questo si ripetera n volte dato che per ogni volta togliamo un unico elemento e comunque la ricorsione diventa T(n) = T(n - 1) + O(n) che poi risulta in una quadratica
 *
 * ma allora xche viene usato cosi tanto e considerato uno dei piu veloci specialmente in input di grandi dimensioni?
 * il caso peggiore si verifica solo in situazioni molto specifiche (come array già ordinati o ordinati al contrario o tutti elementi uguali) e quindi dato che il caso peggiore e raro
 * per il resto dei casi sara molto efficiente, tanto quanto la merge_ sort? assintoticamente parlando si, ma in pratica, ancora piu veloce.
 * notare che il tempo di esecuzione dell'algoritmo si basa completamente sulla divisione bilanciata della struttura dati in due sotto strutture, quindi è importante
 * dove riesce a posizionarsi il pivot tra gli elementi, ma noi non abbiamo controllo di questo e quindi l'obbiettivo è quello di rendere il pivot il meno propenso possibile a essere in un caso dove si trovi sugli estremi
 * e quindi separi le sotto strutture in modo molto sbilanciato.
 */
// comunque sia ci sono diverse ottimizzazioni che si possono fare sia sulla merge_ sort che il quick sort, per ora concentriamoci su risolvere
// il problema del caso peggiore sul quick sort, usando la variante della quick sort randomizzata (altro file e comunque da ora in poi implementazione solo su vettori).

namespace alg {
    int partition_(std::vector<int>& a, int l, int r) {
        int x = a.at(r); // per noi il pivot sara l'ultimo elemento, tra l'altro non usare a.back() o a.at(a.size() - 1), per che ci serve l'ultimo elemento dello spazio limitato non quello di tutta la struttura dati;
        // int i = l - 1;
        int i = l;
        for(int j = l; j != r; ++j) {
            if(a.at(j) <= x) {
                // ++i;
                // std::swap(a.at(i), a.at(j));
                std::swap(a.at(i), a.at(j));
                i++;
            }
        }
        // std::swap(a.at(i + 1), a.at(r));
        // return ++i;
        std::swap(a.at(i), a.at(r));
        return i;
    }
    void quick_sort_(std::vector<int>& a, int l, int r) {
        /*
        if (l >= r) {
            return;
        }
        ...
        */
        if (l < r) {
            int q = partition_(a, l, r);
            quick_sort_(a, l, q - 1);
            quick_sort_(a, q + 1, r);
        }
    }
    void quick_sort(std::vector<int>& a) {
        quick_sort_(a, 0, a.size() - 1);
    }

    std::list<int>::iterator partition(std::list<int>& a, std::list<int>::iterator l, std::list<int>::iterator r) {
        int x = *r;
        auto it_one = l;
        for(auto it_two = l; it_two != r; ++it_two) {
            if (*it_two <= x) {
                std::swap(*it_one, *it_two);
                it_one++;
            }
        }
        std::swap(*it_one, *r);
        return it_one;
    }
    void quick_sort(std::list<int>& a) {
        if (a.size() <= 1) { return; } // la lista è vuota o gia ordianta
        std::list<int> l, r;
        auto it_pivot = partition(a, a.begin(), std::prev(a.end()));
        l.splice(l.begin(), a, a.begin(), it_pivot);
        r.splice(r.begin(), a, std::next(a.begin()), a.end()); // std::next(a.begin()) sarebbe std::next(it_pivot) ma dato che si usa move scemantics facciamo cosi
        quick_sort(l);
        quick_sort(r);

        int pivot = *it_pivot;
        a.clear();
        a.splice(a.end(), l);
        a.push_back(pivot); // a.insert(a.end(), pivot);
        a.splice(a.end(), r);
    }
}

#endif //STRUTTURE_DATI_QUICK_SORT_NORMALE_HPP