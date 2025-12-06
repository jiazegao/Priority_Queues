cmake_minimum_required(VERSION 4.0)
project(PriorityQueues)

set(CMAKE_CXX_STANDARD 20)

add_executable(PriorityQueues main.cpp
        Singly_Linked_List.h
        Leftist_Heap.h
        Skew_Heap.h)
