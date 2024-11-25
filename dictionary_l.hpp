#ifndef STRUTTURE_DATI_DICTIONARY_L_HPP
#define STRUTTURE_DATI_DICTIONARY_L_HPP

/*
 * a dictionary represents the mathematical concept of a one-to-one relationship, defined from a
 * domain D to a codomain C R : D -> C the elements belonging to the domain are called keys, while those belonging to the codomain are called values,
 * meaning each key has a 1 to 1 unique relationship to a value.
 * a dictionary can thus be viewed as a set of associations (records) of type (KEY (K), VALUE or DATA (V / D)).
 */
/* implementazione dizionario attraverso una collezione L di n record contenenti una chiave key, un valore data, un puntatore al record successivo next e un puntatore al record precedente prev.
 * inoltre un attributo L.head punta al primo record della sequenza, la lista vuota viene codificata con la seguente condizione: L.head == NIL.
 */
/* notice this kind of dictionary could also be implemented using std::lists */

#include <iostream>
#include <stdexcept>

namespace ds {
    namespace l {
        template <typename A, typename B>
        class dictionary {
        private:
            struct record {
                A key;
                B data;
                record* next;
                record* prev;
                record(A const& key, B const& data) : key(key), data(data), next(nullptr), prev(nullptr) {}
            };
            record* head;
            size_t size_;
        public:
            dictionary() : head(nullptr), size_(0) {}
            void clear() {
                while(head) {
                    record* to_delete = head;
                    head = head->next;
                    delete to_delete;
                }
                head = nullptr;
                size_ = 0;
            }
            ~dictionary() {
                clear();
            }
            B search(A const& k) const {
                record* current = head;
                while(current and current->key != k) {
                    current = current->next;
                }
                if(current) {
                    return current->data;
                }
                throw std::logic_error("ERROR: 'search' method call on key not found on dictionary"); // this should be handled differently depending on the implementation
            }
            /* l’algoritmo consiste in una semplice aggiunta di un elemento in testa ad una lista doppiamente concatenata, con la sistemazione dei puntatori
             * che tale operazione richiede. a differenza della insert() dell’implementazione con gli array, questa operazione non si preoccupa di aggiornare il valore del record contenente la
             * chiave K qualora questa sia già presente nella lista.
             */
            void insert(A const& k, B const& d) {
                record* new_record = new record(k, d);
                if(!head) {
                    head = new_record;
                    return;
                }
                new_record->next = head;
                head->prev = new_record;
                head = new_record;
            }
            /* dato che l’insert non aggiorna il valore delle chiavi qualora queste siano già presenti, bisogna scorrere tutta la lista per rimuovere tutte le occorrenze della chiave K. */
            // erase sta per delete ma delete e' anche keyword del linguaggio
            void erase(A const& k) {
                if(!head) {
                    throw std::logic_error("ERROR: 'erase' method call on empty dictionary");
                }
                record* current = head;
                while(current) {
                    if(current->key == k) {
                        if(current->prev) {
                            current->prev->next = current->next;
                        } else {
                            head = current->next;
                        }
                        if(current->next) {
                            current->next->prev = current->prev;
                        }
                        record* to_delete = current;
                        current = current->next;
                        delete to_delete;
                    } else {
                        current = current->next;
                    }
                }
            }
            bool empty() const {
                return head == nullptr;
            }
            size_t size() const {
                return size_;
            }
            void display() const {
                if (empty()) {
                    std::cout << "dictionary is empty." << std::endl;
                    return;
                }
                std::cout << "dictionary: { ";
                record* current = head;
                while(current) {
                    std::cout << "[" << current->key << ":" << current->data << "]";
                    if (current->next) {
                        std::cout << " ";
                    }
                    current = current->next;
                }
                std::cout << " }" << std::endl;
            }
        protected:
        };
    }
}

#endif //STRUTTURE_DATI_DICTIONARY_L_HPP