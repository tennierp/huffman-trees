#pragma once
#include <string>

// TreeNode struct using words, key_words, and frequencies data
struct TreeNode {
    std::string word;
    std::string key_word;
    int freq;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const std::string& w, int f) {
        word = w;
        key_word = w;
        freq = f;
        left = nullptr;
        right = nullptr;
    }

    TreeNode(TreeNode* l, TreeNode* r, int f, const std::string& kw) {
        word = "";
        key_word = kw;
        freq = f;
        left = l;
        right = r;
    }
};
