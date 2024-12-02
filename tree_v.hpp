#ifndef STRUTTURE_DATI_TREE_V_HPP
#define STRUTTURE_DATI_TREE_V_HPP

/*
 * l’implementazione con gli array prevede l’utilizzo di vettore di coppie, che rappresentano i singoli nodi, rappresentati da delle coppie (info, parent),
 * contenenti rispettivamente l’informazione del nodo e l’indice del suo nodo padre.
 * gli n nodi dell'albero P vanno da 0 ad n - 1, P[v].info è il contenuto informativo, P[v].parent == u se e solo se vi è un arco (u, v) ∈ A, se v è la radice, P[v].parent == -1
 * P.length contiene il numero di nodi dell’albero
 */
/* questa implementazione supporta alberi generici ma non e' la migliore per alberi k-ari o binari */

#include <iostream>
#include <stdexcept>

namespace ds {
    namespace v {
        template <typename T>
        class tree {
        private:
            std::vector<std::pair<T, int>> a;
            /*
             * ogni elemento del vettore e' considerato un nodo, del quale si tiene traccia dell'indice (relativo alla posizine dentro il vettore), una certa informazione (data) di tipo T e un int che contiene
             * la posiszione dentro al vettore del nodo padre, per il nodo radice questo int e' -1
             */
        public:
            void add(T const& d, int p) {
                if(a.empty()) {
                    throw std::logic_error("ERROR: 'add' method call on empty tree, method 'add_root' should be called first");
                }
                if(p > (static_cast<int>(a.size()) - 1)) {
                    throw std::out_of_range("ERROR: on 'add' method call, p parameter doesn't point to any node");
                }
                a.push_back(std::make_pair(d, p)); // {d, p}
            }
            void add_root(T const& d) {
                if(!a.empty()) {
                    throw std::logic_error("ERROR: 'add_root' method call more than once");
                }
                a.emplace_back(d, -1);
            }
            /* v ∈ P e restituisce il padre di v se v è diverso dalla radice, NIL altrimenti. */
            int padre(int v) const {
                return a[v].second;
            }
            /* v ∈ P e restituisce una lista contenente i figli del nodo v.*/
            std::vector<int> figli(int v) const {
                std::vector<int> lista_figli;
                for(size_t i = 0; i != a.size(); ++i) {
                    if(a[i].second == v) {
                        lista_figli.push_back(i);
                    }
                }
                return lista_figli;
            }
            void clear() {
                a.clear();
            }
            tree& operator=(tree const& other) {
                if(this != &other) {
                    a = other.a;
                }
                return *this;
            }
            bool empty() const {
                return a.empty();
            }

        protected:
        };
    }
}

#endif //STRUTTURE_DATI_TREE_V_HPP