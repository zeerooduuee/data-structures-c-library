#ifndef STRUTTURE_DATI_TREE_VETTORE_POSIZIONALE_HPP
#define STRUTTURE_DATI_TREE_VETTORE_POSIZIONALE_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

/* albero implementato con vettore posizionale */
/*
 *  per questa rappresentazione, supponiamo di avere un albero k-ario con k ≥ 2, ogni nodo del quale ha una posizione prestabilita nella struttura.
 *  sia T = (N, A) un albero k-ario completo, w è un vettore di dimensione n tale che w[v] contiene l’informazione associata al nodo v e i nodi vengono considerati
 *  indici interi che poi sono letti all'interno del vettore w.
 */
// 0 e' la posizione della radice
// l’i-esimo figlio di v è in posizione k · v + 1 + i, i ∈ {0, . . . , k − 1}, primo filgio e' i = 0, secondo i = 1 e cosi
// il padre del nodo f, f  != 0, è in posizione (f - 1) / k, cioe questo ci da la posizione del nodo padre del nodo f

namespace ds {
    namespace v {
        namespace posizionale {
            template <typename T>
            class tree {
            private:
                std::vector<T> w;
                int k; // contiene il grado di tutti i nodi, cioe il grado k-ario dell'albero
            public:
                tree(int k) : k(k) {}
                void add(T const& data) {
                    w.push_back(data);
                    /*
                     * pero e' da considerarsi un vettore dove ogni livello dell'albero deve essere completo
                     * per cio se k = 3
                     * se si aggiunge un elemento pos = 0, allora questo e' la radice, ma poi se si vuole aggiungere nuovamente allora ne servono 3 e da pos = 1 fino a  pos = 3 saranno quelli a livello 1 e poi 9 e coso per che sia completo
                     */
                }
                void clear() {
                    w.clear();
                }
                bool empty() const {
                    return w.empty();
                }
                size_t size() const {
                    return w.size();
                }
                int padre(int x) const {
                    if(x < 0 || x >= w.size()) {
                        throw std::out_of_range("ERROR: node is not part of the tree");
                    }
                    if(x == 0) {
                        return -1;
                    }
                    return ((x - 1) / k); // floor(((x - 1) / k));
                }
                std::vector<int> figli(int x) const{
                    if(x < 0 || x >= w.size()) {
                        throw std::out_of_range("ERROR: node is not part of the tree");
                    }
                    std::vector<int> v;
                    if((x * k + 1) >= w.size()) {
                        return v;
                    }
                    for(int i = 0; i != k; ++i) {
                        v.push_back(w.at(x * k + 1 + i));
                    }
                    return v;
                }
            protected:
            };
        }
    }
}

#endif //STRUTTURE_DATI_TREE_VETTORE_POSIZIONALE_HPP
