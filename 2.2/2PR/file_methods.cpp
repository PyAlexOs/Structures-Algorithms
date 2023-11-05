#include "file_methods.h"

void print(istream& file) {
    int number;
    while (!file.eof()) {
        file >> number;
        cout << number << " ";
    }
    cout << endl;
}

void append(ostream& file, int new_number) {
    file << "\n" << new_number;
}

int get_number(istream& file, int index) {
    int num = INT32_MAX, i = 0;
    while (i <= index && !file.eof()) {
        file >> num;
        i++;
    }

    if (i != index) {
        return INT32_MAX;
    }
    return num;
}

int count(istream& file) {
    int average = 0, current;
    while (!file.eof()) {
        file >> current;
        ++average;
    }

    return average;
}

void stats_file(istream& file, ostream& new_file) {
    int number, sum;
    while (!file.eof()) {
        file >> number;
        new_file << number << " " << to_string(number).length() << " ";

        sum = 0;
        while (number > 0) {
            sum += number % 10;
            number /= 10;
        }

        new_file << sum << endl;
    }
}