#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <io.h>
#include <fcntl.h>
using namespace std;

struct word {
    char name[30];
    unsigned int count;
};

void text2bin(istream& text_file, ostream& bin_file);
void bin2text(istream& bin_file, ostream& text_file);
void print_bin(istream& file);
word get_word(istream& file, int index);
bool delete_word(fstream& file, string key, string file_path);
word get_widest(istream& file);
void add_word(ostream& file, string new_word);
void count_words(fstream& file, vector<string> words);
