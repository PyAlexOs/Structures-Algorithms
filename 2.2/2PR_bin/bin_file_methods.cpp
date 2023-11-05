#include "bin_file_methods.h"

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
    file.seekg((index - 1) * sizeof(word), ios::beg);
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
    int pos = new_word.size();
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
                cout << current.name << " обновлено: " << current.count << endl;
                break;
            }
        }
        file.read((char*)&current, sizeof(word));
    }
}