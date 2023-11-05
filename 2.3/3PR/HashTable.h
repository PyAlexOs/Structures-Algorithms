#pragma once
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct record {
    string key;
    int position;
    bool is_deleted;

    record() : key(""), position(-1), is_deleted(false) {};
    record(string _key, int _position) : key(_key), position(_position), is_deleted(false) {};
};

struct HashTable {
    size_t size;
    size_t filled;
    record** records;

    HashTable();
    ~HashTable();
};

size_t hash_key(string key, size_t size);
bool insert_key(HashTable &table, string key, int position);
record* find_key(HashTable &table, string key);
int get_index(HashTable &table, string key);
int delete_key(HashTable &table, string key);
void rehash(HashTable &table);
void printHashTable(const HashTable &table);
int testHashT();
