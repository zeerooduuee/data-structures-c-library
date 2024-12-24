#ifndef STRUTTURE_DATI_TREE_FIGLIO_SINISTRO_FRATELLO_DESTRO_HPP
#define STRUTTURE_DATI_TREE_FIGLIO_SINISTRO_FRATELLO_DESTRO_HPP

/*
 * figlio sinistro e fratello destro
 * ogni nodo x di questa rappresentazione ha:
 * x.Key: contiene l’informazione del nodo.
 * x.p: puntatore al padre.
 * x.left_child: puntatore al figlio più a sinistra di x; se vale NIL, x è un nodo foglia.
 * x.right_sib: puntatore al fratello di x immediatamente alla sua destra; se vale NIL, è il figlio più a destra di suo padre.
 */

#include <iostream>
#include <stdexcept>
#include <stack>
#include <queue>

namespace sd {
    namespace sc {
        namespace fsfd {
            template <typename T>
            struct node {
                T key;
                node* parent;
                node* left_child;
                node* right_sibling;
                node(T const& key) : key(key), parent(nullptr), left_child(nullptr), right_sibling(nullptr) {}
            };
            template <typename T>
            class tree {
            private:
                node<T>* root;
                void clear_aux(node<T>* x) {
                    if(x) {
                        clear_aux(x->left_child);
                        clear_aux(x->right_sibling);
                        delete x;
                    }
                }
            public:
                tree() : root(nullptr) {}
                tree(T const& key) {
                    root = new node(key);
                }
                void clear() {
                    clear_aux(root);
                }
                ~tree() {
                    clear();
                }
                node<T>* padre(node<T>* n) {
                    if(!n) {
                        throw std::logic_error("ERROR: 'padre' method call with empty pointer (node)");
                    }
                    return n->parent;
                }
                std::vector<node<T>*> figli(node<T>* n) {
                    if(!n) {
                        throw std::logic_error("ERROR: 'figli' method call with empty pointer (node)");
                    }
                    std::vector<node<T>*> figli;
                    node<T>* current = n->left_child;
                    while(current) {
                        figli.push_back(current);
                        current = current->right_sibling;
                    }
                    return figli;
                }
                node<T>* get_root() const {
                    return root;
                }
                void add(T const& key, node<T>* n) {
                    if(!n) {
                        throw std::logic_error("ERROR: 'add' method call with empty pointer (node)");
                    }
                    if(!(n->left_child)) {
                        n->left_child = new node(key);
                        n->left_child->parent = n;
                    } else {
                        /*
                        node<T>* current = n;
                        while(current->right_sibling) {
                            current = current->right_sibling;
                        }
                        current->right_sibling = new node(key);
                        current->right_sibling->parent = n;
                        */
                        node<T>* temp = n->left_child;
                        n->left_child = new node(key);
                        n->left_child->parent = n;
                        n->left_child->right_sibling = temp;
                    }
                }
                /* visite */
                // DFS
                // stack
                void visita_dfs_stack() const {
                    std::stack<node<T>*> s;
                    s.push(root);
                    while(!s.empty()) {
                        node<T>* nodo = s.top();
                        s.pop();
                        if(nodo) {
                            // visita
                            node<T>* corrente = nodo->left_child;
                            while(corrente) {
                                s.push(corrente);
                                corrente = corrente->right_sibling;
                            }
                        }
                    }
                }
                // preordine (anticipata)
                void visita_ricorsiva_dfs_pre_aux_while(node<T>* n) {
                    if(n) {
                        // visita
                        node<T>* corrente = n->left_child;
                        while(corrente) {
                            visita_ricorsiva_dfs_pre_aux_while(corrente);
                            corrente = corrente->right_sibling;
                        }
                    }
                }
                void visita_ricorsiva_dfs_pre_aux_ric(node<T>* n) {
                    if(n) {
                        // visita
                        visita_ricorsiva_dfs_pre_aux_ric(n->left_child);
                        visita_ricorsiva_dfs_pre_aux_ric(n->right_sibling);
                    }
                }
                void visita_ricorsiva_dfs_pre() {
                    visita_ricorsiva_dfs_pre_aux_while(root);
                }
                // simmetrica (in order)
                void visita_ricorsiva_dfs_sim_aux_ric(node<T>* n) {
                    if(n) {
                        visita_ricorsiva_dfs_sim_aux_ric(n->left_child);
                        // visita
                        visita_ricorsiva_dfs_sim_aux_ric(n->right_sibling);
                    }
                }
                void visita_ricorsiva_dfs_sim() {
                    visita_ricorsiva_dfs_sim_aux_ric(root);
                }
                // postordine (posticipata)
                void visita_ricorsiva_dfs_post_aux_ric(node<T>* n) {
                    if(n) {
                        visita_ricorsiva_dfs_post_aux_ric(n->left_child);
                        visita_ricorsiva_dfs_post_aux_ric(n->right_sibling);
                        // visita
                    }
                }
                void visita_ricorsiva_dfs_post() {
                    visita_ricorsiva_dfs_post_aux_ric(root);
                }
                // BFS
                // queue
                // disordered
                void visita_bfs_disordinata() const {
                    std::queue<node<T>*> q;
                    q.push(root);
                    while(!q.empty()) {
                        node<T>* n = q.front();
                        q.pop();
                        if(n) {
                            // visita
                            node<T>* current = n->left_child;
                            while(current) {
                                q.push(current);
                                current = current->right_sibling;
                            }
                        }
                    }
                }
                // ordered (for every while loop the queue contains all the level at once)
                void visita_bfs_ordinata() const {
                    std::queue<node<T>*> q;
                    q.push(root);
                    while(!q.empty()) {
                        // a questo punto la queue contiene unicamente nodi alla stessa profondita
                        int dimensione_livello = q.size();
                        for(int i = 0; i != dimensione_livello; ++i) {
                            node<T>* n = q.front();
                            q.pop();
                            if(n) {
                                // visita
                                node<T>* current = n->left_child;
                                while(current) {
                                    q.push(current);
                                    current = current->right_sibling;
                                }
                            }
                        }
                    }
                }
            protected:
            };
        }
    }
}

/* non importa il tipo di albero e come è costruito se si continua a salire da un qualsiasi x nodo alla fine si arriva alla root */
template <typename T>
void visita_dfs_stack(sd::sc::fsfd::tree<T> const& a, sd::sc::fsfd::node<T>* nodo) {
    bool match = false;
    while(nodo && !match) {
        if(nodo == a.get_root()) {
            match = true;
        }
        nodo = nodo->parent;
    }
    if(!match) {
        throw std::logic_error("ERROR: 'visita_dfs_stack' method call with not belonging node");
    }
    // ...
}

#endif //STRUTTURE_DATI_TREE_FIGLIO_SINISTRO_FRATELLO_DESTRO_HPP