//
// Created by Parker Tennier on 10/17/25.
//

#include "PriorityQueue.hpp"

PriorityQueue::PriorityQueue(std::vector<TreeNode *> nodes) {
    items_ = nodes;

    // Insertion sort using swaps
    for (size_t i = 1; i < items_.size(); ++i) {
        for (size_t j = i; j > 0 && higherPriority(items_[j], items_[j-1]); j--) {
            TreeNode* temp = items_.at(j);
            items_.at(j) = items_.at(j - 1);
            items_.at(j - 1) = temp;
        }
    }
}

std::size_t PriorityQueue::size() const noexcept {
    return items_.size();
}

bool PriorityQueue::empty() const noexcept {
    return items_.empty();
}

TreeNode *PriorityQueue::findMin() const noexcept {
    if (items_.empty()) {
        return nullptr;
    }

    return items_.back();
}

TreeNode *PriorityQueue::extractMin() noexcept {
    if (items_.empty()) {
        return nullptr;
    }

    TreeNode* min = items_.back();
    items_.pop_back();


    return min;
}

void PriorityQueue::deleteMin() noexcept {
    if (!items_.empty()) {
        items_.pop_back();
    }
}

void PriorityQueue::insert(TreeNode* node) {
    items_.push_back(node);
    size_t idx = items_.size() - 1;

    while (idx > 0 && higherPriority(items_.at(idx), items_.at(idx - 1))) {
        auto* temp = items_.at(idx - 1);
        items_.at(idx - 1) = items_.at(idx);
        items_.at(idx) = temp;
        idx--;
    }
}


void PriorityQueue::print(std::ostream &os) const {
    for (size_t i = 0; i < items_.size(); ++i) {
        TreeNode* node = items_.at(i);
        os << std::setw(10) << node->freq << " " << node->key_word << std::endl;
    }
}

bool PriorityQueue::higherPriority(const TreeNode *a, const TreeNode *b) noexcept {
    if (a->freq != b->freq) {
        return a->freq > b->freq;
    }
    return a->key_word < b->key_word;
}

bool PriorityQueue::isSorted() const {
    for (size_t i = 1; i < items_.size(); ++i) {
        if (higherPriority(items_.at(i), items_.at(i - 1))) {
            return false;
        }
    }
    return true;
}
