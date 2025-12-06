//
// Created by jiaze on 2025/12/5.
//

#ifndef PRIORITYQUEUES_SKEW_HEAP_H
#define PRIORITYQUEUES_SKEW_HEAP_H

#include <queue>
#include <vector>
#include "Singly_Linked_List.h"

template <typename AnyType>
class Skew_Heap {
public:

    // Node struct
    struct Node {
        AnyType data{};
        int priority{};
        Node* left{};
        Node* right{};
    };

    // Root
    Node* root = nullptr;
    int size = 0;

    // Default merge
    void merge(const Skew_Heap* heap) {
        // Pointers
        Node* thisCurr = root;
        Node* thatCurr = heap->root;
        auto* newHeap = new Skew_Heap();
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

        // Swap branches
        for (int i = nodes.size()-1; i >= 0; i--) {
            auto temp = nodes[i];

            // If not the rightest node, swap
            if (temp->right != nullptr) {
                auto temp2 = temp->left;
                temp->left = temp->right;
                temp->right = temp2;
            }
        }

        // Reassign root
        root = newHeap->root;
    }

    // Item insertion
    void enqueue(const AnyType data, int priority) {
        auto *heap = new Skew_Heap();
        heap->root = new Node();
        heap->root->data = data;
        heap->root->priority = priority;
        merge(heap);
        delete heap;
        size++;
    }

    // Item insertion
    void enqueue(const int data) {
        auto* heap = new Skew_Heap();
        heap->root = new Node();
        heap->root->data = data;
        heap->root->priority = data;
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
        std::cout << node->data << " (" << (father!=nullptr?father->data:node->data) << "," << (father!=nullptr?(father->left->data==node->data?"L":"R"):"N/A") << ")" << std::endl;
    }

    // Print Heap
    void printHeap() {
        printData(nullptr, root, 0);
    }

    // Build heap
    static Skew_Heap insertBuild(const std::vector<int>& items) {
        auto heap = Skew_Heap<int>();
        for (auto x : items) {
            heap.enqueue(x, x);
        }
        return heap;
    }

    // Quick build
    static Skew_Heap quickBuild(const std::vector<int>& items) {
        std::queue<Skew_Heap<int>> heaps{};
        for (auto x : items) {
            auto heap = Skew_Heap<int>();
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
        Skew_Heap<int> h1 = Skew_Heap<int>();
        Skew_Heap<int> h2 = Skew_Heap<int>();
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

#endif //PRIORITYQUEUES_SKEW_HEAP_H