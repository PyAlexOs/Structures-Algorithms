#pragma once
#include "Node.h"

struct binTree {
    Node* root;
    binTree() : root(nullptr) {};
    binTree(Node* _root) : root(_root) {};
    ~binTree();

    Node* search(string key);
    int getIndex(string key);
    bool add(string _key, int _position);
    int erase(string key);
    void print();

private:
    Node* searchFrom(string key, Node* current);
    bool addTo(Node* current, Node* new_node);
    Node* getMax(Node* from);
    Node* getMin(Node* from);
    static void printSubTree(Node* current, char from = ' ', size_t from_size = 0, size_t level = 0);
    void clear(Node* current);
};
