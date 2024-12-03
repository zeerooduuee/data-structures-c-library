#ifndef STRUTTURE_DATI_TREE_ALBERI_BINARI_DI__RICERCA_HPP
#define STRUTTURE_DATI_TREE_ALBERI_BINARI_DI__RICERCA_HPP

/* alberi binari di ricerca */
/*  la definizione di un albero binario di ricerca è un albero binario che soddisfa la seguente proprietà di ricerca.
 *  proprietà di ricerca: sia x un nodo di un albero binario di ricerca. se y è un nodo nel sottoalbero sinistro di x, allora y.Key <= x.Key. se y è un nodo
 *  nel sottoalbero destro di x, allora y.Key >= x.Key.
 */
/*
 * la proprietà di ricerca consente di elencare in ordine non decrescente (crescente) le chiavi di un albero binario di ricerca visitando l’albero in ordine simmetrico (usando la visita simmetrica).
 */

#include <iostream>
#include <stdexcept>
#include <stack>
#include <queue>
#include <vector>

namespace ds {
    namespace sc {
        namespace search {
            template <typename T>
            // il tipo T deve supportare gli operatori ==, !=, <, <=, > e >=
            struct node {
                T key;
                node* padre;
                node* left;
                node* right;
            };

            template <typename T>
            class tree {
            private:
                node<T>* root;
                void clear_aux(node<T>* n) {
                    if(n) {
                        clear_aux(n->left);
                        clear_aux(n->right);
                        delete n;
                    }
                }
            public:
                tree() : root(nullptr) {}
                void clear() {
                    clear_aux(root);
                    root = nullptr;
                }
                ~tree() {
                    clear();
                }
                node<T>* padre(node<T>* n) const {
                    if(!n) {
                        throw std::logic_error("ERROR: 'padre' method call with empty pointer (node)");
                    }
                    return n->padre;
                }
                bool empty() const {
                    return !root;
                }
                /* ricerca (research) */
                // restituisce il nodo con la chiave k passata in parametro se presente, NIL altrimenti
                // versione ricorsiva
                node<T>* search_ricorsiva_aux(node<T>* n, T k) const {
                    if(!n || n->key == k) {
                        return n;
                    }
                    if(n->key > k) {
                        return search_ricorsiva_aux(n->left, k);
                    } else {
                        return search_ricorsiva_aux(n->right, k);
                    }
                }
                node<T>* search_ricorsiva(T k) const {
                    return search_ricorsiva_aux(root, k);
                }
                // versione iterativa
                node<T>* search_iterativa(T k) const {
                    node<T>* corrente = root;
                    while(corrente && corrente->key != k) {
                        if(corrente->key > k) {
                            corrente = corrente->left;
                        } else {
                            corrente = corrente->right;
                        }
                    }
                    return corrente;
                }
                /* massimo e minimo */
                // massimo restituisce il nodo con la chiave di valore piu alto e minimo quella di valore piu basso
                node<T>* massimo() const {
                    node<T>* corrente = root;
                    while(corrente->right) {
                        corrente = corrente->right;
                    }
                    return corrente;
                }
                node<T>* minimo() const {
                    node<T>* corrente = root;
                    while(corrente->left) {
                        corrente = corrente->left;
                    }
                    return corrente;
                }
                node<T>* massimo_parametro(node<T>* x) const {
                    if(!x) {
                        throw std::logic_error("ERROR: 'massimo_parametro' method call with empty pointer (node)");
                    }
                    node<T>* corrente = x;
                    while(corrente->right) {
                        corrente = corrente->right;
                    }
                    return corrente;
                }
                node<T>* minimo_parametro(node<T>* x) const {
                    if(!x) {
                        throw std::logic_error("ERROR: 'minimo_parametro' method call with empty pointer (node)");
                    }
                    node<T>* corrente = x;
                    while(corrente->left) {
                        corrente = corrente->left;
                    }
                    return corrente;
                }
                /* predecessore e successore */
                // successore
                /*
                 * in a binary search tree the successor operation aims to find a node that is bigger than the given node, but that has the minimum possible value among all the options,
                 * meaning that we want to find the lowest-key-value node that is also bigger than the given node. the name successor makes sense since we are looking for the "next" node as in ascending order.
                 * there's three possible scenarios:
                 * 1. the given node is already the biggest-key-value node, so we just return NIL
                 * 2. the given node has a right child, so we can just go right once (this one will have a bigger-key-value) and then go left all the way to find the smallest (we want to return the minimum node of the implicit
                 * tree rooted on the node's right child)
                 * 3. the given node doesn't have a right child, so we need to go up until we turn right the first time
                 */
                node<T>* successore(node<T>* x) const {
                    if(!x) {
                        throw std::logic_error("ERROR: 'successore' method call with empty pointer (node)");
                    }
                    if(x->right) {
                        return minimo_parametro(x->right);
                    }
                    node<T>* y = x->padre;
                    while(y && x == y->right) {
                        x = y;
                        y = y->padre;
                    }
                    return y;
                }
                // predecessore
                /*
                 * le casistiche e gli algoritmi relativi alla ricerca del predecessore di un nodo x appartenente ad un albero binario di ricerca sono analoghi a quelli di ricerca del successore, ma invertiti.
                 * se x ha un figlio sinistro, allora il predecessore sarà il massimo del sottoalbero sinistro di x, altrimenti sarà l’antenato più prossimo di x il cui
                 * figlio destro è anch’esso antenato di x. per trovarlo, si risale da x verso la radice fino a incontrare la prima svolta a sinistra.
                 * cioe in pratica il predecessore di un nodo e' il nodo "precedente" in ordine crescente di un certo nodo
                 */
                node<T>* predecessore(node<T>* x) const {
                    if(!x) {
                        throw std::logic_error("ERROR: 'successore' method call with empty pointer (node)");
                    }
                    if(x->left) {
                        return massimo_parametro(x->left);
                    }
                    node<T>* y = x->padre;
                    while(y && x == y->left) {
                        x = y;
                        y = y->padre;
                    }
                    return y;
                }
                /* inserimento e cancellazione */
                // insert
                /*
                 * dato un nodo z con chiave associata v, tale che z.Key = v e z.left = z.right = NIL, si vuole aggiungere il nodo ad un albero T, con attributo T.root, che contiene la radice dell'albero.
                 */
                // da notare che per uno stesso insieme di elementi si puo avere piu di una rappresentazione corrispondente in forma di albero binaro di ricerca che soddisfa le propieta
                /*
                 * se il nodo che si vuole aggiungere ha come chiave una gia presente, si possono fare tre cose:
                 * 1. non ggiungere il nodo, 2. spostarsi verso sinistra o 3. spostarsi verso destra
                 */
                void insert(T const& k) {
                    node<T>* nuovo_nodo = new node<T>{k, nullptr, nullptr, nullptr};
                    if(!root) {
                        root = nuovo_nodo;
                    } else {
                        node<T>* x = root;
                        node<T>* y = nullptr;
                        while(x) {
                            y = x;
                            if(x->key > k) {
                                x = x->left;
                            } else {
                                x = x->right;
                            }
                        }
                        nuovo_nodo->padre = y;
                        /*
                        if(!y) {
                            root = nuovo_nodo;
                            return;
                        }
                        */
                        if(y->key > k) {
                            y->left = nuovo_nodo;
                        } else {
                            y->right = nuovo_nodo;
                        }
                    }
                }
                // erase
                /*
                 * prima di fornire un’implementazione dell’algoritmo di cancellazione di un nodo da un albero binario di ricerca, è utile tenere a mente la seguente
                 * proprietà degli alberi binari di ricerca.
                 * se un nodo x in un albero binario di ricerca ha due figli, allora il suo successore non ha un figlio sinistro, e, in maniera analoga, il suo predecessore
                 * non ha un figlio destro.
                 */
                /*
                 * quando si vuole rimuovere un qualsiasi nodo z da un albero binario di ricerca ci si puo ritrovare in qualsiasi di questi tre casi:
                 * 1. se z non ha figli, modifichiamo suo padre (z.p) per sostituire z con NIL.
                 * 2. se z ha un unico figlio, stacchiamo z creando un collegamento "lungo" tra suo figlio e suo padre.
                 * 3. se z ha due figli, troviamo il successore y di z che deve trovarsi nel sottoalbero destro di z e facciamo in modo che y assuma la posizione di z nell’albero.
                 */
                // per spostare dei sottoalberi all’interno di un albero si usa la seguente procedura.
                /*
                 * la transpalant e un algoritmo che dato un albero (sul quale si vuole realizare l'operazione) e due nodi u e v (u appartenente all'albero),
                 * si vuole sostituire il sottoalbero con radice in u con il sottoalbero con radice in v.
                 */
                // da notare che su entrambe le implementazioni della transplant e la erase sarebbe da verificare che il nodo dato in parametro esista e che sia parte dell'albero sul quale si vuole fare la transplant o erase
                void transplant(node<T>* u, node<T>* v) {
                    if(!u->padre) {
                        root = v;
                    } else {
                        if(u->padre->left == u) { // u e' il figlio sinistro del padre
                            u->padre->left = v;
                        } else { // u e' il figlio destro del padre
                            u->padre->right = v;
                        }
                    }
                    if(v) {
                        v->padre = u->padre;
                    }
                }
                // ora facciamo la erase
                void erase(node<T>* x) {
                    if(!x->left) {
                        transplant(x, x->right);
                    } else {
                        if(!x->right) {
                            transplant(x, x->left);
                        } else {
                            node<T>* y = minimo_parametro(x->right);
                            if(y->padre != x) {
                                transplant(y, y->right);
                                y->right = x->right;
                                x->right->padre = y;
                            }
                            transplant(x,y);
                            y->left = x->left;
                            y->left->padre = y;
                        }
                    }
                    delete x;
                }
                /* costruzione di alberi binari di ricerca */
                /*
                 * le operazioni di ricerca di minimo, massimo, successore, predecessore, inserimento e cancellazione possono essere realizzate nel tempo O(h) in un
                 * albero binario di ricerca di altezza h. se l’albero è bilanciato, O(h) = O(log n). Quanto più un albero è sbilanciato, tanto più il tempo d’esecuzione dei suddetti algoritmi su di esso tenderà ad essere O(n).
                 * ma qual è la condizione che ci porta ad avere albero fortemente sbilanciato? supponiamo di avere un vettore di elementi strettamente crescenti o decrescenti che vogliamo
                 * trasformare in un albero binario di ricerca attraverso il seguente algoritmo.
                 */
                // questo algoritmo e' ok nel caso di un vettore casuale ma comunque e' sempre O(n2) dato che potrebbe che casualmente gli elementi sono ordinati e quindi creare un albero sbilanciato
                void build_bst(std::vector<T> const& w) {
                    for(int i = 0; i != w.size(); ++i) {
                        insert(w.at(i));
                    }
                }
                /*
                 * questo algoritmo avra tempo di esecuzione pari a O(n2), dato che nel peggiore dei casi dovremmo scorrere n elementi del vettore e per ogni elemento inserire questo nell'albero con tempo di esecuzione O(n),
                 * dato che nel caso di ricevere un vettore strettamente crescenete o dicrescente questo albero sara fortemente sbilanciato, questa cosa ovviamente porta svantaggi anche su future operazioni di ricerca
                 */
                // c'e comunque un modo di migliorare questo algoritmo, supponiamo sempre di avere un vettore completamente ordinato in modo crescente
                // per utilizzare questo algoritmo serve che l'insieme di elementi sia ordinato in modo (crescente o decrescente) da scegliere e da tempo di esecuzione O(logn)
                // nel caso ci venga dato un vettore casuale e' meglio ordinarlo e poi applicare questo algoritmo che quello precedente, dato che questo da tempo di esecuzione O(nlogn)
                node<T>* crea_bst_ottimizzato_aux(std::vector<T> const& w, int left, int right, node<T>* p) {
                    if(left > right) { return nullptr; }
                    int m = (left + right) / 2; // int m = left + (right - left) / 2;
                    node<T>* nuovo_nodo = new node<T>{w.at(m), p, nullptr, nullptr};
                    // nuovo_nodo->padre = p;
                    nuovo_nodo->left = crea_bst_ottimizzato_aux(w, left, m - 1, nuovo_nodo);
                    nuovo_nodo->right = crea_bst_ottimizzato_aux(w, m + 1, right, nuovo_nodo);
                    return nuovo_nodo;
                }
                void crea_bst_ottimizzato(std::vector<T> const& w) {
                    if(root) {
                        throw std::logic_error("ERROR: call on 'crea_bst_ottimizzato' on not empty tree");
                    }
                    root = crea_bst_ottimizzato_aux(w, 0, w.size() - 1, nullptr);
                }
            protected:
            };
        }
    }
}

#endif //STRUTTURE_DATI_TREE_ALBERI_BINARI_DI__RICERCA_HPP