﻿#include "fileMethods.h"
#include <chrono>

int main() {
	system("chcp 1251");
	string text_file, bin_file;
	ifstream fin;
	ofstream fout;
	fstream file;

	//D:/MIREA/DataProccessingStructuresAlgorithms/2.5/files/test.txt
	//D:/MIREA/DataProccessingStructuresAlgorithms/2.5/files/test.dat

	//D:/MIREA/DataProccessingStructuresAlgorithms/2.5/files/data.txt
	//D:/MIREA/DataProccessingStructuresAlgorithms/2.5/files/data.dat

	binTree* tree = new binTree();
	int position = 0;
	int action;
	while (true)
	{
		cout << endl << "Выберите действие:" << endl;
		cout << "1. Преобразование текстового файла в двоичный" << endl;
		cout << "2. Перевод двоичного файла в БДП" << endl;
		cout << "3. Поиск узла в БДП по ключу и вывод из двоичного файла" << endl;
		cout << "4. Добавление узла в БДП и двоичный файл по ключу" << endl;
		cout << "5. Удаление записи из БДП и двоичного файла" << endl;
		cout << "6. Вывод БДП" << endl;
		cout << "7. Выйти" << endl;

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
				if (fin.bad() || fout.bad()) {
					cout << "Ошибка при создании двоичного файла из текстового." << endl;
					return 1;
				}
				cout << "Двоичный файл успешно создан." << endl;
				fin.close();
				fout.close();
			}

			else {
				cout << "Текстовый файл не найден или не существует." << endl;
			}
			break;
		}

		case 2: {
			cout << "Введите имя двоичного файла: ";
			cin >> bin_file;
			fin.open(bin_file, ios::binary | ios::in);

			if (fin.is_open()) {
				bin2tree(*tree, fin, position);
				if (fin.bad()) {
					cout << "Ошибка создания БДП из данных двоичного файла." << endl;
					return 1;
				}
				cout << "БДП успешно создано." << endl;
				fin.close();
			}

			else {
				cout << "Двоичный файл не найден или не существует." << endl;
			}
			break;
		}

		case 3: {
			cout << "Введите имя двоичного файла: ";
			cin >> bin_file;
			fin.open(bin_file, ios::binary | ios::in);

			if (fin.is_open()) {
				string key;
				cout << "Введите слово для поиска: ";
				cin >> key;

				auto start = chrono::high_resolution_clock::now();
				word found = findWord(*tree, fin, key);
				auto end = chrono::high_resolution_clock::now();

				cout << endl << "--------------------------------------" << endl;
				cout << "Время поиска: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() / 1e6 << " ms";
				cout << endl << "--------------------------------------" << endl << endl;

				if (fin.bad()) {
					cout << "Ошибка при поиске записи в файле." << endl;
					return 1;
				}

				if (found.name[0] != '\0') {
					cout << "Слово '" << found.name << "' встретилось в тексте " << found.count << " раз(-а)." << endl;
				}
				else {
					cout << "Запись не найдена." << endl;
				}
				fin.close();
			}

			else {
				cout << "Двоичный файл не найден или не существует." << endl;
			}
			break;
		}

		case 4: {
			cout << "Введите имя двоичного файла: ";
			cin >> bin_file;
			file.open(bin_file, ios::out | ios::app | ios::binary);
			if (file.is_open()) {
				string key;
				unsigned int count;
				cout << "Введите слово: ";
				cin >> key;
				cout << "Введите количество вхождений в текст: ";
				cin >> count;

				addWord(*tree, file, key, count, position);
				if (fin.bad()) {
					cout << "Ошибка при добавлении слова в файл." << endl;
					return 1;
				}
				cout << "Запись успешно удалена." << endl;
				file.close();
			}

			else {
				cout << "Двоичный файл не найден или не существует." << endl;
			}
			break;
		}

		case 5: {
			cout << "Введите имя двоичного файла: ";
			cin >> bin_file;
			file.open(bin_file, ios::in | ios::out | ios::binary);
			if (file.is_open()) {
				string key;
				cout << "Введите слово: ";
				cin >> key;
				bool status = eraseWord(*tree, file, key, bin_file);
				if (fin.bad()) {
					cout << "Ошибка при удалении слова из файла." << endl;
					return 1;
				}

				if (status) {
					cout << "Запись успешно удалена." << endl;
					position--;
				}
				else {
					cout << "Запись с таким ключом не найдена." << endl;
				}
				file.close();
			}

			else {
				cout << "Двоичный файл не найден или не существует." << endl;
			}
			break;
		}

		case 6: {
			tree->print();
			break;
		}

		default: {
			delete tree;
			return 0;
		}
		}
	}
}
