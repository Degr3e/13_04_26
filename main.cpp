#include <iostream>

template<class T, size_t K>
struct BTree {
    T val[K];
    BTree<T, K>* childs[K + 1] = {};
    BTree<T, K>* parent = nullptr;
};

template<class T, size_t K>
struct BTreeIt {
    size_t s;
    BTree<T, K>* current;
};

template<class T, size_t K>
T value(BTreeIt<T, K> it) {
    return it.current->val[it.s];
}

template<class T, size_t K>
BTreeIt<T, K> leftmost(BTree<T, K>* node) {
    while (node->childs[0]) node = node->childs[0];
    return {0, node};
}

template<class T, size_t K>
BTreeIt<T, K> rightmost(BTree<T, K>* node) {
    while (node->childs[K]) node = node->childs[K];
    return {K - 1, node};
}

template<class T, size_t K>
BTreeIt<T, K> next(BTreeIt<T, K> it) {
    auto node = it.current;
    size_t i = it.s;

    if (node->childs[i + 1]) {
        return leftmost<T, K>(node->childs[i + 1]);
    }

    while (node->parent) {
        auto parent = node->parent;
        size_t idx = 0;
        while (parent->childs[idx] != node) idx++;
        if (idx < K) return {idx, parent};
        node = parent;
    }

    return it;
}

template<class T, size_t K>
BTreeIt<T, K> prev(BTreeIt<T, K> it) {
    auto node = it.current;
    size_t i = it.s;

    if (node->childs[i]) {
        return rightmost<T, K>(node->childs[i]);
    }

    while (node->parent) {
        auto parent = node->parent;
        size_t idx = 0;
        while (parent->childs[idx] != node) idx++;
        if (idx > 0) return {idx - 1, parent};
        node = parent;
    }

    return it;
}

template<class T, size_t K>
bool hasNext(BTreeIt<T, K> it) {
    auto node = it.current;
    size_t i = it.s;

    if (node->childs[i + 1]) return true;

    while (node->parent) {
        auto parent = node->parent;
        size_t idx = 0;
        while (parent->childs[idx] != node) idx++;
        if (idx < K) return true;
        node = parent;
    }

    return false;
}

template<class T, size_t K>
bool hasPrev(BTreeIt<T, K> it) {
    auto node = it.current;
    size_t i = it.s;

    if (node->childs[i]) return true;

    while (node->parent) {
        auto parent = node->parent;
        size_t idx = 0;
        while (parent->childs[idx] != node) idx++;
        if (idx > 0) return true;
        node = parent;
    }

    return false;
}

template<class T, size_t K>
BTreeIt<T, K> begin(BTree<T, K>* root) {
    return leftmost<T, K>(root);
}

int main() {
    const size_t K = 2;

    auto root = new BTree<int, K>;
    root->val[0] = 10;
    root->val[1] = 20;

    auto left = new BTree<int, K>;
    left->val[0] = 5;
    left->val[1] = 7;
    left->parent = root;

    auto right = new BTree<int, K>;
    right->val[0] = 25;
    right->val[1] = 30;
    right->parent = root;

    root->childs[0] = left;
    root->childs[2] = right;

    auto it = begin(root);

    while (true) {
        std::cout << value(it) << " ";
        if (!hasNext(it)) break;
        it = next(it);
    }

    return 0;
}