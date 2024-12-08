#ifndef STRUTTUREDATI_VECTOR_HPP
#define STRUTTUREDATI_VECTOR_HPP

#include <iostream>
#include <stdexcept>

namespace sd {
    template <typename T>
    class vector {
    private:
        T* data_;
        size_t capacity_;
        size_t size_;

        void resize(size_t new_capacity) {
            T* new_data = new T[new_capacity];
            for(size_t i = 0; i != size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }
    public:
        /* constructor */
        vector() : data_(new T[1]), capacity_(1), size_(0) {}
        /* desctructor */
        ~vector() {
            delete[] data_;
            capacity_ = 0; // not really needed
            size_ = 0; // not really needed
        }
        /* add element */
        void push_back(T const& data) {
            if (size_ == capacity_) {
                resize(capacity_ * 2);
            }
            data_[size_++] = data;
        }
        /* remove element */
        void pop_back() {
            if (size_ > 0) {
                --size_;
                if (size_ == (capacity_ / 4) && capacity_ > 2) {
                    resize(capacity_ / 2);
                }
            }
        }
        /* front and back */
        T front() const {
            if(size_ == 0) {
                throw std::out_of_range("ERROR: 'front' method call on empty vector");
            }
            return data_[0];
        }
        T back() const {
            if(size_ == 0) {
                throw std::out_of_range("ERROR: 'back' method call on empty vector");
            }
            return data_[size_ - 1];
        }
        /* access element by index */
        // []
        T& operator[](size_t index) {
            return data_[index];
        }
        T const& operator[](size_t index) const {
            return data_[index];
        }
        // at()
        T& at(size_t index) {
            if (index >= size_) {
                throw std::out_of_range("ERROR: index out of range on method call 'at()'");
            }
            return data_[index];
        }
        T const& at(size_t index) const {
            if (index >= size_) {
                throw std::out_of_range("ERROR: index out of range on method call 'at()'");
            }
            return data_[index];
        }
        /* getters */
        size_t size() const {
            return size_;
        }
        size_t capacity() const {
            return capacity_;
        }
        /* empty */
        bool empty() const {
            return size_ == 0;
        }
        /* clear */
        void clear() {
            delete[] data_;
            data_ = new T[1];
            capacity_ = 1;
            size_ = 0;
        }
        /* iterator class */
        class iterator {
        private:
            T* ptr;
        public:
            iterator(T* ptr) : ptr(ptr){}
            // dereference operator
            T& operator*() {
                return *ptr;
            }
            T const& operator*() const{
                return *ptr;
            }
            // pre-increment es: a = ++b se b = 0; --> b = b + 1 quindi b = 1 e poi a = b quindi a = 1
            iterator& operator++() {
                ++ptr;
                return *this;
            }
            // post-increment es: a = b++ se b = 0; --> a = b quindi a = 0  e poi b = b + 1 quindi b = 1
            iterator operator++(int) {
                iterator temp(ptr); // iterator temp = *this (also valid)
                ++(ptr); // ++(*this) (also valid)
                return temp;
            }
            // comparison operators
            bool operator==(iterator const& other) const {
                return ptr == other.ptr;
            }
            bool operator!=(iterator const& other) const {
                return ptr != other.ptr;
            }
        protected:
        };
        // begin iterator
        iterator begin() {
            return iterator(data_);
        }
        // end iterator
        iterator end() {
            return iterator(data_ + size_);
        }
        // display
        void display() const {
            std::cout << "vector: { ";
            for(size_t i = 0; i != size_; ++i) {
                std::cout << data_[i];
                if(i != (size_ - 1)) {
                    std::cout << ", ";
                }
            }
            std::cout << " }" << std::endl;
        }
    protected:
    };
}

#endif //STRUTTUREDATI_VECTOR_HPP