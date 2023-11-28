#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Node {
    struct record {
        string key;
        int position;
        record(string _key, int _position) : key(_key), position(_position) {};
    } data;
    size_t height;

    Node* left;
    Node* right;
    Node(string _key, int _position) : data(_key, _position), height(1), left(nullptr), right(nullptr) {}; 
};
