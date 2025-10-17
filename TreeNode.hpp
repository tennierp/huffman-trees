#pragma once
#include <string>

struct TreeNode {
    std::string word;      // the actual word (for leaves)
    std::string key_word;  // representative word for ordering
    int freq;              // count/frequency
    TreeNode* left;
    TreeNode* right;

    // Constructor for leaf nodes (from BST)
    TreeNode(const std::string& w, int f) {
        word = w;
        key_word = w;
        freq = f;
        left = nullptr;
        right = nullptr;
    }

    // Constructor for internal nodes (for Huffman - not used in Part 2)
    TreeNode(TreeNode* l, TreeNode* r, int f, const std::string& kw) {
        word = "";
        key_word = kw;
        freq = f;
        left = l;
        right = r;
    }
};
