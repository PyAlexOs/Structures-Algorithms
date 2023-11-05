#include "file_methods.h"

int main()
{
    system("chcp 1251");
    string file, new_file;
    ifstream fin;
    ofstream fout;

    //file = "D:/МИРЭА/СиАОД/2.2/files/test.txt";
    //new_file = "D:/МИРЭА/СиАОД/2.2/files/new.txt";
    
    int action;
    while (true) {
        cout << "Выберите действие:" << endl;
        cout << "1. Напечатать числа из файла" << endl;
        cout << "2. Добавить новое число в конец файла" << endl;
        cout << "3. Найти число в файле по порядковому номеру" << endl;
        cout << "4. Определить количество чисел в файле" << endl;
        cout << "5. Создать новый файл из значений исходного, размещая в каждой строке три числа: исходное, количество цифр в числе, сумму цифр в числе" << endl;
        cout << "6. Выйти" << endl;

        cin >> action;
        if (action != 6) {
            cout << "Введите имя файла: ";
            cin >> file;
        }

        switch (action) {
        case 1:
            fin.open(file, ios::in);
            if (fin.is_open()) {
                print(fin);
                if (!fin) {
                    cout << "Ошибка при выводе чисел из файла в консоль." << endl;
                }
                fin.close();
            }
            else {
                cout << "Файл не найден или не существует." << endl;
            }
            break;

        case 2:
            fout.open(file, ios::out | ios::app);
            if (fout.is_open()) {
                cout << "Введите число для добавления в файл: ";
                int number;
                cin >> number;
                append(fout, number);
                if (!fout) {
                    cout << "Ошибка при добавлении нового числа в файл." << endl;
                }
                else {
                    cout << "Число добавлено в файл." << endl;
                }
                fout.close();
            }
            else {
                cout << "Файл не найден или не существует." << endl;
            }
            break;

        case 3:
            fin.open(file, ios::in);
            if (fin.is_open()) {
                cout << "Введите порядковый номер числа: ";
                int number;
                cin >> number;
                number = get_number(fin, number);

                if (number != INT32_MAX) {
                    cout << "Найденное число: " << number << endl;
                }
                else {
                    cout << "Ошибка при поиске числа по порядковому номеру в файле." << endl;
                }
                fin.close();
            }
            else
                cout << "Файл не найден или не существует." << endl;
            break;

        case 4:
            fin.open(file, ios::in);
            if (fin.is_open()) {
                cout << "Количество чисел в файле: " << count(fin) << endl;
                if (!fin) {
                    cout << "Ошибка при подсчёте количества чисел в файле." << endl;
                }
                fin.close();
            }
            else
                cout << "Файл не найден или не существует." << endl;
            break;

        case 5: {
            cout << "Введите имя нового файла: ";
            cin >> new_file;
            fin.open(file, ios::in);
            if (fin.is_open()) {
                fout.open(new_file, ios::out);
                stats_file(fin, fout);
                if (!fin || !fout) {
                    cout << "Ошибка при создании нового файла." << endl;
                }
                else {
                    cout << "Новый файл успешно создан." << endl;
                }
                fin.close();
                fout.close();
            }
            else
                cout << "Файл не найден или не существует." << endl;
            break;
        }
        default:
            return 0;
        }
    }
}
