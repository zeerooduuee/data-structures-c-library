#ifndef STRUTTURE_DATI_QUEUE_VECTORS_HPP
#define STRUTTURE_DATI_QUEUE_VECTORS_HPP

/*
 * queues are data_ structures that operate on the FIFO (First In, First Out) principle,
 * also referred to as FCFS (First Come, First Served).
 * this means the first element added to the stack is the first one to be removed,
 * while the most recently added element is the last to be accessed.
 */

#include <iostream>
#include <stdexcept>
#include <vector>

/* implementation with capacity cap */
/*
    class queue {
    private:
        std::vector<int> data;
        int capacity;
        int front;
        int rear;
        int size;

    public:
        queue(int cap) : capacity(cap), front(0), rear(0), size(0) {
            data.resize(cap);
        }
*/

namespace sd {
    namespace v {
        template <typename T>
        class queue {
        private:
            std::vector<T> a;
            size_t size_;
            size_t front_;
            size_t rear_;

            void resize() {
                std::vector<T> new_a(a.size() * 2);
                for(size_t i = 0; i != size_; ++i) {
                    new_a[i] = a[(front_ + i) % a.size()];
                }
                a = std::move(new_a);
                front_ = 0;
                rear_ = size_;
            }

        public:
            queue() : size_(0), front_(0), rear_(0) {
                a.resize(4);
            }
            void enqueue(T const& data) {
                if(size_ == a.size()) {
                    resize();
                }
                a[rear_] = data;
                rear_ = (rear_ + 1) % a.size();
                ++size_;
            }
            void dequeue() {
                if(size_ == 0) {
                    throw std::out_of_range("ERROR: 'dequeue' method call on empty queue");
                }
                front_ = (front_ + 1) % a.size();
                --size_;
            }
            T front() const {
                if(size_ == 0) {
                    throw std::out_of_range("ERROR: 'front' method call on empty queue");
                }
                return a[front_];
            }
            bool empty() const {
                return size_ == 0;
            }
            size_t size() const {
                return size_;
            }
            void display() const {
                if (size_ == 0) {
                    std::cout << "queue is empty." << std::endl;
                    return;
                }
                std::cout << "queue: { ";
                for (int i = 0; i < size_; ++i) {
                    std::cout << a[(front_ + i) % a.size()];
                    if (i < size_ - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << " }" << std::endl;
            }
        protected:
        };
    }
}

#endif //STRUTTURE_DATI_QUEUE_VECTORS_HPP