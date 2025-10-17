#include "BinSearchTree.hpp"

BinSearchTree::~BinSearchTree() {
    destroy(root_);
}

void BinSearchTree::insert(const std::string &word) {
    root_ = insertHelper(root_, word);
}

void BinSearchTree::bulkInsert(const std::vector<std::string> &words) {
    for (const auto& word : words) {
        insert(word);
    }
}

bool BinSearchTree::contains(std::string_view word) const noexcept {
    return findNode(root_, word) != nullptr;
}

std::optional<int> BinSearchTree::countOf(std::string_view word) const noexcept {
    const TreeNode* node = findNode(root_, word);

    if (node) {
        return node->freq;
    }

    return std::nullopt;
}

void BinSearchTree::inorderCollect(std::vector<std::pair<std::string, int>> &out) const {
    inorderHelper(root_, out);
}

std::size_t BinSearchTree::size() const noexcept {
    return sizeHelper(root_);
}

unsigned BinSearchTree::height() const noexcept {
    return heightHelper(root_);
}

void BinSearchTree::destroy(TreeNode *node) noexcept {
    if (node) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

TreeNode *BinSearchTree::insertHelper(TreeNode *node, const std::string &word) {
    if (!node) {
        return new TreeNode(word, 1);
    }

    if (word < node->word) {
        node->left = insertHelper(node->left, word);
    } else if (word > node->word) {
        node->right = insertHelper(node->right, word);
    } else {
        node->freq += 1;
    }

    return node;
}

const TreeNode *BinSearchTree::findNode(const TreeNode *node, std::string_view word) noexcept {
    if (!node) {
        return nullptr;
    }

    if (word < node->word) {
        return findNode(node->left, word);
    } else if (word > node->word) {
        return findNode(node->right, word);
    }

    return node;
}

void BinSearchTree::inorderHelper(const TreeNode *node, std::vector<std::pair<std::string, int>> &out) {
    if (!node) {
        return;
    }

    inorderHelper(node->left, out);
    out.emplace_back(node->word, node->freq);
    inorderHelper(node->right, out);
}

std::size_t BinSearchTree::sizeHelper(const TreeNode *node) noexcept {
    if (!node) {
        return 0;
    }

    return 1 + sizeHelper(node->left) + sizeHelper(node->right);
}

unsigned BinSearchTree::heightHelper(const TreeNode *node) noexcept {
    if (!node) {
        return 0;
    }

    unsigned leftHeight = heightHelper(node->left);
    unsigned rightHeight = heightHelper(node->right);

    return 1 + std::max(leftHeight, rightHeight);
}
