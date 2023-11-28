#pragma once
#include "Node.h"

struct AVLtree {
    Node* root;
    AVLtree() : root(nullptr) {};
    AVLtree(Node* _root) : root(_root) {};

    Node* search(string key);
    int getIndex(string key);
    void add(string _key, int _position);
    int erase(string key);
    void print();
    ~AVLtree();

private:
    Node* searchFrom(string key, Node* current);
    Node* addTo(Node* current, Node* new_node);
    Node* remove(Node* current, string key, int& position);
    Node* removeMin(Node* current);

    size_t getHeight(Node* current);
    void updateHeight(Node* current);
    int getBalance(Node* current);

    Node* saveBalance(Node* current);
    Node* fixRight(Node* current);
    Node* fixLeft(Node* current);

    Node* getMin(Node* from);
    void printSubTree(Node* current, char from = ' ', size_t from_size = 0, size_t level = 0);
    void clear(Node* current);
};
