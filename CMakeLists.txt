cmake_minimum_required(VERSION 4.0)
project(huffman-trees)

set(CMAKE_CXX_STANDARD 20)

add_executable(huffman-trees main.cpp
        Scanner.cpp
        Scanner.hpp
        utils.cpp
        utils.hpp
        BinSearchTree.cpp
        BinSearchTree.hpp
        TreeNode.hpp
        PriorityQueue.cpp
        PriorityQueue.hpp
        HuffmanTree.cpp
        HuffmanTree.hpp
)