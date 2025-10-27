#pragma once
#include <string>
#include <utility>
#include <vector>
#include <ostream>
#include "utils.hpp"
#include "TreeNode.hpp"
#include "PriorityQueue.hpp"

class HuffmanTree {
public:
    // Build from BST output (lexicographic vector of (word, count)).
    void buildFromCounts(const std::vector<std::pair<std::string,int>>& counts);

    HuffmanTree() = default;
    ~HuffmanTree(); // deletes the entire Huffman tree

    // Build a vector of (word, code) pairs by traversing the Huffman tree
    // (left=0, right=1; visit left before right).
    void assignCodes(std::vector<std::pair<std::string,std::string>>& out) const;

    // Write header lines of "word code" in preorder (left=0, right=1).
    error_type writeHeader(std::ostream& os) const;

    // Encode a sequence of tokens as bits, wrapping every wrap_cols columns (default 80).
    error_type encode(const std::vector<std::string>& tokens,
                      std::ostream& os_bits,
                      int wrap_cols = 80) const;

private:
    TreeNode* root_ = nullptr; // owns the full Huffman tree

    // helpers (decl only; defs in .cpp)
    static void destroy(TreeNode* n) noexcept;

    static void assignCodesDFS(const TreeNode* n,
                               std::string& prefix,
                               std::vector<std::pair<std::string,std::string>>& out);

    static void writeHeaderPreorder(const TreeNode* n,
                                    std::ostream& os,
                                    std::string& prefix);
};
