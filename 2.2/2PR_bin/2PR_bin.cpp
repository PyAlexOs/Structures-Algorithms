#include "bin_file_methods.h"

int main() {
    system("chcp 1251");
    string text_file, bin_file;
    ifstream fin;
    ofstream fout;
    fstream fios;

    //text_file = "D:/МИРЭА/СиАОД/2.2/files/word_stats_mini.txt";
    //bin_file = "D:/МИРЭА/СиАОД/2.2/files/word_stats_mini.dat";

    int action;
    while (true) {
        cout << "Выберите действие (частотный словарь):" << endl;
        cout << "1. Преобразовать текстовый файл в двоичный" << endl;
        cout << "2. Вывести записи из двоичного файла в текстовый" << endl;
        cout << "3. Вывести записи из двоичного файла в консоль" << endl;
        cout << "4. Получить запись из двоичного файла по порядковому номеру" << endl;
        cout << "5. Удалить запись из двоичного файла по ключу" << endl;
        cout << "6. Определить, какое слово встречалось в тексте чаще всего" << endl;
        cout << "7. Добавить в файл новую запись по слову" << endl;
        cout << "8. Обновить количество вхождений некоторых слов, увеличив их количество на 1" << endl;
        cout << "9. Выйти" << endl;

        cin >> action;
        switch (action) {
        case 1: {
            cout << "Введите имя текстового файла: ";
            cin >> text_file;
            cout << "Введите имя двоичного файла: ";
            cin >> bin_file;
            fin.open(text_file, ios::in);
            if (fin.is_open()) {
                fout.open(bin_file, ios::binary | ios::out);
                text2bin(fin, fout);
                if (!fout) {
                    cout << "Ошибка при записи в файл." << endl;
                    return 1;
                }
                cout << "Двоичный файл успешно записан." << endl;
                fin.close();
                fout.close();
            }
            else {
                cout << "Файл не найден или не существует." << endl;
            }
            break;
        }

        case 2: {
            cout << "Введите имя двоичного файла: ";
            cin >> bin_file;
            cout << "Введите имя текстового файла: ";
            cin >> text_file;
            fin.open(bin_file, ios::binary | ios::in);
            if (fin.is_open()) {
                fout.open(text_file, ios::out);
                bin2text(fin, fout);
                if (fout.bad() || fout.fail()) {
                    cout << "Ошибка при записи в файл." << endl;
                    return 1;
                }
                cout << "Текстовый файл успешно записан." << endl;
                fin.close();
                fout.close();
            }
            else {
                cout << "Файл не найден или не существует." << endl;
            }
            break;
        }

        case 3: {
            cout << "Введите имя двоичного файла: ";
            cin >> bin_file;
            fin.open(bin_file, ios::binary | ios::in);
            if (fin.is_open()) {
                print_bin(fin);
                if (fin.bad()) {
                    cout << "Ошибка при чтении файла." << endl;
                    return 1;
                }
                fin.close();
            }
            else {
                cout << "Файл не найден или не существует." << endl;
            }
            break;
        }

        case 4: {
            cout << "Введите имя двоичного файла: ";
            cin >> bin_file;
            cout << "Введите порядковый номер записи: ";
            int number;
            cin >> number;

            fin.open(bin_file, ios::binary | ios::in);
            if (fin.is_open()) {
                word found = get_word(fin, number);
                if (found.name[0] =='\0') {
                    cout << "Введённый порядковый номер превышает количество записей в файле." << endl;
                }
                else {
                    cout << number << "-ое слово '" << found.name << "' встречено в тексте " << found.count << " раз(-а)." << endl;
                }

                if (fin.bad() || fin.fail()) {
                    cout << "Ошибка при чтении файла." << endl;
                    return 1;
                }
                fin.close();
            }
            else {
                cout << "Файл не найден или не существует." << endl;
            }
            break;
        }

        case 5: {
            cout << "Введите имя двоичного файла: ";
            cin >> bin_file;
            cout << "Введите ключ (слово): ";
            string key;
            cin >> key;

            fios.open(bin_file, ios::binary | ios::in | ios::out);
            if (fios.is_open()) {
                bool status = delete_word(fios, key, bin_file);
                if (fios.bad()) {
                    cout << "Ошибка при чтении файла." << endl;
                    return 1;
                }

                if (!status) {
                    cout << "Не удалось удалить запись по ключу." << endl;
                }
                else {
                    cout << "Запись удалена." << endl;
                }
                fios.close();
            }
            else {
                cout << "Файл не найден или не существует." << endl;
            }
            break;
        }

        case 6: {
            cout << "Введите имя двоичного файла: ";
            cin >> bin_file;
            fin.open(bin_file, ios::binary | ios::in);
            if (fin.is_open()) {
                word best = get_widest(fin);
                if (fin.bad()) {
                    cout << "Ошибка при чтении файла." << endl;
                    return 1;
                }
                cout << "Слово '" << best.name << "' встречалось в тексте чаще всего: " << best.count << " раз(-а)." << endl;
                fin.close();
            }
            else {
                cout << "Файл не найден или не существует." << endl;
            }
            break;
        }

        case 7: {
            cout << "Введите имя двоичного файла: ";
            cin >> bin_file;
            cout << "Введите новое слово для добавления в частотный словарь: ";
            string new_word;
            cin >> new_word;

            fout.open(bin_file, ios::binary | ios::out | ios::app);
            if (fout.is_open()) {
                add_word(fout, new_word);
                if (fout.bad() || fout.fail()) {
                    cout << "Ошибка при чтении файла." << endl;
                    return 1;
                }

                cout << "Слово " << new_word << " успешно записано в конец бинарного файла." << endl;
                fout.close();
            }
            else {
                cout << "Файл не найден или не существует." << endl;
            }
            break;
        }

        case 8: {
            cout << "Введите имя двоичного файла: ";
            cin >> bin_file;
            cout << "Вводите слова, которые необходимо посчитать (чтобы прекратить ввод введите 'end'): " << endl;
            string new_word = "";
            vector <string> words;
            while (new_word != "end") {
                cin >> new_word;
                words.push_back(new_word);
            }
            words.pop_back();

            fios.open(bin_file, ios::binary | ios::in | ios::out);
            if (fios.is_open()) {
                count_words(fios, words);
                if (fios.bad()) {
                    cout << "Ошибка при чтении файла или записи в него." << endl;
                    return 1;
                }

                cout << "Количество вхоождений слов успешно обновлено в бинарном файле. " << endl;
                fout.close();
            }
            else {
                cout << "Файл не найден или не существует." << endl;
            }
            break;
        }

        default: {
            return 0;
        }
        }
    }
}
