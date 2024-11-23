#ifndef STRUTTURE_DATI_DICTIONARY_V_HPP
#define STRUTTURE_DATI_DICTIONARY_V_HPP

/*
 * a dictionary represents the mathematical concept of a one-to-one relationship, defined from a
 * domain D to a codomain C R : D -> C the elements belonging to the domain are called keys, while those belonging to the codomain are called values,
 * meaning each key has a 1 to 1 unique relationship to a value.
 * a dictionary can thus be viewed as a set of associations (records) of type (KEY (K), VALUE or DATA (V / D)).
 */
/* implementation using an ordered array (vector) of elements (order is provided on the keys) */

#include <iostream>
#include <stdexcept>
#include <vector>

namespace ds {
    namespace v {
        template <typename A, typename B>
        class dictionary {
        private:
            std::vector<std::pair<A, B>> a;
            int search_index(A const& k, int l, int r) const {
                if (r < l) {
                    return -1;
                }
                int m = (l + r) / 2;
                if (a[m].first == k) {
                    return m;
                } else {
                    if(a[m].first > k) {
                        return search_index(k, l, m - 1);
                    } else {
                        return search_index(k, m + 1, r);
                    }
                }
            }
            void reallocate(size_t i) {
                a.push_back({A(), B()}); // add a placeholder at the end of the vector
                for(size_t j = (a.size() - 1); j != i; --j) {
                    a[j] = a[j - 1];
                }
            }
        public:
            /* restituisce il valore associato alla chiave K se presente nel dizionario (insieme S di record), altrimenti (indica che la chiave non è presente nel dizionario) */
            B search(A const& k) const{
                int i = search_index(k, 0, a.size());
                if(i == -1) {
                    throw std::logic_error("ERROR: 'search' method call on key not found on dictionary"); // this should be handled differently depending on the implementation
                }
                return a[i].second;
            }
            /* associa la data d alla chiave K aggiungendo la coppia al dizionario se non presente, aggiornando il valore relativo alla chiave K se presente */
            void insert(A const& k, B const& d) {
                size_t i = 0;
                while(i < a.size() and a[i].first < k) {
                    ++i;
                }
                if(i < a.size() and a[i].first == k) {
                    a[i].second  = d;
                } else {
                    if(i == a.size()) {
                        a.push_back({k, d}); // a.push_back(std::pair<A, B>({k, d}));
                    } else {
                        reallocate(i);
                        a[i] = {k , d};
                    }
                }
            }
            /* K deve essere presente nel dizionario, il metodo cancella da questo la coppia avente chiave K */
            // pop sta per delete ma delete e' anche keyword diel linguaggio
            void pop(A const& k) {
                int i = search_index(k, 0, a.size());
                if(i == -1) {
                    throw std::logic_error("ERROR: 'pop' method call on key not found on dictionary");
                }
                for(int j = i; j != (a.size() - 1); ++j) {
                    a[j] = a[j + 1];
                }
                a.pop_back(); // reallocate
            }
            bool empty() const {
                return a.empty();
            }
            size_t size() const {
                return a.size();
            }
            void display() const {
                if (a.empty()) {
                    std::cout << "dictionary is empty." << std::endl;
                    return;
                }
                std::cout << "dictionary: { ";
                for (auto it = a.begin(); it != a.end(); ++it) {
                    std::cout << "[" << (*it).first << ":" << (*it).second << "]";
                    if (std::next(it) != a.end()) {
                        std::cout << " ";
                    }
                }
                std::cout << " }" << std::endl;
            }
        protected:
        };
    }
}

#endif //STRUTTURE_DATI_DICTIONARY_V_HPP
