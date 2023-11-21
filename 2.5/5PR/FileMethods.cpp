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

void bin2tree(binTree& tree, istream& file) {
    int position = 0;
    word current;

    file.read((char*)&current, sizeof(word));
    while (!file.eof()) {
        if (!tree.add(current.name, position++)) {
            cout << "Провалена попытка добавления слова '" << current.name << "' в БДП." << endl;
        }
        file.read((char*)&current, sizeof(word));
    }
}

word getWord(istream& file, int index) {
    word current;
    file.seekg((index) * sizeof(word), ios::beg);
    file.read((char*)&current, sizeof(word));

    if (file.bad() || file.fail()) {
        current.name[0] = '\0';
    }
    return current;
}

word findWord(binTree& tree, istream& file, string key) {
    word current;


    int index = tree.getIndex(key);
    if (index == -1) {
        current.name[0] = '\0';
    }
    else {
        current = getWord(file, index);
    }
    return current;
}

bool eraseWord(binTree& tree, fstream& file, string key, string file_path) {
    int index = tree.erase(key);
    if (index == -1) {
        return false;
    }

    word last;
    file.seekg(-(int)sizeof(word), ios::end);
    file.read((char*)&last, sizeof(word));

    if (last.name != key) {
        // Record couldn't be deleted if pointer would still be in that part of file
        file.seekg(ios::beg);
        file.seekp(index * sizeof(word), ios::beg);
        file.write((char*)&last, sizeof(word));
        tree.search(last.name)->data.position = index;
    }

    int fh;
    if (_sopen_s(&fh, file_path.c_str(), _O_RDWR, _SH_DENYNO, _S_IREAD | _S_IWRITE) == 0) {
        if (!(_chsize(fh, (_filelength(fh) - sizeof(word))) == 0)) {
            return false;
        }
        _close(fh);
    }

    /*
        * FOR UNIX: CLOSE FILE, THAN RESIZE IT
        #include <filesystem>
        auto p = filesystem::path(file_path);
        filesystem::resize_file(p, (size - 1) * sizeof(word));
        */

    return true;
}
