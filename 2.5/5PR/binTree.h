#pragma once
#include "Node.h"

struct binTree {
    Node* root;
    binTree() : root(nullptr) {};
    binTree(Node* _root) : root(_root) {};
    ~binTree();

    Node* search(string key);
    int getIndex(string key);
    void add(string _key, int _position);
    int erase(string key);
    void print();

private:
    Node* searchFrom(Node* current, string key);
    Node* addTo(Node* current, Node* new_node);
    Node* remove(Node* current, string key, int& position);
    Node* removeMin(Node* current);

    Node* getMin(Node* from);
    static void printSubTree(Node* current, char from = ' ', size_t from_size = 0, size_t level = 0);
    void clear(Node* current);
};
