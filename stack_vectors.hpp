#ifndef STRUTTUREDATI_STACK_VECTORS_HPP
#define STRUTTUREDATI_STACK_VECTORS_HPP

/*
 * stacks are data structures that follow the FILO mechanism, that is first in last out or also known as FCLS (first come last served)
 * meaning that the first element that is written is the last to be read and the last to be written is the first to be read
*/

#include <iostream>
#include <stdexcept>
#include <vector>

namespace sd {
    namespace vectors {
        template <typename T>
        class stack {
        private:
            std::vector<T> a;
        public:
            void push(T const& data) {
                a.push_back(data);
            }
            void pop() {
                if(a.empty()) {
                    throw std::out_of_range("ERROR: 'pop' method call on empty stack");
                }
                a.pop_back();
            }
            T top() const {
                if(a.empty()) {
                    throw std::out_of_range("ERROR: 'top' method call on empty stack");
                }
                a.back();
            }
            bool empty() const {
                return a.empty();
            }
            size_t size() const {
                return a.size();
            }
        protected:
        };
    }
}

#endif //STRUTTUREDATI_STACK_VECTORS_HPP
