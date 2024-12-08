#ifndef STRUTTURE_DATI_LIST_HPP
#define STRUTTURE_DATI_LIST_HPP

/* implementations for doubly linked l and circular linked l are not provided */
/*
 * a doubly linked list is a type of linked list where each node contains references to both the next and
 * the previous nodes in the sequence. this structure includes a head pointer that references the first
 * node and a tail pointer that references the last node, allowing efficient traversal in both directions.
 */
/*
 * a circular linked list is a variation of a linked list in which the last node is connected back to the first node,
 * forming a continuous loop. It can be implemented as either singly or doubly linked. Unlike standard linked l,
 * circular linked l often utilize do-while loops instead of while loops for traversal, and instead of a head pointer,
 * a start flag is typically used to mark the beginning of the list.
 */

#include <iostream>
#include <stdexcept>

namespace sd {
    template <typename T>
    class list {
    private:
        struct node {
            T data;
            node* next;
            node(T data) : data(data), next(nullptr) {}
        };
        node* head;
        size_t size_;
    public:
        /* default constructor */
        list() : head(nullptr), size_(0) {}
        /* copy constructor */
        list(list const& other) : head(nullptr), size_(0) {
            if (!other.head) {
                return;
            }
            head = new node(other.head->data);
            node* current = other.head->next;
            node* previous = head;
            while(current) {
                node* new_node = new node(current->data);
                previous->next = new_node;
                previous = new_node;
                ++size_;
                current = current->next;
            }
        }
        /* move constructor */
        list(list&& other) : head(other.head), size_(other.size_) {
            other.head = nullptr;
            other.size_ = 0;
        }
        /* desctructor */
        void clear() {
            while(head) {
                node* to_delete = head;
                head = head->next;
                delete to_delete;
            }
            head = nullptr;
            size_ = 0;
        }
        ~list() {
            clear();
        }
        void push_back(T data) {
            node* new_node = new node(data);
            if (!head) {
                head = new_node;
            } else {
                node* current = head;
                while(current->next) {
                    current = current->next;
                }
                current->next = new_node;
            }
            ++size_;
        }
        void push_front(T data) {
            node* new_node = new node(data);
            new_node->next = head;
            head = new_node;
            ++size_;
        }
        T pop_back() {
            if(!head) {
                throw std::out_of_range("ERROR: 'pop_back' method call on empty list");
            }
            if(!head->next) {
                T data = head->data;
                delete head;
                head = nullptr;
                size_ = 0;
                return data;
            }
            node* a = head;
            node* b = nullptr;
            while(a->next) {
                b = a;
                a = a->next;
            }
            T data = a->data;
            delete a;
            b->next = nullptr;
            --size_;
            return data;
        }
        T pop_front() {
            if(!head) {
                throw std::out_of_range("ERROR: 'pop_front' method call on empty list");
            }
            T data = head->data;
            node* a = head;
            head = head->next;
            delete a;
            --size_;
            return data;
        };
        T front() const {
            if(!head) {
                throw std::out_of_range("ERROR: 'front' method call on empty list");
            }
            return head->data;
        }
        T back() const {
            if(!head) {
                throw std::out_of_range("ERROR: 'back' method call on empty list");
            }
            node* current = head;
            while(current->next) {
                current = current->next;
            }
            return current->data;
        }
        size_t size() const {
            return size_;
        }
        bool empty() const {
            return head;
        }
        bool operator==(list const& other) const {
            if(size_ != other.size_) {
                return false;
            }
            node* a = head;
            node* b = other.head;
            while(a && b) {
                if(a->data != b->data) {
                    return false;
                }
                a = a->next;
                b = b->next;
            }
            return true;
        }
        bool operator!=(list const& other) const {
            return !(*this == other);
        }
        list& operator=(list const& other) {
            if(this != &other) {
                clear();
                if (!other.head) {
                    return *this;
                }
                head = new node(other.head->data);
                node* current = other.head->next;
                node* previous = head;
                while(current) {
                    node* new_node = new node(current->data);
                    previous->next = new_node;
                    previous = new_node;
                    ++size_;
                    current = current->next;
                }
            }
            return *this;
        }
        list& operator=(list&& other) {
            if(this == &other) {
                return *this;
            }
            clear();
            head = other.head;
            size_ = other.size_;
            other.head = nullptr;
            other.size_ = 0;
            return *this;
        }
        class iterator {
        private:
            node* ptr;
        public:
            iterator() : ptr(nullptr) {}
            iterator(node* ptr) : ptr(ptr) {}
            T& operator*() {
                return ptr->data;
            }
            T const& operator*() const {
                return ptr->data;
            }
            iterator& operator++() {
                ptr = ptr->next;
                return *this;
            }
            iterator operator++(int) {
                iterator temp(ptr);
                ++(*this);
                return temp;
            }
            bool operator==(iterator const& other) const {
                return ptr == other.ptr;
            }
            bool operator!=(iterator const& other) const {
                return ptr != other.ptr;
            }
        protected:
        };
        iterator begin() {
            return iterator(head);
        }
        iterator end() {
            return iterator(nullptr);
        }
        void display() const {
            std::cout << "list: { ";
            node* current = head;
            while(current) {
                std::cout << current->data;
                if(current->next) {
                    std::cout << ", ";
                }
                current = current->next;
            }
            std::cout << " }" << std::endl;
        }
    protected:
    };
}

#endif //STRUTTURE_DATI_LIST_HPP