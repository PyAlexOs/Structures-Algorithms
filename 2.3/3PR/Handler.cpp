#include "Handler.h"

void bin2hash(HashTable &table, istream& file) {
	int position = 0;
	word current;

	file.read((char*)&current, sizeof(word));
	while (!file.eof()) {
        if (!insert_key(table, current.name, position++)) {
            cout << "Провалена попытка вставки слова '" << current.name << "' в хэш-таблицу" << endl;
        }
		file.read((char*)&current, sizeof(word));
	}
    //printHashTable(table);
}

word find_word(HashTable &table, istream& file, string key) {
    word current;
	int index = get_index(table, key);
    if (index == -1) {
        current.name[0] = '\0';
    }
    else {
        current = get_word(file, index);
    }
    return current;
}

bool erase_word(HashTable &table, fstream& file, string key, string file_path) {
	int index = delete_key(table, key);
    if (index == -1) {
        return false;
    }

    word last;
	file.seekg(-(int) sizeof(word), ios::end);
    file.read((char*)&last, sizeof(word));

    if (last.name != key) {
        file.seekg(ios::beg);
        file.seekp(index * sizeof(word), ios::beg);
        file.write((char*)&last, sizeof(word));
        find_key(table, last.name)->position = index;
    }
    
    int fh;
    if (_sopen_s(&fh, file_path.c_str(), _O_RDWR, _SH_DENYNO, _S_IREAD | _S_IWRITE) == 0) {
        if (!(_chsize(fh, (_filelength(fh) - sizeof(word))) == 0)) {
            return false;
        }
        _close(fh);
    }
    return true;
}
