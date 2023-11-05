#pragma once
#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int _value) : value(_value), left(nullptr), right(nullptr) {};
};

struct binTree {
    Node* root;
    binTree() : root(nullptr) {};
    binTree(Node* _root) : root(_root) {};

    bool addNode(Node* new_node);
    static void print(Node* current, char from = ' ', size_t level = 0);
    double mean();
    static size_t count(Node* current);
    void deleteLeft();
    int getLevel(Node* current, int value, int level = -1);
};
