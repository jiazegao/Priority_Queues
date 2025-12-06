//
// Created by jiaze on 2025/12/3.
//

#ifndef PRIORITYQUEUES_SINGLY_LINKED_LIST_H
#define PRIORITYQUEUES_SINGLY_LINKED_LIST_H

// Singly linked list for quick removal / insertion
template <typename AnyType>
class Singly_Linked_List {

public:
    Singly_Linked_List() {
        head = new Node(nullptr);
        tail = new Node(nullptr);
        length = 0;
        head->next = tail;
    }

    class Node {
        public:
            explicit Node(AnyType* obj_ptr) {
                this->ptr = obj_ptr;
                this->next = nullptr;
            }
            AnyType* ptr;
            Node* next;
    };

    class Iterator {
    private:
        Node* next;
        Node* previous;
        Singly_Linked_List* list;
        int count;

    public:
        // Constructor
        explicit Iterator(Singly_Linked_List* list, Node* node) : next(node), previous(list->getHead()), list(list), count(0) {}

        // Dereference operator
        AnyType*& operator*() const {
            return next->ptr;
        }

        // Pre-increment operator
        Iterator& operator++() {
            if (next != list->getTail() && count < list->size()) {
                previous = next;
                next = next->next;
                count++;
            }
            return *this;
        }

        // Post-increment operator (optional, but good practice)
        Iterator operator++(int) {
            Iterator temp = *this;
            if (next != list->getTail() && count < list->size()) {
                previous = next;
                next = next->next;
                count++;
            }
            return temp;
        }

        // Equality operator
        bool operator==(const Iterator& other) const {
            return next == other.next;
        }

        // Inequality operator
        bool operator!=(const Iterator& other) const {
            return next != other.next;
        }

        // Insert at current location
        void insert(AnyType* obj_ptr) {
            if (obj_ptr != nullptr) {
                // previous * next  =>  previous * new - next
                Node* oldNode = next;
                previous->next = new Node(obj_ptr);
                previous->next->next = oldNode;
                ++list->length;

                next = previous->next; // Update iterator
            }
        }

        // Remove current object
        bool remove(bool clean = false) {
            if (next == list->getTail()) return false;

            if (0 <= count && count < list->size()) {
                // previous * next - nextNext  =>  previous * nextNext
                Node* oldNode = next;
                next = next->next;
                previous->next = next;
                if (clean && oldNode->ptr != nullptr) delete oldNode->ptr;
                delete oldNode;
                --list->length;
                return true;
            }
            else {
                return false;
            }
        }

        // Get current index
        [[nodiscard]] int getIndex() const {
            return count;
        }
    };

    Iterator begin() {
        return Iterator(this, head->next);
    }

    Iterator end() {
        return Iterator(this, tail);
    }

    void push_back(AnyType* obj_ptr) {
        insert(length, obj_ptr);
    }

    void add_front(AnyType* obj_ptr) {
        insert(0, obj_ptr);
    }

    void insert(int index, AnyType* obj_ptr) {
        if (obj_ptr != nullptr) {
            int temp_index = index;

            if (this->head != nullptr && temp_index >= 0 && temp_index <= length) {
                Node* currNode = this->head;
                while (temp_index > 0){
                    currNode = currNode->next;
                    temp_index--;
                }
                Node* oldNode = currNode->next;
                currNode->next = new Node(obj_ptr);
                currNode->next->next = oldNode;
                length++;
            }
        }
    }

    void pop(int index, bool clean = false){
        if (index >= 0 && index < length) {
            Node* currNode = head;
            while (index > 0){
                currNode = currNode->next;
                index--;
            }
            Node* oldNode = currNode->next;
            currNode->next = oldNode->next;
            if (clean && oldNode->ptr != nullptr) delete oldNode->ptr;
            delete oldNode;
            length--;
        }
    }

    AnyType* get(int index){
        Node* currNode = head;
        if (index >= 0 && index < length) {
            while (index >= 0){
                currNode = currNode->next;
                index--;
            }
        }
        return currNode->ptr;
    }

    AnyType* operator[](int index) {
        return get(index);
    }

    void remove(AnyType* obj_ptr, bool clean = false) {
        if (obj_ptr != nullptr) {
            Node* currNode = this->head;
            while (currNode->next != nullptr && currNode->next->ptr != obj_ptr){
                currNode = currNode->next;
            }
            if (currNode->next != nullptr && currNode->next->ptr == obj_ptr) {
                Node* oldNode = currNode->next;
                currNode->next = oldNode->next;
                if (clean && oldNode->ptr != nullptr) delete oldNode->ptr;
                delete oldNode;
                length--;
            }
        }
    }

    [[nodiscard]] int size() const {
        return length;
    }

    void setSize(int size) {
        length = size;
    }

    Node* getHead() {
        return this->head;
    }

    Node* getTail() {
        return this->tail;
    }

private:
    Node* head;
    Node* tail;
    int length = 0;

};

#endif //PRIORITYQUEUES_SINGLY_LINKED_LIST_H