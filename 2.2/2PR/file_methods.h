#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void print(istream& file);
void append(ostream& file, int new_number);
int get_number(istream& file, int index);
int count(istream& file);
void stats_file(istream& file, ostream& new_file);
