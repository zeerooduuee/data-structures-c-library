#ifndef STRUTTURE_DATI_BINARY_SEARCH_HPP
#define STRUTTURE_DATI_BINARY_SEARCH_HPP

/*
 * la binary search (ricerca binaria) e' una funzione di ricerca su vettori ordinati (strutture dati lineari con accesso diretto tramite indice e ordinate)
 * per trovare se un certo elemento e' presente in complessita O(logn).
 * la pre condizione per l'utilizzo di una qualsiasi binary search e' che il vettore sia ordinato in modo crescente o dicrescente
 * (dipendendo cambia l'implementazione) e ci sono diverse varianti di questo. la binary search di solito restituisce un bool, true se la chiave era presente nel vettore o false altrimenti, o direttamente
 * la posizione di un qualunque elemento che matcha la chiave o throwa una eccezione in caso di chiave non presente.
 */

#include <iostream>
#include <vector>

// a modo di fare le cose piu semplici lavoreremo con un vettore di interi, anche se ovviamente potrebbe essere di tipo generico T
// molto importante ricordarsi che in c++ il cast da double a int e' verso il basso sempre, cio vuol dire che qualcosa tipo int x = 0.75; diventa x = 0; dato che il valore viene troncato e la parte decimale eliminata
// assumiamo che l'ordine del vettore e' ascending

/* basic search */
int basic_search(std::vector<int> const& w, int k) {
    for(int i = 0; i != w.size(); ++i) {
        if(k == w.at(i)) {
            return i;
        }
    }
    return -1;
}

/* binary search ricorsiva */
// funzione di setup (solita cosa sulle funzioni ricorsive, dove una funzione fa il setup e gestisce le piccole cose) ma poi la risoluzione del problema avviene nella funzione ricorsiva ausiliare
int search_ricorsiva_aux(std::vector<int> const& w, int k, int left, int right) {
    if(left > right) { return -1; }
    int mid = left + (right - left) / 2;
    if(w.at(mid) == k) { return mid; }
    if(w.at(mid) > k) { return search_ricorsiva_aux(w, k, left, mid - 1); }
    else { return search_ricorsiva_aux(w, k, mid + 1, right); }
}
int search_ricorsiva(std::vector<int> const& w, int k) {
    return search_ricorsiva_aux(w, k, 0, w.size() - 1);
}


/* binary search iterativa */
int search_iterativa(std::vector<int> const& w, int k) {
    int left = 0;
    int right = w.size() -1;
    while(left <= right) {
        int mid = left + (right - left) / 2; // (left + right) / 2 ma per evitare overflow si fa quello scritto a sinistra
        if(w.at(mid) == k) {
            return mid;
        }
        if(w.at(mid) > k) { // ci spostiamo a sinistra
            right = mid - 1;
        } else { // ci spostiamo a destra
            left = mid + 1;
        }
    }
    return -1;
}

/*
 * nel caso si ha vettori ordinati ma con ripetizione delgi elementi all'interno, essendo che questi sono in ordine allora gli elementi ripetuti saranno uno dietro l'altro
 */
// queste potrebbero essere sia ricorsive che iterative, ma faro le iterative
/* left-most binary search */
int left_most_search(std::vector<int> const& w, int k) {
    int left = 0;
    int right = w.size() -1;
    int result = -1;
    while(left <= right) {
        int mid = left + (right - left) / 2; // (left + right) / 2 ma per evitare overflow si fa quello scritto a sinistra
        if(w.at(mid) == k) {
            right = mid - 1;
            result = mid;
        } else if(w.at(mid) > k) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return result;
}

/* right-most binary search */
int right_most_search(std::vector<int> const& w, int k) {
    int left = 0;
    int right = w.size() -1;
    int result = -1;
    while(left <= right) {
        int mid = left + (right - left) / 2; // (left + right) / 2 ma per evitare overflow si fa quello scritto a sinistra
        if(w.at(mid) == k) {
            left = mid + 1;
            result = mid;
        } else if(w.at(mid) > k) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return result;
}

/* number of occurences */
int num_occurences(std::vector<int> const& w, int k) {
    int left = left_most_search(w, k);
    if(left == -1) {
        return 0;
    }
    int right = right_most_search(w, k);
    return (right - left + 1);
}

#endif //STRUTTURE_DATI_BINARY_SEARCH_HPP
