#include <iostream>
#include "Leftist_Heap.h"
#include "Skew_Heap.h"
#include <chrono>

void buildSkew(int size) {
    Skew_Heap<int> skew;
    for (int i = 0 ; i < size ; i++) {
        skew.enqueue(i);
    }
}

void buildLeftist(int size) {
    Leftist_Heap<int> leftist;
    for (int i = 0 ; i < size ; i++) {
        leftist.enqueue(i);
    }
}


int main() {
    Skew_Heap<int> heap;

    /*
    std::vector<int> h1 = {15,31,1,13,42,8,57,27,33};
    std::vector<int> h2 = {17,21,8,35,24,6};

    Skew_Heap<int> heap1 = Skew_Heap<int>::insertBuild(h1);
    Skew_Heap<int> heap2 = Skew_Heap<int>::insertBuild(h2);

    heap1.merge(&heap2);
    heap1.pop();

    heap1.printHeap();
    */

    auto start_time = std::chrono::high_resolution_clock::now();
    buildSkew(1000);
    auto diff1 = std::chrono::high_resolution_clock::now() - start_time;

    auto start_time2 = std::chrono::high_resolution_clock::now();
    buildSkew(10000);
    auto diff2 = std::chrono::high_resolution_clock::now() - start_time2;

    std::cout << diff1.count() << std::endl << diff2.count() << std::endl;

    while (true) {
        std::cout << "INPUT: ";
        int input;
        std::cin >> input;

        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

        heap.enqueue(input);
        heap.printHeap();
    }



}
