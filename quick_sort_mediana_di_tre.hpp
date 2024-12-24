#ifndef STRUTTURE_DATI_QUICK_SORT_MEDIANA_DI_TRE_HPP
#define STRUTTURE_DATI_QUICK_SORT_MEDIANA_DI_TRE_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

/* quick sort a due vie (two-way quick sort) */
/* quick sort con pivot come mediana di tre elementi */

/*
 * cioe alla fine questa idea di scegliere il pivot come mediana di 3 numeri sfrutta la partition normale (che prende come pivot sempre l'ultimo elemento) ma modifica l'array
 * in modo di mettere come ultimo elemento propio quello calcolato come la mediana di 3 numeri, che comunque è la stessa cosa che fa la versione randomizzata della quick sort e infatti poi si puo
 * decidere in modo semplice di volere usare la quick sort a due o tre vie con un veloce cambio della funzione partition in chiamata e vabbe del come ci prendiamo l'indici per la ricorsione.
 * l'idea della mediana di 3 numeri è quella di dire se l'array (al momento della partition, cioe calcolo del pivot in questo caso) ha almeno 3 elementi allora prendiamo il primo elemento, l'ultimo elemento e quello
 * che si trova in un indice a meta, poi per definizione della mediana (elemento al 50% della distribuzione in un set di elementi ordinati in modo crescente) allora ordiniamo questi 3 elementi in modo crescente, ma
 * per mantenere l'algoritmo sul posto lo facciamo diretto nel sotto'array (che comunque è da ordinare quindi non importa se spostiamo cose) e poi una volta sono in modo crescente è ovvio che quello in posizione
 * m (l'elemento centrale) è la mediana, quindi c'è lo portiamo in ultima posizione. se invece l'array ha soli 2 elementi, allora scegliamo o il piu piccolo o il piu grande e lo mettiamo in ultima posizione.
 * poi una volta che l'array è stato modificato allora chiamiamo la partition_ normale, casi di array con 0 o 1 elemento non ci possono essere.
 * i vantaggi di questo metodo sono che la mediana di questi 3 numeri aumenta la probabilita di essere piu vicini all'elemento centrale (in ordine) dell'array e quindi a creare partizioni piu bilanciate. in piu riduce
 * le possibilita di finire nel caso peggiore e comunque aggiunge meno overhead rispetto alla rand() cosa che aiuta in array di grandi dimensioni.
 */

namespace alg {
    int partition_mediana_(std::vector<int>& a, int l, int r) {
        int m = l + (r - l) / 2; // l indice di sinistra, r destra e m mezzo
        if ((r - l + 1) > 2) { // ci sono almeno 3 elementi
            // riordiniamo i 3 elementi in ordine crescente e poi mettiamo l'elemento in posizione m nella posizione dell'ultimo elemento
            if (a.at(l) > a.at(m)) { std::swap(a.at(l), a.at(m)); }
            if (a.at(l) > a.at(r)) { std::swap(a.at(l), a.at(r)); }
            if (a.at(m) > a.at(r)) { std::swap(a.at(m), a.at(r)); }
            std::swap(a.at(m), a.at(r));
        } else if ((r - l + 1) == 2) { // ci sono 2 elementi
            if (a.at(l) < a.at(r)) { std::swap(a.at(l), a.at(r)); }
        }
        return partition_(a, l, r);
        /*
         * l'idea è quella di chiamare alla fine xche tanto sfrutteremo la partition della normale a due vie per realizzare la procedura, ma questa funzione serve solo a
         * modificare l'array in modo che per quando si chiama la partition_ normale e questa vada a prendersi come pivot l'ultimo elemento, questo è gia stato modificato
         * e ora l'ultimo elemento è il risultato di questa funzione (quindi la mediana tra l'ultimo elemento, il primo e quello di mezzo).
         * comunque non serve preoccuparsi per il caso di 1 o 0 elementi xche tanto questa funzione non vendra chiamata in questi casi, x l'if della quick sort e comunque mettiamo la chiamata alla fine
         * siccome questa è condivisa per entrambi i casi scritti qui sopra
         */
    }
    void quick_sort_mediana_(std::vector<int>& a, int l, int r) {
        if (l < r) {
            int q = partition_mediana_(a, l, r);
            quick_sort_mediana_(a, l, q - 1);
            quick_sort_mediana_(a, q + 1, r);
        }
    }
    void quick_sort_mediana(std::vector<int>& a) {
        quick_sort_mediana_(a, 0, a.size() - 1);
    }
}

#endif //STRUTTURE_DATI_QUICK_SORT_MEDIANA_DI_TRE_HPP