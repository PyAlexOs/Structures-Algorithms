#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <io.h>
#include <fcntl.h>
#include "binTree.h"

struct word {
    char name[30];
    unsigned int count;
};

void text2bin(istream& text_file, ostream& bin_file);
void bin2tree(binTree& tree, istream& file, int& position);
word findWord(binTree& tree, istream& file, string key);
void addWord(binTree& tree, ostream& file, string key, unsigned int count, int& position);
bool eraseWord(binTree& tree, fstream& file, string key, string file_path);
