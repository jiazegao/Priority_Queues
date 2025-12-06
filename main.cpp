#include <iostream>
#include "Leftist_Heap.h"
#include "Skew_Heap.h"
#include <chrono>
#include <random>

std::mt19937 engine(std::random_device{}());
std::uniform_int_distribution<int> RNG_SMALL(1, 9999);

long long insertBuildSkew(const int size) {
    // Generate random integers
    std::vector<int> items(size, 0);
    for (int i = 0; i < size; i++) {
        items[i] = RNG_SMALL(engine);
    }

    // Perform enqueues
    auto start_time = std::chrono::high_resolution_clock::now();
    Skew_Heap<int>::insertBuild(items);
    return (std::chrono::high_resolution_clock::now() - start_time).count();
}

long long insertBuildSkew(const std::vector<int> &items) {
    // Perform enqueues
    auto start_time = std::chrono::high_resolution_clock::now();
    Skew_Heap<int>::insertBuild(items);
    return (std::chrono::high_resolution_clock::now() - start_time).count();
}

long long insertBuildLeftist(const int size) {
    // Generate random integers
    std::vector<int> items(size, 0);
    for (int i = 0; i < size; i++) {
        items[i] = RNG_SMALL(engine);
    }

    // Perform enqueues
    auto start_time = std::chrono::high_resolution_clock::now();
    Leftist_Heap<int>::insertBuild(items);
    return (std::chrono::high_resolution_clock::now() - start_time).count();
}

long long insertBuildLeftist(const std::vector<int> &items) {
    // Perform enqueues
    auto start_time = std::chrono::high_resolution_clock::now();
    Leftist_Heap<int>::insertBuild(items);
    return (std::chrono::high_resolution_clock::now() - start_time).count();
}

long long quickBuildSkew(const int size) {
    // Generate random integers
    std::vector<int> items(size, 0);
    for (int i = 0; i < size; i++) {
        items[i] = RNG_SMALL(engine);
    }

    // Perform enqueues
    auto start_time = std::chrono::high_resolution_clock::now();
    Skew_Heap<int>::quickBuild(items);
    return (std::chrono::high_resolution_clock::now() - start_time).count();
}

long long quickBuildSkew(const std::vector<int> &items) {
    // Perform enqueues
    auto start_time = std::chrono::high_resolution_clock::now();
    Skew_Heap<int>::quickBuild(items);
    return (std::chrono::high_resolution_clock::now() - start_time).count();
}

long long quickBuildLeftist(const int size) {
    // Generate random integers
    std::vector<int> items(size, 0);
    for (int i = 0; i < size; i++) {
        items[i] = RNG_SMALL(engine);
    }

    // Perform enqueues
    auto start_time = std::chrono::high_resolution_clock::now();
    Leftist_Heap<int>::quickBuild(items);
    return (std::chrono::high_resolution_clock::now() - start_time).count();
}

long long quickBuildLeftist(const std::vector<int> &items) {
    // Perform enqueues
    auto start_time = std::chrono::high_resolution_clock::now();
    Leftist_Heap<int>::quickBuild(items);
    return (std::chrono::high_resolution_clock::now() - start_time).count();
}

int main() {

    /*
    std::vector<int> h1 = {15,31,1,13,42,8,57,27,33};
    std::vector<int> h2 = {17,21,8,35,24,6};

    Skew_Heap<int> heap1 = Skew_Heap<int>::insertBuild(h1);
    Skew_Heap<int> heap2 = Skew_Heap<int>::insertBuild(h2);

    heap1.merge(&heap2);
    heap1.pop();

    heap1.printHeap();
    */

    // Warm up
    Skew_Heap<int> heap10;
    for (int i = 0; i < 100000; i++) {
        heap10.enqueue(i);
    }

    std::vector<int> items(10000, 0);

    // Sorted Insert
    for (int i = 0; i < 10000; i++) {
        items[0] = i;
    }
    std::cout << "Sorted Skew Insert: " << insertBuildSkew(items) << std::endl;
    std::cout << "Sorted Leftist Insert: " << insertBuildLeftist(items) << std::endl;

    // Reversed Insert
    for (int i = 9999; i >= 0; i--) {
        items[0] = i;
    }
    std::cout << "Reversed Skew Insert: " << insertBuildSkew(items) << std::endl;
    std::cout << "Reversed Leftist Insert: " << insertBuildLeftist(items) << std::endl;

    // Random Insert
    for (int i = 0; i < 10000; i++) {
        items[0] = RNG_SMALL(engine);
    }
    std::cout << "Random Skew Insert: " << insertBuildSkew(items) << std::endl;
    std::cout << "Random Leftist Insert: " << insertBuildLeftist(items) << std::endl;

    // Sorted Quick
    for (int i = 0; i < 10000; i++) {
        items[0] = i;
    }
    std::cout << "Sorted Skew Quick: " << quickBuildSkew(items) << std::endl;
    std::cout << "Sorted Leftist Quick: " << quickBuildLeftist(items) << std::endl;

    // Reversed Quick
    for (int i = 9999; i >= 0; i--) {
        items[0] = i;
    }
    std::cout << "Reversed Skew Quick: " << quickBuildSkew(items) << std::endl;
    std::cout << "Reversed Leftist Quick: " << quickBuildLeftist(items) << std::endl;

    // Random Quick
    for (int i = 0; i < 10000; i++) {
        items[0] = RNG_SMALL(engine);
    }
    std::cout << "Random Skew Quick: " << quickBuildSkew(items) << std::endl;
    std::cout << "Random Leftist Quick: " << quickBuildLeftist(items) << std::endl;

    Skew_Heap<int> heap;

    while (true) {
        std::cout << "\nINPUT: ";
        int input;
        std::cin >> input;

        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

        heap.enqueue(input);
        heap.printHeap();
    }



}
