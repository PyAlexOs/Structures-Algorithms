#pragma once
#include <chrono>
#include "FileMethods.h"
#include "HashTable.h"

void bin2hash(HashTable &table, istream& file);
word find_word(HashTable &table, istream& file, string key);
bool erase_word(HashTable &table, fstream& file, string key, string file_path);
