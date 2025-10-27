#include "HuffmanTree.hpp"
#include "PriorityQueue.hpp"
#include "TreeNode.hpp"
#include <utility>

void HuffmanTree::buildFromCounts(const std::vector<std::pair<std::string, int>>& counts) {
    if (counts.empty()) {
        root_ = nullptr;
        return;
    }

    std::vector<TreeNode*> nodes;
    for (size_t i = 0; i < counts.size(); ++i) {
        const std::string& word = counts[i].first;
        int freq = counts[i].second;

        TreeNode* node = new TreeNode(word, freq);
        node->key_word = word;
        nodes.push_back(node);
    }

    PriorityQueue pq(nodes);

    while (pq.size() > 1) {
        TreeNode* left = pq.extractMin();
        TreeNode* right = pq.extractMin();

        int combined_freq = left->freq + right->freq;
        std::string combined_key;

        if (left->key_word < right->key_word) {
            combined_key = left->key_word;
        } else {
            combined_key = right->key_word;
        }

        TreeNode* parent = new TreeNode(left, right, combined_freq, combined_key);
        pq.insert(parent);
    }

    if (pq.size() == 1) {
        root_ = pq.extractMin();
    } else {
        root_ = nullptr;
    }
}

HuffmanTree::~HuffmanTree() {
    destroy(root_);
}

void HuffmanTree::destroy(TreeNode* node) noexcept {
    if (node == nullptr) {
        return;
    }

    destroy(node->left);
    destroy(node->right);
    delete node;
}

void HuffmanTree::assignCodes(std::vector<std::pair<std::string, std::string>> &out) const {
    out.clear();

    if (!root_) {
        return;
    }

    std::string prefix;
    assignCodesDFS(root_, prefix, out);
}

error_type HuffmanTree::writeHeader(std::ostream& os) const {
    if (!os) {
        return UNABLE_TO_OPEN_FILE_FOR_WRITING;
    }

    std::string prefix;
    writeHeaderPreorder(root_, os, prefix);

    if (os.fail()) {
        return FAILED_TO_WRITE_FILE;
    }
    return NO_ERROR;
}

error_type HuffmanTree::encode(const std::vector<std::string>& tokens, std::ostream& os_bits, int wrap_cols) const {
    if (!os_bits) {
        return UNABLE_TO_OPEN_FILE_FOR_WRITING;
    }

    std::vector<std::pair<std::string, std::string> > codes;
    assignCodes(codes);

    size_t col = 0;
    for (size_t i = 0; i < tokens.size(); ++i) {
        const std::string& t = tokens[i];

        bool found = false;
        std::string code;

        for (size_t k = 0; k < codes.size(); ++k) {
            if (codes[k].first == t) {
                found = true;
                code = codes[k].second;
                break;
            }
        }

        if (!found) {
            return ERR_TYPE_NOT_FOUND;
        }

        for (size_t j = 0; j < code.size(); ++j) {
            if (wrap_cols > 0 && col == static_cast<size_t>(wrap_cols)) {
                os_bits << '\n';
                col = 0;
            }
            os_bits << code[j];
            col += 1;
        }
    }

    if (col != 0 || tokens.empty()) {
        os_bits << '\n';
    }

    if (os_bits.fail()) {
        return FAILED_TO_WRITE_FILE;
    }
    return NO_ERROR;
}

void HuffmanTree::assignCodesDFS(const TreeNode *n, std::string &prefix, std::vector<std::pair<std::string, std::string>> &out) {
    if (!n) {
        return;
    }

    if (!n->word.empty()) {
        std::string code;
        if (prefix.empty()) {
            code = "0";
        } else {
            code = prefix;
        }
        out.push_back({n->word, code});
        return;
    }

    prefix.push_back('0');
    assignCodesDFS(n->left, prefix, out);
    prefix.pop_back();

    prefix.push_back('1');
    assignCodesDFS(n->right, prefix, out);
    prefix.pop_back();
}

void HuffmanTree::writeHeaderPreorder(const TreeNode *n, std::ostream &os, std::string &prefix) {
    if (!n) {
        return;
    }

    if (!n->word.empty()) {
        std::string code;
        if (prefix.empty()) {
            code = "0";
        } else {
            code = prefix;
        }
        os << n->word << " " << code << "\n";
        return;
    }

    prefix.push_back('0');
    writeHeaderPreorder(n->left, os, prefix);
    prefix.pop_back();

    prefix.push_back('1');
    writeHeaderPreorder(n->right, os, prefix);
    prefix.pop_back();
}