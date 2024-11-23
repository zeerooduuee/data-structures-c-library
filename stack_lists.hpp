#ifndef STRUTTUREDATI_STACK_LISTS_HPP
#define STRUTTUREDATI_STACK_LISTS_HPP

/*
 * stacks are data_ structures that operate on the FILO (First In, Last Out) principle,
 * also referred to as FCLS (First Come, Last Served). 
 * this means the first element added to the stack is the last one to be removed, 
 * while the most recently added element is the first to be accessed.
 */

#include <iostream>
#include <stdexcept>
#include <list>

namespace ds {
    namespace l {
        template <typename T>
        class stack {
        private:
            std::list<T> a;
        public:
            void push(T const& data) {
                a.push_front(data);
            }
            void pop() {
                if(a.empty()) {
                    throw std::out_of_range("ERROR: 'pop' method call on empty stack");
                }
                a.pop_front();
            }
            T top() const {
                if(a.empty()) {
                    throw std::out_of_range("ERROR: 'top' method call on empty stack");
                }
                a.front();
            }
            bool empty() const {
                return a.empty();
            }
            size_t size() const {
                return a.size();
            }
            void display() const {
                std::cout << "stack: { ";
                for (auto it = a.begin(); it != a.end(); ++it) {
                    std::cout << *it;
                    if (std::next(it) != a.end()) {
                        std::cout << ", ";
                    }
                }
                std::cout << " }" << std::endl;
            }
        protected:
        };
    }
}

#endif //STRUTTUREDATI_STACK_LISTS_HPP