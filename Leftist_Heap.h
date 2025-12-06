//
// Created by jiaze on 2025/12/3.
//

#ifndef PRIORITYQUEUES_LEFTIST_HEAP_H
#define PRIORITYQUEUES_LEFTIST_HEAP_H

#include <queue>
#include <vector>
#include "Singly_Linked_List.h"

template <typename AnyType>
class Leftist_Heap {
public:

    // Node struct
    struct Node {
        AnyType data{};
        int priority{};
        Node* left{};
        Node* right{};
        int NPL{};
    };

    // Root
    Node* root = nullptr;
    int size = 0;

    // Default merge
    void merge(const Leftist_Heap* heap) {
        // Pointers
        Node* thisCurr = root;
        Node* thatCurr = heap->root;
        auto* newHeap = new Leftist_Heap();
        Node* newCurr = newHeap->root;

        // One of the heap is empty
        if (thisCurr == nullptr && thatCurr != nullptr) {
            root = heap->root;
            return;
        }
        if (thisCurr != nullptr && thatCurr == nullptr) {
            return;
        }
        if (thisCurr == nullptr && thatCurr == nullptr) {
            return;
        }

        std::vector<Node*> nodes;

        // Initialize root
        if (thisCurr->priority <= thatCurr->priority) {
            // Assign then cut down the right branch
            newHeap->root = thisCurr;
            newCurr = thisCurr;
            // Advance
            thisCurr = thisCurr->right;
            newCurr->right = nullptr;
        }
        else if (thisCurr->priority > thatCurr->priority) {
            // Assign then cut down the right branch
            newHeap->root = thatCurr;
            newCurr = thatCurr;
            // Advance
            thatCurr = thatCurr->right;
            newCurr->right = nullptr;
        }

        nodes.push_back(newCurr);

        // Merge with comparison
        while (thisCurr != nullptr && thatCurr != nullptr) {
            // Merging this subtree
            if (thisCurr->priority <= thatCurr->priority) {
                // Assign then cut down the right branch
                newCurr->right = thisCurr;
                // Advance
                thisCurr = thisCurr->right;
                newCurr->right->right = nullptr;
                newCurr = newCurr->right;
            }
            // Merging that subtree
            else if (thisCurr->priority > thatCurr->priority) {
                // Assign then cut down the right branch
                newCurr->right = thatCurr;
                // Advance
                thatCurr = thatCurr->right;
                newCurr->right->right = nullptr;
                newCurr = newCurr->right;
            }
            nodes.push_back(newCurr);
        }

        // Merge without comparison
        if (thisCurr != nullptr) {
            newCurr->right = thisCurr;
        }
        else if (thatCurr != nullptr) {
            newCurr->right = thatCurr;
        }

        // Update NPL and swap if necessary
        for (int i = nodes.size()-1; i >= 0; i--) {
            auto temp = nodes[i];
            // Both empty
            if (temp->left == nullptr && temp->right == nullptr) {
                temp->NPL = 0;
            }
            // Only left is empty
            else if (temp->left == nullptr && temp->right != nullptr) {
                temp->left = temp->right;
                temp->right = nullptr;
                temp->NPL = 0;
            }
            // Only right is empty
            else if (temp->left != nullptr && temp->right == nullptr) {
                temp->NPL = 0;
            }
            // Swap if necessary
            else if (temp->left->NPL < temp->right->NPL) {
                auto temp2 = temp->left;
                temp->left = temp->right;
                temp->right = temp2;
                temp->NPL = temp->right->NPL+1;
            }
            // No swap
            else {
                temp->NPL = temp->right->NPL+1;
            }
        }

        // Reassign root
        root = newHeap->root;
    }

    // Item insertion
    void enqueue(const AnyType data, int priority) {
        auto *heap = new Leftist_Heap();
        heap->root = new Node();
        heap->root->data = data;
        heap->root->priority = priority;
        heap->root->NPL = 0;
        merge(heap);
        delete heap;
        size++;
    }

    // Item insertion
    void enqueue(const int data) {
        auto* heap = new Leftist_Heap();
        heap->root = new Node();
        heap->root->data = data;
        heap->root->priority = data;
        heap->root->NPL = 0;
        merge(heap);
        delete heap;
        size++;
    }

    // Single print
    void printData(Node* father, Node* node, int depth) {
        if (node->right != nullptr) {
            printData(father==nullptr?root:node, node->right, depth+1);
        }
        if (node->left != nullptr) {
            printData(father==nullptr?root:node, node->left, depth+1);
        }
        for (int i = 0; i < depth; i++) {
            std::cout << "  ";
        }
        std::cout << node->data << " (" << (father!=nullptr?father->data:node->data) << "," << (father!=nullptr?(father->left->data==node->data?"L":"R"):"N/A") << "," << node->NPL << ")" << std::endl;
    }

    // Print Heap
    void printHeap() {
        printData(nullptr, root, 0);
    }

    // Build heap
    static Leftist_Heap insertBuild(const std::vector<int>& items) {
        auto heap = Leftist_Heap<int>();
        for (auto x : items) {
            heap.enqueue(x, x);
        }
        return heap;
    }

    // Quick build
    static Leftist_Heap quickBuild(const std::vector<int>& items) {
        std::queue<Leftist_Heap<int>> heaps{};
        for (auto x : items) {
            auto heap = Leftist_Heap<int>();
            heap.enqueue(x, x);
            heaps.emplace(heap);
        }
        while (heaps.size() > 1) {
            auto heap = heaps.front();
            heaps.pop();
            heap.merge(&heaps.front());
            heaps.pop();
            heaps.emplace(heap);
        }
        return heaps.front();
    }

    AnyType top() {
        return root->data;
    }

    // Remove
    void pop() {
        Leftist_Heap<int> h1 = Leftist_Heap<int>();
        Leftist_Heap<int> h2 = Leftist_Heap<int>();
        h1.root = root->left;
        h2.root = root->right;

        // One nullptr
        if (h1.root == nullptr) {
            root = h2.root;
            return;
        }
        if (h2.root == nullptr) {
            root = h1.root;
            return;
        }

        // Merge
        h1.merge(&h2);
        root = h1.root;
    }
};

#endif //PRIORITYQUEUES_LEFTIST_HEAP_H