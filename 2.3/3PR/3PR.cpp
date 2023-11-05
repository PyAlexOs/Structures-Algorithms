#include "Handler.h"

int main() {
	system("chcp 1251");
	string text_file, bin_file;
	ifstream fin;
	ofstream fout;
	fstream file;

	//D:/МИРЭА/СиАОД/2.3/files/test.txt
	//D:/МИРЭА/СиАОД/2.3/files/test.dat

	//D:/МИРЭА/СиАОД/2.3/files/data.txt
	//D:/МИРЭА/СиАОД/2.3/files/data.dat

	HashTable table = HashTable();
	int action;
	while (true)
	{
		cout << endl << "Выберите действие:" << endl;
		cout << "1. Преобразование текстового файла в двоичный" << endl;
		cout << "2. Перевод двоичного файла в хэш-таблицу" << endl;
		cout << "3. Поиск записи в хэш-таблице и вывод из двоичного файла" << endl;
		cout << "4. Удаление записи из хэш-таблицы и двоичного файла" << endl;
		cout << "5. Вывод хэш-таблицы" << endl;
		cout << "6. Вывод бинарного файла" << endl;
		cout << "7. Тестирование модуля управления хэш-таблицей" << endl;
		cout << "8. Тестирование модуля управления бинарным файлом" << endl;
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
				bin2hash(table, fin);
				if (fin.bad()) {
					cout << "Ошибка создания хэш-таблицы из данных двоичного файла." << endl;
					return 1;
				}
				cout << "Хэш-таблица успешно создана." << endl;
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
				word found = find_word(table, fin, key);
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
			file.open(bin_file, ios::in | ios::out | ios::binary);
			if (file.is_open()) {
				string key;
				cout << "Введите слово: ";
				cin >> key;
				bool status = erase_word(table, file, key, bin_file);
				if (fin.bad()) {
					cout << "Ошибка при удалении слова из файла." << endl;
					return 1;
				}

				if (status) {
					cout << "Запись успешно удалена." << endl;
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

		case 5: {
			printHashTable(table);
			break;
		}

		case 6: {
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
				cout << "Двоичный файл не найден или не существует." << endl;
			}
			break;
		}

		case 7: {
			return testHashT();
			break;
		}

		case 8: {
			return testBinF();
			break;
		}

		default: {
			return 0;
		}
		}
	}
}