#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <io.h>
#include <fcntl.h>
#include "AVLtree.h"

struct word {
    char name[30];
    unsigned int count;
};

void text2bin(istream& text_file, ostream& bin_file);
void bin2tree(AVLtree& tree, istream& file, int& position);
word findWord(AVLtree& tree, istream& file, string key);
void addWord(AVLtree& tree, ostream& file, string key, unsigned int count, int& position);
bool eraseWord(AVLtree& tree, fstream& file, string key, string file_path);
