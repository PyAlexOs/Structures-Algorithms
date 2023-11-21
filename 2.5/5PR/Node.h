#pragma once
#include <iostream>
#include <string>
using namespace std;

struct record {
    string key;
    int position;
    record(string _key, int _position) : key(_key), position(_position) {};
};

struct Node {
    record data;

    Node* left;
    Node* right;
    Node* parent;

    Node(string _key, int _position, Node* _parent) : data(_key, _position), left(nullptr), right(nullptr), parent(_parent) {};
    bool isNeightbor(Node* first, Node* second);
};
