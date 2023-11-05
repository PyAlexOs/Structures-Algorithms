#include <iostream>
#include <bitset>
using namespace std;

int main() {
    cout << "Input number: ";
    int x;
    cin >> x;

    cout << "Input number of bits: ";
    int n;
    cin >> n;

    cout << "Input start position: ";
    int p;
    cin >> p;

    cout << "Input number:  " << bitset<sizeof(int) * 8>(x) << endl;
    int maska = ((1u << n) - 1) << p;
    x ^= maska;
    cout << "Mask:          " << bitset<sizeof(int) * 8>(maska) << endl;
    cout << "New number:    " << bitset<sizeof(int) * 8>(x) << endl;
}
