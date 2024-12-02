#ifndef STRUTTURE_DATI_TREE_PUNTATORI_AI_FIGLI_HPP
#define STRUTTURE_DATI_TREE_PUNTATORI_AI_FIGLI_HPP

/*
 * alberi implementati con strutture collegate si possono rappresentare facilmente attraverso la definizione di un record che contiene:
 * l’informazione associata al nodo, un puntatore al padre e altri puntatori (per accedere ai figli)
 */
/*
 * puntatori ai figli
 * assunzione: se ogni nodo ha grado al più k, possiamo mantenere in ogni nodo un puntatore a ciascuno dei possibili k figli. supponendo un albero binario (k = 2), ogni nodo x dell’albero avrà:
 * x.p: puntatore al padre, x.left: puntatore al figlio sinistro, x.right: puntatore al figlio destro e x.key: contiene l’informazione del nodo
 * definiamo un albero T avente come campo T.root, un puntatore alla radice dell’albero.
 */

#include <iostream>
#include <stdexcept>
#include <stack>
#include <queue>

template <typename T>
struct record {
    T data;
    record* p;
    record* left;
    // record* center;
    record* right;
};

namespace ds {
    namespace sc {
        namespace pf {
            template <typename T>
            class tree {
            private:
                record<T>* root;
                void clear_aux(record<T>* v) {
                    if(v) {
                        clear_aux(v->left);
                        clear_aux(v->right);
                        delete v;
                    }
                }
                void add_BFS(T const& d) {
                    std::queue<record<T>*> q;
                    q.push(root);
                    while(!q.empty()) {
                        record<T>* node = q.front();
                        q.pop();
                        if(node) {
                            if(!node->left) {
                                node->left = new record<T>{d, node, nullptr, nullptr};
                                return;
                            } else if(!node->right) {
                                node->right = new record<T>{d, node, nullptr, nullptr};
                                return;
                            }
                            q.push(node->left);
                            q.push(node->right);
                        }
                    }
                }
            public:
                tree() : root(nullptr) {}
                // implementata molto bene con la visita ricorsiva post ordine
                void clear() {
                    clear_aux(root);
                    root = nullptr;
                }
                ~tree() {
                    clear();
                }
                /* algoritmi di visita di alberi */
                /* visita generica */
                /*
                 * 1 visitaGenerica (Node r)
                 * 2    S = {r}
                 * 3    while S != emptySet
                 * 4        estrai un nodo n da S
                 * 5        visita il nodo n
                 * 6        S = S U {figli di n}
                 * l’algoritmo di visita applicato alla radice di un albero con n nodi termina in O(n) iterazioni. Lo spazio utilizzato è O(n).
                 * l'idea e' quella di poi tradurre queste visite ad alberi diversi anche generici con nodi x di grado arbitrario
                 */
                /* visita in profondità - Depth-First Search (DFS) */
                /*
                 * per questo algoritmo faremo uso di una struttura dati a pila/stack S, dotata di politica LIFO.
                 * versione non ricorsiva.
                 */
                // per gli algoritmi di visita implementati con stack o queue non e' del tutto importante quando avviene la visita, se prima o dopo le push, ma dipendendo dallo scopo potrebbe essere relevante (tipo per i distruttori)
                // volendo si puo dare come parametro il nodo (radice indotta) da cui comincare la visita, ma in questo caso faremmo dalla root
                void visitaDFS_stack() {
                    std::stack<record<T>*> s;
                    s.push(root);
                    while(!s.empty()) {
                        record<T>* node = s.top();
                        s.pop();
                        if(node) {
                            // visita
                            s.push(node->right);
                            s.push(node->left);
                        }
                    }
                }
                /* versioni ricorsive della DFS */
                /*
                 * 1 visitaDFS_rec(Node r)
                 * 2    if r != NIL
                 * 3        visita il nodo r
                 * 4        visitaDFS_rec (r.left)
                 * 5        visitaDFS_rec (r.right)
                 */
                // non credo che tutte siano applicabili per un qualsiasi albero, penso che si prestano di piu agli alberi binari
                // visita in preordine (anticipata)
                // si visita prima la radice, poi si fa una chiamata ricorsiva sul figlio sinistro e poi sul figlio destro.
                void visitaDFS_rec_preordine(record<T>* v) {
                    if(v) {
                        // visita il nodo v
                        visitaDFS_rec_preordine(v->left);
                        visitaDFS_rec_preordine(v->right);
                    }
                }
                // solo per mostrare come si dovrebbe fare con encapsulation
                void setup_visitaDFS_rec_preordine() {
                    visitaDFS_rec_preordine(root);
                }
                // visita simmetrica (in order)
                // prima si effettua la chiamata ricorsiva sul figlio sinistro, poi si visita la radice, infine si fa la chiamata ricorsiva sul figlio destro.
                void visitaDFS_rec_simmetrica(record<T>* v) {
                    if(v) {
                        visitaDFS_rec_preordine(v->left);
                        // visita il nodo v
                        visitaDFS_rec_preordine(v->right);
                    }
                }
                // visita in postordine (posticipata)
                // si effettuano prima le chiamate ricorsive sul figlio sinistro e sul figlio destro, poi si visita la radice.
                void visitaDFS_rec_postordine(record<T>* v) {
                    if(v) {
                        visitaDFS_rec_preordine(v->left);
                        visitaDFS_rec_preordine(v->right);
                        // visita il nodo v
                    }
                }
                /* visita in ampiezza - Breadth-First Search (BFS) */
                /*
                 * la visita in ampiezza, altrimenti detta Breadth-First Search, è un algoritmo che permette di visitare tutti i nodi presenti alla corrente profondità di un albero
                 * prima di scendere a visitare i nodi delle profondità inferiori. per questo algoritmo faremo uso di una struttura dati a coda/queue C, dotata di politica FIFO.
                 * questa non prevede versione ricorsiva e neanche preordine, simmetrica e postordine.
                 */
                // .push() sarebbe .enque() e .front() con .pop() sarebbe .deque()
                void visitaBFS() {
                    std::queue<record<T>*> q;
                    q.push(root);
                    while(!q.empty()) {
                        record<T>* node = q.front();
                        q.pop();
                        if(node) {
                            // visita
                            q.push(node->left);
                            q.push(node->right);
                        }
                    }
                }
                void add(T const& d) {
                    if(!root) {
                        root = new record<T>{d, nullptr, nullptr, nullptr};
                        return;
                    }
                    add_BFS(d);
                }
                record<T>* padre(record<T>* v) const {
                    return v->p;
                }
                std::vector<record<T>*> figli(record<T>* v) const {
                    std::vector<record<T>*> a;
                    if(v->left) {
                        a.push_back(v->left);
                    }
                    if(v->right) {
                        a.push_back(v->right);
                    }
                    return a;
                }
                bool empty() const {
                    return !root;
                }
            protected:
            };
        }
    }
}

#endif //STRUTTURE_DATI_TREE_PUNTATORI_AI_FIGLI_HPP