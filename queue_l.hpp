#ifndef STRUTTURE_DATI_QUEUE_LISTS_HPP
#define STRUTTURE_DATI_QUEUE_LISTS_HPP

/*
 * queues are data_ structures that operate on the FIFO (First In, First Out) principle,
 * also referred to as FCFS (First Come, First Served).
 * this means the first element added to the stack is the first one to be removed,
 * while the most recently added element is the last to be accessed.
 */

#include <iostream>
#include <stdexcept>
#include <list>

namespace sd {
    namespace l {
        template <typename T>
        class queue {
        private:
            std::list<T> a;
        public:
            void enqueue(T const& data) {
                a.push_back(data);
            }
            void dequeue() {
                if(a.empty()) {
                    throw std::out_of_range("ERROR: 'dequeue' method call on empty queue");
                }
                a.pop_front();
            }
            T front() const {
                if(a.empty()) {
                    throw std::out_of_range("ERROR: 'front' method call on empty queue");
                }
                return a.front();
            }
            bool empty() const {
                return a.empty();
            }
            size_t size() const {
                return a.size();
            }
            void display() const {
                if (a.empty()) {
                    std::cout << "queue is empty." << std::endl;
                    return;
                }
                std::cout << "queue: { ";
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

#endif //STRUTTURE_DATI_QUEUE_LISTS_HPP