#ifndef STRUTTURE_DATI_LIST_HPP
#define STRUTTURE_DATI_LIST_HPP

/* implementation for doubly linked lists and circular lists is not provided */
/*
 * doubly linked: same as singly linked lists (provided below) but you not only have head pointer but also tail pointer
 * and each node has a pointer to the next and previous node, so it is easier to iterate over it,
 * but it is important to make sure everything is correctly implemented
*/
/*
 * circular lists: same as singly linked lists (provided below) but here the implementation doesn't support an actual starting and finishing point
 * there is a flag (any node) that is considered the start, and then you iterate over the list not until next is nullptr (meaning the end was reached),
 * but until you reach the same node the iteration started from, you do so using do while loops instead of dimple whiles, because otherwise the finishing condition
 * wouldn't even let you start the first iteration of the loop (current != start) and current starts as current = start, so first you iterate once and then condition starts
 * making sense
 * last important thing is that all nodes are connected using a next pointer, but there isn't a last node that has next == nullptr,
 * but eventually one node's next will be another node address, usually unless specified it is more efficient to add and remove nodes one node after the start (start->next)
 *
 * a circular list is a linked list where the last node points back to the first node, it can be either singly or doubly linked
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
    protected:
    };
}

#endif //STRUTTURE_DATI_LIST_HPP