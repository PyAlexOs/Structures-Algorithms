#include <iostream>
#include <iomanip>
#include <bitset>
#include <vector>
#include <chrono>
using namespace std;

void task_1() {
    unsigned short num = 0xA02, mask = 0x78;
    cout << "Number 0xA02:               " << bitset<sizeof(short) * 8>(num) << endl;

    num = num | mask;
    cout << "Number 0xA02 with 1-st mask:" << bitset<sizeof(short) * 8>(num) << endl;
    num = num | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6);
    cout << "Number 0xA02 with 2-nd mask:" << bitset<sizeof(short) * 8>(num);
}

void task_2() {
    unsigned short num, mask = 0x1802;
    cout << "Input number:           ";
    cin >> num;
    cout << "                        " << bitset<sizeof(short) * 8>(num) << endl;

    num = num & ~mask;
    cout << "Number with 1-st mask:  " << bitset<sizeof(short) * 8>(num) << endl;
    num = num & ~(1 << 12) & ~(1 << 11) & ~(1 << 1);
    cout << "Number with 2-nd mask:  " << bitset<sizeof(short) * 8>(num);
}

void task_3() {
    unsigned short num, pos = 5;
    cout << "Input number:      ";
    cin >> num;
    cout << "                   " << bitset<sizeof(short) * 8>(num) << endl;

    num = num << pos;
    cout << "Number with mask:  " << bitset<sizeof(short) * 8>(num) << "     " << num;
}

void task_4() {
    unsigned short num, pos = 5;
    cout << "Input number:      ";
    cin >> num;
    cout << "                   " << bitset<sizeof(short) * 8>(num) << endl;

    num = num >> pos;
    cout << "Number with mask:  " << bitset<sizeof(short) * 8>(num) << "     " << num;
}

void task_5() {
    unsigned short num, pos, mask = 0x8000;
    cout << "Input number:      ";
    cin >> num;
    cout << "                   " << bitset<sizeof(short) * 8>(num) << endl;
    
    cout << "Enter the bit number to set '0': ";
    cin >> pos;

    num = num & ~(mask >> ((sizeof(short) * 8 - 1) - pos));
    cout << "Number with mask:  " << bitset<sizeof(short) * 8>(num) << "     " << num;
}

unsigned char* create_array(size_t size) {
    unsigned char* numbers = new unsigned char[(size >> 3) + 1];
    for (size_t i = 0; i <= (size >> 3); ++i) {
        numbers[i] = 0;
    }

    return numbers;
}

void sort_array(unsigned char* &numbers, vector<int>input_nums) {
    for (size_t i = 0; i < input_nums.size(); ++i) {
        numbers[input_nums[i] >> 3] = numbers[input_nums[i] >> 3] | (1 << (input_nums[i] & 7));
    }
}

void get_nums(unsigned char* numbers, vector<int> &output_nums) {
    output_nums.clear();
    unsigned char mask = 1;
    size_t bit;

    for (size_t i = 0; i <= 10000000 >> 3; ++i) {
        bit = 0;
        while (numbers[i] != 0) {
            if ((numbers[i] & mask) != 0) {
                output_nums.push_back((i << 3) + bit);
            }
            numbers[i] >>= 1;
            ++bit;
        }
    }
}

void array_bit_sort() {
    size_t average, num;
    cout << "How many unique numbers we need sort?   ";
    cin >> average;

    vector<int> input_nums(average);
    cout << "Enter numbers to sort:" << endl;
    for (size_t i = 0; i < average; ++i) {
        cin >> input_nums[i];
    }

    auto start = chrono::high_resolution_clock::now();
    unsigned char* numbers = create_array(10000000);
    sort_array(numbers, input_nums);
    get_nums(numbers, input_nums);
    auto end = chrono::high_resolution_clock::now();

    cout << "--------------------------SORTED--------------------------" << endl;
    for (int num : input_nums) {
        cout << num << " ";
    }

    chrono::duration<float> duration = end - start;
    cout << endl << "Time: " << setprecision(4) << duration.count();

    delete[] numbers;
}

void bit_sort() {
    size_t average, num, size = 9000000;
    cout << "How many unique numbers we need sort?   ";
    cin >> average;

    vector<bool> numbers(size);
    vector<int> input_nums;
    cout << "Enter numbers to sort:" << endl;
    for (size_t i = 0; i < average; ++i) {
        cin >> num;
        input_nums.push_back(num - 1000000);
    }

    auto start = chrono::high_resolution_clock::now();
    for (size_t i = 0; i < average; ++i) {
        numbers[input_nums[i]] = true;
    }
    auto end = chrono::high_resolution_clock::now();

    cout << "Sorted:" << endl;
    for (size_t i = 0; i < size; ++i) {
        if (numbers[i]) {
           cout << i + 1000000 << endl;
        }
    }

    chrono::duration<float> duration = end - start;
    cout << endl << "Time: " << setprecision(4) << duration.count();
}

int main()
{
    array_bit_sort();

    return 0;
}
