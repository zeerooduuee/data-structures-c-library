#ifndef STRUTTURE_DATI_HEAP_E_HEAP_SORT_HPP
#define STRUTTURE_DATI_HEAP_E_HEAP_SORT_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

/* heap (struttura dati) e heap sort (algoritmo di ordinamento) */

/*
 * come si puo vedere qui sotto l'heap puo essere visto come una struttura dati o semplicemente come l'idea di una struttura dati, che si implementa e mantiene tramite propieta e operazioni che forzano queste propieta
 * (in questo caso funzioni) che poi vengono sfruttate per algoritmi come quello della heap sort.
 * poi vabbe rispetto al tempo di esecuzione della heap sort, l'analisi della complessita è semplice xche sappiamo che la costruzione dell'heap è di O(n) e che poi l'operazione di maxheapify ha tempo di
 * esecuzione O(logn), per n-1 cicli e quindi risulta che il costo di questo algoritmo viene dato da t(n) = O(n) + O(nlogn) = O(nlogn).
 * questo ovviamente è un algoritmo di ordinamento molto efficiente e veloce che poi è anche sul posto. l'algoritmo della quick sort continua a essere piu veloce attraverso le diverse ottimizzazioni
 * nel caso medio ma questo è meglio nel caso peggiore.
 */

namespace alg {
    /* heap */
    /*
     * siccome l'heap sort sfruttera l'array in input per poter realizzare la procedura, in realta non serve implementare la struttura dati dell'heap ma lo facciamo tanto per avercela.
     */
    /*
     * l'heap è una struttura dati implementata come un albero binario (quindi con nodi di grado da 0 a 2) quasi completo (cioe tutti i livelli sono completi tranne eventualmente l'ultimo che potrebbe essere
     * completo oppure avere semplicemente tutte le foglie addossate a sinistra). l'heap è facilmente implementabile tramite un array posizionale, cosa che è utile per poi riciclarlo per l'heap sort sui vettori.
     * questo contendra due attributi A.size (numero di elementi, cioe dimensione, dell'array posizionale su cui è contenuto) e A.heap_size (numero di elementi dell'heap memorizzati in A), vale che
     * A.heap_size <= A.size
     * è importante ricordare che siccome l'implementazione si basa su un array posizionale allora i nodi saranno considerati indici, xche ogni indice (che punta ha un elemento dell'array) sara
     * un nodo dell'heap. da prendere in conto pure che la radice sara sempre nella prima posizione, cioe è il primo elemento dell'array (A[0] è la radice) mentre gli altri nodi saranno
     * nelle posizioni A[1 ... A.heap_size - 1].
     */
    /*
     * l'heap base sarebbe quello descritto qui sopra, comunque noi per usare l'heap per poi scrivere la procedura della heap sort useremo una variante di questo. queste varianti sono la max heap e la min heap
     * che sono opposte tra loro ma alla fine diccono la stessa cosa solo che al contrario. la max heap è sempre un heap come quello normale, l'unica cosa è che questo soddisfa una propieta che per ogni nodo i
     * dell'heap si ha che A[parent(i)] >= A[i], ovvero che per ogni nodo tutti i suoi figli sono piu piccoli o uguali a questo e quindi a sua volta i figli dei figli saranno piu piccoli dei padri e quindi
     * piu piccoli degli antenati e cosi via. una cosa molto importante è ricordare che la radice sara sempre il nodo piu grande dell'heap, poi vabbe la min heap è la stessa cosa ma inversa, quindi
     * ogni nodo i suoi figli sono piu piccoli o uguali a questo e cosi via ....
     * alcune propieta aggiuntive degli heap, anche quello normale sono che
     * 1. l'altezza di un heap di n elementi è ⌊logn⌋, dove ⌊ ⌋ rappresentano la funzione parte intera o floor
     * 2. se si implementa un heap di n elementi come un array posizionale allora le foglie saranno negli indici che vanno da ⌊n/2⌋, ⌊n/2⌋ + 1, ... , n - 1
     * 3. in un heap di altezza h e con n nodi, il numero massimo di nodi al livello h è ⌈n / 2^(h + 1)⌉, dove ⌈x⌉ (ceil o ceiling) indica il più piccolo numero intero che è maggiore o uguale a x, in altre parole, arrotonda per
     * eccesso al numero intero più vicino, se x è gia un numero intero, allora ⌈x⌉ = x
     */
    // useremo std::vector<int> come struttura dati di supporto, dove <int> xche il valore contenuto nei nodi saranno interi anche se potrebbero essere qualsiasi cosa e poi i figli e padri dei nodi saranno calcolati
    // usando e sfruttando di propieta dell'array posizionale
    // in questo caso andremo a implementare un max heap, ma comunque sappiamo che un min heap ha quasi la stessa identica logica e implementazione dietro, salvo per la cosa che questo a una propieta inversa a quella del max heap
    class heap {
    private:
        // int heap_size;
        // int size;
        std::vector<int> w; // in questo caso essendo che w è l'array che useremo per l'heap w.size() sara la dimensione di questo, quindi non serve un attributo size e neanche quello heap_size
    public:
        heap(std::vector<int>& a) : w(a) {} // dato che a sia un max heap
        /*
         * l'operazione padre per definizione prende un nodo x in input e ritorna il nodo padre del nodo x. siccome siamo su una implementazione che usa il vettore posizionale possiamo
         * sfruttare le sue propieta e trovare il padre di un nodo con una semplice formula che nel caso degli alberi binari sarebbe se il nodo è la radice quindi quello in indice 0 si ritorna -1 (come
         * valore default dato che comunque non si puo calcolare), altrimenti per un nodo y qualsiasi il padre di questo è ⌊(y - 1) / 2⌋, poi vabbe facciamo anche un controllo che l'input sia corretto.
         */
        int padre(int i) { // i è l'indice di un nodo che viene considerato il nodo stesso xche si puo leggere dentro al vettore
            if(i < 0 || i >= w.size()) {
                throw std::out_of_range("ERROR: node is not part of the heap");
            }
            if(i == 0) {
                return -1;
            }
            return ((i - 1) / 2); // floor(((i - 1) / 2));
        }
        /*
         * questa operazione per definizione ha il compito di ritornare il figlio sinitro di un qualsiasi nodo x dato in input, anche questa volta si puo fare applicando una semplice formula. in un heap implementato
         * con un array, i nodi sono memorizzati livello per livello, da sinistra a destra, con indici da 0 a n-1, dove n è il numero di nodi. e quindi se l'indice di un nodo padre è x, allora il suo figlio sinitro
         * sara in posizione 2x + 1
         */
        int sinistra(int i) { // figlio sinistro di nodo i
            if(i < 0 || i >= w.size()) {
                throw std::out_of_range("ERROR: node is not part of the heap");
            }
            if ((2 * i + 1) < w.size()) { return 2 * i + 1; }
            return -1;
        }
        /*
         * stessa cosa ma col figlio destro, e quindi per un nodo padre in posizione x il suo figlio destro è dato dalla formula 2x + 2
         */
        int destra(int i) { // figlio destro di nodo i
            if(i < 0 || i >= w.size()) {
                throw std::out_of_range("ERROR: node is not part of the heap");
            }
            if ((2 * i + 2) < w.size()) { return 2 * i + 2; }
            return -1;
        }
        // tutte queste operazioni hanno complessita Θ(1) xche sono eseguite in maniera istantanea, dato che si tratta unicamente di condizioni semplici e operazioni aritmetiche
        /*
         * max_heapify è una procedura che serve per mantenere la proprietà dei max_heap e metterli apposto. la pre-condizione è che gli alberi binari con radice in left(i) e right(i) siano max_heap e la post-condizione
         * sarebbe che l’albero radicato in i è un max_heap.
         * per quanto riguarda alla complessita di questo algoritmo, poiché un heap ha altezza ⌊logn⌋, se la procedura viene chiamata sulla radice, allora il suo tempo d’esecuzione è
         * Θ(logn), quindi il tempo d’esecuzione è O(h), dove h è l’altezza del nodo su cui chiamiamo la procedura, perché ad ogni chiamata ricorsiva scendiamo di un livello fino ai nodi foglia.
         */
        /*
        void max_heapify(int i) { // siccome stiamo lavorando su una classe non serve prendersi l'heap in input ma altrimenti servirebbe
            int l, r, massimo;
            l = sinistra(i);
            r = destra(i);
            if (l < w.size() && w[l] > w[i]) { // l < w.size() && w[l] > w[i], tutto questo si puo scrivere anche come l != -1 and w[l] > w[i]
                massimo = l;
            } else {
                massimo = i;
            }
            if (r < w.size() && w[r] > w[massimo]) {
                massimo = r;
            }
            if (i != massimo) { // se i fosse == a massimo allora vuol dire che l'heap era gia un max heap
                std::swap(w[i], w[massimo]);
                max_heapify(massimo);
            }
        }
        */
        // come prossima operazione ci sarebbe quella del costruttore di un max heap, ma siccome è un costruttore la faremo all'inizio
    protected:
    };
    /*
         * l'operazione padre per definizione prende un nodo x in input e ritorna il nodo padre del nodo x. siccome siamo su una implementazione che usa il vettore posizionale possiamo
         * sfruttare le sue propieta e trovare il padre di un nodo con una semplice formula che nel caso degli alberi binari sarebbe se il nodo è la radice quindi quello in indice 0 si ritorna -1 (come
         * valore default dato che comunque non si puo calcolare), altrimenti per un nodo y qualsiasi il padre di questo è ⌊(y - 1) / 2⌋, poi vabbe facciamo anche un controllo che l'input sia corretto.
         */
    int padre(std::vector<int>& a, int i) { // i è l'indice di un nodo che viene considerato il nodo stesso xche si puo leggere dentro al vettore
        if(i < 0 || i >= a.size()) {
            throw std::out_of_range("ERROR: node is not part of the heap");
        }
        if(i == 0) {
            return -1;
        }
        return ((i - 1) / 2); // floor(((i - 1) / 2));
    }
    /*
     * questa operazione per definizione ha il compito di ritornare il figlio sinitro di un qualsiasi nodo x dato in input, anche questa volta si puo fare applicando una semplice formula. in un heap implementato
     * con un array, i nodi sono memorizzati livello per livello, da sinistra a destra, con indici da 0 a n-1, dove n è il numero di nodi. e quindi se l'indice di un nodo padre è x, allora il suo figlio sinitro
     * sara in posizione 2x + 1
     */
    int sinistra(std::vector<int>& a, int i) { // figlio sinistro di nodo i
        if(i < 0 || i >= a.size()) {
            throw std::out_of_range("ERROR: node is not part of the heap");
        }
        if ((2 * i + 1) < a.size()) { return 2 * i + 1; }
        return -1;
    }
    /*
     * stessa cosa ma col figlio destro, e quindi per un nodo padre in posizione x il suo figlio destro è dato dalla formula 2x + 2
     */
    int destra(std::vector<int>& a, int i) { // figlio destro di nodo i
        if(i < 0 || i >= a.size()) {
            throw std::out_of_range("ERROR: node is not part of the heap");
        }
        if ((2 * i + 2) < a.size()) { return 2 * i + 2; }
        return -1;
    }
    // tutte queste operazioni hanno complessita Θ(1) xche sono eseguite in maniera istantanea, dato che si tratta unicamente di condizioni semplici e operazioni aritmetiche
    // max_heapify come ausiliare per il costruttore e come funzioni indipendenti
    void max_heapify(std::vector<int>& a, int heap_size, int i) { // siccome stiamo lavorando su una classe non serve prendersi l'heap in input ma altrimenti servirebbe
        int l, r, massimo;
        l = sinistra(a, i);
        r = destra(a, i);
        if ((0 <= l && l < heap_size) && a[l] > a[i]) { // l < a.size() && a[l] > a[i], tutto questo si puo scrivere anche come l != -1 and a[l] > a[i]
            massimo = l;
        } else {
            massimo = i;
        }
        if ((0 <= r && r < heap_size) && a[r] > a[massimo]) {
            massimo = r;
        }
        if (i != massimo) { // se i fosse == a massimo allora vuol dire che l'heap era gia un max heap
            std::swap(a[i], a[massimo]);
            max_heapify(a, heap_size, massimo);
        }
    }
    // costruttore di un max heap
    // dato un vettore disordinato, vogliamo trasformarlo in un max heap
    // non creiamo un max heap in base al vettore ma trasformiamo il vettore direttamente in un max heap
    void build_max_heap(std::vector<int>& a, int heap_size) {
        for(int i = ((a.size() / 2) - 1); i >= 0; --i) {
            max_heapify(a, heap_size, i);
        }
    }
    // osservazioni
    /*
     * una foglia è un max heap banale, detto questo, sappiamo che allora per tutti i nodi oltre (a.size() / 2) incluso, la propieta del max heap viene rispettata.
     * funziona xche noi stiamo chiamando max_heapify su tutti i nodi interni, partendo dall'ultimo (quello piu a destra non foglia nel livello piu basso), fino alla radice e per ognuno di questi, max_heapify
     * ci assicura che manteniamo l'heap come un max heap in radicato in quel nodo, sempre che i sotto alberi radicati nel figlio sinistro e destro siano max heap e poiche inziamo dall'ulitimo all'inizio
     * ci saranno solo mfoglie che rispettano la pre condizione e eventualmente a seconda che ci spostiamo verso l'alto comunque stiamo rispettando i sotto max heap.
     * la costruzione di un max-heap da un vettore disordinato usando l'algoritmo build_max_heap ha un tempo di esecuzione di O(n), non O(nlogn) come si potrebbe pensare a prima vista.
     */

    /* heap sort */
    /*
     * per prima cosa è importante notare una propieta degli heap con rispetto agli array. un array ordinato in modo non crescente (quindi decrescente) è sempre un max heap (nel senso che
     * sarebbe direttamente un array posizionale che puo essere letto come un max heap, sappiamo che con la buils un qualsiasi array ordinato o meno diventa un max heap), mentre un max heap, potrebbe essere
     * ma non è detto che lo sia, un max heap. questo xche è vero che un max heap contiene il nodo piu grande nella radice e che i figli sono piu piccoli di questo, ma poi chi va dopo tra sinsitro e destro?
     */
    /*
     * l'heap sort è un algoritmo di ordinamento, basato sul confronto, che usa l'heap (max heap o min heap dipendendo da che tipo di ordinamento si vuole) come supporto per la procedura.
     * in questo caso si vuole fare un heap sort con ordinamento crescente (per ordinamento crescente si usa max heap e per decrescente si usa min heap). l'algortimo inizia trasformando l'array in input
     * in un max heap, poi fa un ciclo for che va dall'ulitmo elemento dell'array da ordinare fino al primo non incluso, per ogni ciclo scambia l'elemento in prima posizione (indice 0) con
     * quello nel indice corrente, essendo che tutta la parte sinistra dall'indice in cui ci troviamo (con size heap_size) non incluso è un max heap, l'elemento in prima posizione sara sempre quello
     * piu grande e quindi per ogni ciclo ci portiamo il piu grande alla fine, anche se pero per ogni ciclo riduciamo la i di uno e quindi ci spostiamo e a destra della i avremmo la parte ordinata.
     * [max heap][i][parte ordinata], si va avanti cosi, per ogni ciclo dopo lo scambio si riduce di uno l'heap_size, per escludere il nuovo elemento che fa gia parte della porzione ordinata dalla porzione dell'max heap
     * e poi si richiama max_heapify che mantiene la propieta e sistema il max heap per poi andare avanti, max heap si chiama nella posizione 0 (radice) dato che abbiamo scambiato li, ma comunque rimane
     * che i sotto alberi radicati sui figli sono max heap (anche xche abbiamo escluso quello scambiato). l'ultimo elemento (quello dell'inizio) non serve guardarlo xche tanto sara quello rimasto alla fine e
     * per cio il piu piccolo.
     */
    void heap_sort(std::vector<int>& a) {
        int heap_size = a.size();
        build_max_heap(a, heap_size);
        for(int i = (a.size() - 1); i > 0; --i) {
            std::swap(a[0], a[i]);
            --heap_size;
            max_heapify(a, heap_size, 0);
        }
    }
}



#endif //STRUTTURE_DATI_HEAP_E_HEAP_SORT_HPP