#include "FileMethods.h"

void text2bin(istream& text_file, ostream& bin_file) {
    while (!text_file.eof()) {
        word current;
        int i = 0;

        do {
            text_file.get(current.name[i]);
        } while (current.name[i++] != '\n');
        current.name[i - 1] = '\0';

        text_file >> current.count;
        text_file.get();

        bin_file.write((char*)&current, sizeof(word));
    }
}

void bin2text(istream& bin_file, ostream& text_file) {
    word current;
    bin_file.read((char*)&current, sizeof(word));
    while (!bin_file.eof()) {
        text_file << current.name << "\n" << current.count;
        bin_file.read((char*)&current, sizeof(word));

        if (!bin_file.eof()) {
            text_file << "\n";
        }
    }
}

void print_bin(istream& file) {
    word current;
    int n = 1;
    file.read((char*)&current, sizeof(word));
    while (!file.eof()) {
        cout << n++ << ". " << current.name << ": " << current.count << endl;
        file.read((char*)&current, sizeof(word));
    }
}

word get_word(istream& file, int index) {
    word current;
    file.seekg((index) * sizeof(word), ios::beg);
    file.read((char*)&current, sizeof(word));

    if (file.bad() || file.fail()) {
        current.name[0] = '\0';
    }
    return current;
}

bool delete_word(fstream& file, string key, string file_path) {
    word last, current;
    bool status = false;

    file.seekg(-(int)sizeof(word), ios::end);
    file.read((char*)&last, sizeof(word));

    // Record couldn't be deleted if pointer would still be in that part of file
    if (last.name != key) {
        file.seekg(ios::beg);
        file.read((char*)&current, sizeof(word));
        while (!file.eof()) {
            if (current.name == key) {
                file.seekp(-(int)sizeof(word), ios::cur);
                file.write((char*)&last, sizeof(word));
                status = true;
                break;
            }
            file.read((char*)&current, sizeof(word));
        }
    }
    else {
        status = true;
    }

    if (status) {
        int fh;
        if (_sopen_s(&fh, file_path.c_str(), _O_RDWR, _SH_DENYNO, _S_IREAD | _S_IWRITE) == 0) {
            if (!(_chsize(fh, (_filelength(fh) - sizeof(word))) == 0)) {
                status = false;
            }
            _close(fh);
        }
        /*
        * FOR UNIX: CLOSE FILE, THAN RESIZE IT
        #include <filesystem>
        auto p = filesystem::path(file_path);
        filesystem::resize_file(p, (size - 1) * sizeof(word));
        */
    }
    return status;
}

word get_widest(istream& file) {
    word current, best;
    best.count = 0;

    file.read((char*)&current, sizeof(word));
    while (!file.eof()) {
        if (current.count > best.count) {
            best.count = current.count;
            strcpy_s(best.name, current.name);
        }
        file.read((char*)&current, sizeof(word));
    }

    return best;
}

void add_word(ostream& file, string new_word) {
    word current;
    size_t pos = new_word.size();
    strncpy(current.name, new_word.c_str(), pos);
    current.name[pos] = '\0';
    current.count = 0;
    file.write((char*)&current, sizeof(word));
}

void count_words(fstream& file, vector<string> words) {
    word current;
    file.read((char*)&current, sizeof(word));
    while (!file.eof()) {
        for (string w : words) {
            if (w == current.name) {
                ++current.count;
                file.seekp(-(int)sizeof(word), ios::cur);
                file.write((char*)&current, sizeof(word));
                file.seekg(sizeof(word), ios::cur);
                cout << current.name << " ���������: " << current.count << endl;
                break;
            }
        }
        file.read((char*)&current, sizeof(word));
    }
}

int testBinF() {
    string text_file, bin_file;
    ifstream fin;
    ofstream fout;
    fstream fios;

    int action;
    while (true) {
        cout << endl << "�������� ��������:" << endl;
        cout << "1. ������������� ��������� ���� � ��������" << endl;
        cout << "2. ������� ������ �� ��������� ����� � ���������" << endl;
        cout << "3. ������� ������ �� ��������� ����� � �������" << endl;
        cout << "4. �������� ������ �� ��������� ����� �� ����������� ������" << endl;
        cout << "5. ������� ������ �� ��������� ����� �� �����" << endl;
        cout << "6. ����������, ����� ����� ����������� � ������ ���� �����" << endl;
        cout << "7. �������� � ���� ����� ������ �� �����" << endl;
        cout << "8. �������� ���������� ��������� ��������� ����, �������� �� ���������� �� 1" << endl;
        cout << "9. �����" << endl;

        cin >> action;
        switch (action) {
        case 1: {
            cout << "������� ��� ���������� �����: ";
            cin >> text_file;
            cout << "������� ��� ��������� �����: ";
            cin >> bin_file;
            fin.open(text_file, ios::in);
            if (fin.is_open()) {
                fout.open(bin_file, ios::binary | ios::out);
                text2bin(fin, fout);
                if (!fout) {
                    cout << "������ ��� ������ � ����." << endl;
                    return 1;
                }
                cout << "�������� ���� ������� �������." << endl;
                fin.close();
                fout.close();
            }
            else {
                cout << "���� �� ������ ��� �� ����������." << endl;
            }
            break;
        }

        case 2: {
            cout << "������� ��� ��������� �����: ";
            cin >> bin_file;
            cout << "������� ��� ���������� �����: ";
            cin >> text_file;
            fin.open(bin_file, ios::binary | ios::in);
            if (fin.is_open()) {
                fout.open(text_file, ios::out);
                bin2text(fin, fout);
                if (fout.bad() || fout.fail()) {
                    cout << "������ ��� ������ � ����." << endl;
                    return 1;
                }
                cout << "��������� ���� ������� �������." << endl;
                fin.close();
                fout.close();
            }
            else {
                cout << "���� �� ������ ��� �� ����������." << endl;
            }
            break;
        }

        case 3: {
            cout << "������� ��� ��������� �����: ";
            cin >> bin_file;
            fin.open(bin_file, ios::binary | ios::in);
            if (fin.is_open()) {
                print_bin(fin);
                if (fin.bad()) {
                    cout << "������ ��� ������ �����." << endl;
                    return 1;
                }
                fin.close();
            }
            else {
                cout << "���� �� ������ ��� �� ����������." << endl;
            }
            break;
        }

        case 4: {
            cout << "������� ��� ��������� �����: ";
            cin >> bin_file;
            cout << "������� ���������� ����� ������: ";
            int number;
            cin >> number;

            fin.open(bin_file, ios::binary | ios::in);
            if (fin.is_open()) {
                word found = get_word(fin, number);
                if (found.name[0] == '\0') {
                    cout << "�������� ���������� ����� ��������� ���������� ������� � �����." << endl;
                }
                else {
                    cout << number << "-�� ����� '" << found.name << "' ��������� � ������ " << found.count << " ���(-�)." << endl;
                }

                if (fin.bad() || fin.fail()) {
                    cout << "������ ��� ������ �����." << endl;
                    return 1;
                }
                fin.close();
            }
            else {
                cout << "���� �� ������ ��� �� ����������." << endl;
            }
            break;
        }

        case 5: {
            cout << "������� ��� ��������� �����: ";
            cin >> bin_file;
            cout << "������� ���� (�����): ";
            string key;
            cin >> key;

            fios.open(bin_file, ios::binary | ios::in | ios::out);
            if (fios.is_open()) {
                bool status = delete_word(fios, key, bin_file);
                if (fios.bad()) {
                    cout << "������ ��� ������ �����." << endl;
                    return 1;
                }

                if (!status) {
                    cout << "�� ������� ������� ������ �� �����." << endl;
                }
                else {
                    cout << "������ �������." << endl;
                }
                fios.close();
            }
            else {
                cout << "���� �� ������ ��� �� ����������." << endl;
            }
            break;
        }

        case 6: {
            cout << "������� ��� ��������� �����: ";
            cin >> bin_file;
            fin.open(bin_file, ios::binary | ios::in);
            if (fin.is_open()) {
                word best = get_widest(fin);
                if (fin.bad()) {
                    cout << "������ ��� ������ �����." << endl;
                    return 1;
                }
                cout << "����� '" << best.name << "' ����������� � ������ ���� �����: " << best.count << " ���(-�)." << endl;
                fin.close();
            }
            else {
                cout << "���� �� ������ ��� �� ����������." << endl;
            }
            break;
        }

        case 7: {
            cout << "������� ��� ��������� �����: ";
            cin >> bin_file;
            cout << "������� ����� ����� ��� ���������� � ��������� �������: ";
            string new_word;
            cin >> new_word;

            fout.open(bin_file, ios::binary | ios::out | ios::app);
            if (fout.is_open()) {
                add_word(fout, new_word);
                if (fout.bad() || fout.fail()) {
                    cout << "������ ��� ������ �����." << endl;
                    return 1;
                }

                cout << "����� " << new_word << " ������� �������� � ����� ��������� �����." << endl;
                fout.close();
            }
            else {
                cout << "���� �� ������ ��� �� ����������." << endl;
            }
            break;
        }

        case 8: {
            cout << "������� ��� ��������� �����: ";
            cin >> bin_file;
            cout << "������� �����, ������� ���������� ��������� (����� ���������� ���� ������� 'end'): " << endl;
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
                    cout << "������ ��� ������ ����� ��� ������ � ����." << endl;
                    return 1;
                }

                cout << "���������� ���������� ���� ������� ��������� � �������� �����. " << endl;
                fout.close();
            }
            else {
                cout << "���� �� ������ ��� �� ����������." << endl;
            }
            break;
        }

        default: {
            return 0;
        }
        }
    }
}