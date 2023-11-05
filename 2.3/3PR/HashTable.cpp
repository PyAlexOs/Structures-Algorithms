#include "HashTable.h"

HashTable::HashTable() {
    this->size = 5;
    this->filled = 0;

    this->records = new record * [size];
    for (int i = 0; i < this->size; ++i) {
        this->records[i] = nullptr;
    }
}

HashTable::~HashTable() {
    delete[] this->records;
}

size_t hash_key(string key, size_t size) {
    size_t hash = 0;
    for (size_t i = 0; i < key.size(); ++i) {
        hash += ((unsigned char) key[i]) * (i + 1); // for compiler independence
    }
    return (hash % size);
}

bool insert_key(HashTable &table, string key, int position) {
    bool unique = true;
    size_t index = hash_key(key, table.size);
    size_t stop_index = index;
    while (index < table.size && table.records[index] != nullptr) {
        if (table.records[index]->key == key && !table.records[index]->is_deleted) {
            unique = false;
            break;
        }
        index++;
    }
    
    if (index >= table.size && unique) {
        for (index = 0; index < stop_index; ++index) {
            if (table.records[index] != nullptr) {
                if (table.records[index]->key == key && !table.records[index]->is_deleted) {
                    unique = false;
                    break;
                }
            }
            else {
                break;
            }
        }
    }

    if (index < table.size && unique) {
        table.records[index] = new record(key, position);
        if (++table.filled > 0.75 * table.size) {
            rehash(table);
        }
        return true;
    }
    return false;
}

record* find_key(HashTable &table, string key) {
    record* found = nullptr;
    size_t index = hash_key(key, table.size);
    size_t stop_index = index;
    while (index < table.size) {
        if (table.records[index] != nullptr) {
            if (table.records[index]->key == key) {
                if (!table.records[index]->is_deleted) {
                    found = table.records[index];
                    break;
                }
            }
            ++index;
        }
        else {
            break;
        }
    }

    if (found == nullptr) {
        for (index = 0; index < stop_index; ++index) {
            if (table.records[index] != nullptr) {
                if (table.records[index]->key == key) {
                    if (!table.records[index]->is_deleted) {
                        found = table.records[index];
                        break;
                    }
                }
            }
            else {
                break;
            }
        }
    }

    return found;
}

int get_index(HashTable &table, string key) {
    record* found = find_key(table, key);
    if (found != nullptr) {
        return found->position;
    }
    return -1;
}

int delete_key(HashTable &table, string key) {
    record* rubbish = find_key(table, key);
    if (rubbish != nullptr) {
        rubbish->is_deleted = true;
        return rubbish->position;
    }
    return -1;
}

void rehash(HashTable &table) {
    size_t rehashed_size = table.size << 1;
    cout << "В хэш-таблице " << table.filled << " запис(-и/-ей)." << endl;
    cout << "Рехэширование хэш-таблицы с " << table.size << " элементов до " << rehashed_size << " элементов..." << endl;

    record** rehashed_records = new record * [rehashed_size];
    for (size_t i = 0; i < rehashed_size; ++i) {
        rehashed_records[i] = nullptr;
    }

    table.filled = 0;
    for (size_t i = 0; i < table.size; ++i) {
        if (table.records[i] != nullptr && !table.records[i]->is_deleted) {
            size_t new_index = hash_key(table.records[i]->key, rehashed_size);
            size_t stop_index = new_index;
            while (new_index < rehashed_size && rehashed_records[new_index] != nullptr) {
                new_index++;
            }

            if (new_index >= rehashed_size) {
                for (new_index = 0; new_index < stop_index; ++new_index) {
                    if (rehashed_records[new_index] == nullptr) {
                        break;
                    }
                }
            }
            rehashed_records[new_index] = new record(table.records[i]->key, table.records[i]->position);
            table.filled++;
        }
    }
    //printHashTable(table);
    table.size *= 2;
    delete[] table.records;
    table.records = rehashed_records;
    cout << "Рехэширование выполнено успешно." << endl;
}

void printHashTable(const HashTable &table) {
    cout << "|---------------------------------|" << endl;
    for (size_t i = 0; i < table.size; ++i) {
        cout << "| " << i << ": ";
        if (table.records[i] != nullptr) {
            if (!table.records[i]->is_deleted) {
                cout << setw(29) << table.records[i]->key << "|";
            }
            else {
                cout << setw(30) << "DELETED|";
            }
        }
        else {
            cout << setw(30) << "|";
        }
        cout << endl;
    }
    cout << "|---------------------------------|" << endl;
}

int testHashT() {
    HashTable table;
    int position = 0;
    string key;

    while (true) {
        cout << endl << "Выберите действие:" << endl;
        cout << "1. Добавление элемента в таблицу" << endl;
        cout << "2. Поиск элемента в таблице" << endl;
        cout << "3. Удаление элемента из таблицы" << endl;
        cout << "4. Вывод хэш-таблицы" << endl;
        cout << "5. Выйти" << endl;

        int action;
        cin >> action;
        switch (action) {
        case 1: {
            cout << "Введите ключ записи: ";
            cin >> key;
            if (insert_key(table, key, position++)) {
                cout << "Ключ успешно добавлен в хэш-таблицу:" << endl;
                printHashTable(table);
            }
            else {
                cout << "Нарушено условие уникальности ключа, дублирование ключа запрещено." << endl;
            }
            break;
        }

        case 2: {
            cout << "Введите ключ записи: ";
            cin >> key;
            int index = get_index(table, key);
            if (index == -1) {
                cout << "В хэш-таблице не найден элемент с заданным ключом." << endl;
            }
            else {
                cout << "Порядковый номер элемента в двоичном файле: " << index << endl;
            }
            break;
        }

        case 3: {
            cout << "Введите ключ записи: ";
            cin >> key;
            int index = delete_key(table, key);
            if (index == -1) {
                cout << "В хэш-таблице не найден элемент с заданным ключом." << endl;
            }
            else {
                cout << "Элемент с позицией " << index << " удалён." << endl;
                printHashTable(table);
            }
            break;
        }

        case 4: {
            printHashTable(table);
            break;
        }

        default: {
            return 0;
        }
        }
    }

}
