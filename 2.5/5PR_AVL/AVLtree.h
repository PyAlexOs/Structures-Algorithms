#pragma once
#include "Node.h"

struct AVLtree {
    Node* root;
    AVLtree() : root(nullptr) {};
    AVLtree(Node* _root) : root(_root) {};

    Node* search(string key);
    int getIndex(string key);
    bool add(string _key, int _position);
    int erase(string key);
    void print();

private:
    Node* searchFrom(string key, Node* current);
    Node* addTo(Node* current, Node* new_node);
    void updateBalance(Node* current);
    void saveBalance(Node* current);
    void fixRR(Node* current);
    void fixLL(Node* current);
    void fixRL(Node* current);
    void fixLR(Node* current);
    static void printSubTree(Node* current, char from = ' ', size_t from_size = 0, size_t level = 0);
};

