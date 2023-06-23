#ifndef NERPLUS_TABLE_H
#define NERPLUS_TABLE_H

#include <string>
#include <fstream>
#include <iostream>

#define MAX_ROWS 8192
#define MAX_COLS 24

class Table {
private:
    std::string text_filename;
    std::string regex_filename;
    std::string table[MAX_COLS][MAX_ROWS];
    std::string columns[MAX_COLS];
    std::string regex[MAX_COLS];
    std::string line;
    int r = 0;  // number of rows
    int c = 0;  // number of columns

    void load_text();
    void load_regex();

public:
    Table(std::string text_filename, std::string regex_filename) {
        this->text_filename = text_filename;
        this->regex_filename = regex_filename;
        load_text();
        load_regex();

        columns[0] = "text";
    }

    void print_text(int start, int end);
    void print_columns();
    void print_regex();
    void print_regex_maps();
};

// PRIVATE METHODS

inline void Table::load_text() {
    std::ifstream text_file(this->text_filename);

    if (text_file.is_open()) {
        while (std::getline(text_file, this->line) && this->r < MAX_ROWS) {
            this->table[0][this->r] = this->line;
            this->r++;
        }
        text_file.close();
    } else {
        std::cout << "Unable to open file.\n";
    }
}

inline void Table::load_regex() {
    std::ifstream regex_file(this->regex_filename);

    if (regex_file.is_open()) {
        while (std::getline(regex_file, this->line) && this->c < MAX_COLS) {
            if (this->c % 2 == 0) {
                this->columns[this->c/2] = this->line;
            } else {
                this->regex[this->c/2] = this->line;
            }
            this->c++;
        }
        this->c = this->c / 2;
        regex_file.close();
    } else {
        std::cout << "Unable to open file.\n";
    }
}

// PUBLIC METHODS

inline void Table::print_text(int start = 0, int end = MAX_ROWS) {
    if ((start <= end) && (end <= this->r)) {
        for (int i = start; i <= end; i++) {
            std::cout << this->table[0][i] << "\n\n";
        }
    } else {
        std::cout << "Invalid index.\n";
    }
}

inline void Table::print_columns() {
    for (int i = 0; i < this->c; i++) {
        std::cout << this->columns[i] << "\n";
    }
    std::cout << "\n";
}

inline void Table::print_regex() {
    for (int i = 0; i < this->c; i++) {
        std::cout << this->regex[i] << "\n";
    }
    std::cout << "\n";
}

inline void Table::print_regex_maps() {
    for (int i = 0; i < this->c; i++) {
        std::cout << columns[i] << ": " << regex[i] << "\n";
    }
    std::cout << "\n";
}

#endif //NERPLUS_TABLE_H
