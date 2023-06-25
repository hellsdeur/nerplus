#ifndef NERPLUS_TABLE_H
#define NERPLUS_TABLE_H

#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <omp.h>

#define THREAD_NUM 4

#define MAX_ROWS 8192
#define MAX_COLS 24

class Table {
public:
    Table(std::string text_filename, std::string regex_filename) {
        this->text_filename = text_filename;
        this->regex_filename = regex_filename;
        load_text();
        load_regex();
    }

    std::string text_filename;
    std::string regex_filename;
    std::string data[MAX_COLS][MAX_ROWS];
    std::string columns[MAX_COLS];
    std::string regex[MAX_COLS];
    std::string line;
    int r = 0;  // number of rows
    int c = 0;  // number of columns

    void load_text();
    void load_regex();
    void print_text(int start, int end);
    void print_columns();
    void print_regex();
    void print_regex_maps();
    void write_csv(const std::string& csv_filename, const std::string& sep);
    static std::string match(const std::string& text, const std::string& pattern, bool multivariate);
};

inline void Table::load_text() {
    std::ifstream text_file(this->text_filename);

    if (text_file.is_open()) {
        while (std::getline(text_file, this->line) && this->r < MAX_ROWS) {
            this->data[0][this->r] = this->line;
            this->r++;
        }
        text_file.close();
        columns[c] = "TEXT";
        c++;
    } else {
        std::cout << "Unable to open file.\n";
    }
}

inline void Table::load_regex() {
    std::ifstream regex_file(this->regex_filename);

    int p = 0;

    if (regex_file.is_open()) {
        while (std::getline(regex_file, this->line) && this->c < MAX_COLS) {
            if (p % 2 == 0) {
                this->columns[c] = this->line;
            } else {
                this->regex[c] = this->line;
                c++;
            }
            p++;
        }
        regex_file.close();
    } else {
        std::cout << "Unable to open file.\n";
    }
}

inline void Table::print_text(int start = 0, int end = MAX_ROWS) {
    if ((start <= end) && (end <= this->r)) {
        for (int i = start; i <= end; i++) {
            std::cout << this->data[0][i] << "\n\n";
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

inline void Table::write_csv(const std::string& csv_filename, const std::string& sep = "|") {
    std::ofstream csv_file(csv_filename);

    if (csv_file.is_open()) {
        for (int i = 0; i < c; i++) {
            csv_file << columns[i];
            if (i < c-1) {
                csv_file << sep;
            }
        }
        csv_file << "\n";

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                csv_file << data[j][i];
                if (j < c-1) {
                    csv_file << sep;
                }
            }
            csv_file << "\n";
        }
    } else {
        std::cout << "Unable to write file.\n";
    }

    csv_file.close();
}

inline std::string Table::match(const std::string& text, const std::string& pattern, bool multivariate = false) {
    std::regex regex_pattern(pattern);
    std::smatch match;
    std::string result;

    if (multivariate) {
        std::string sep = "|";
        bool found_match = false;

        auto it = text.begin();
        while (std::regex_search(it, text.end(), match, regex_pattern)) {
            result += match.str() + sep;
            it = match[0].second;
            found_match = true;
        }
        if (found_match) {
            result.pop_back();
        }
    } else {
        if (std::regex_search(text, match, regex_pattern)) {
            result = match.str();
        }
    }

    return result;
}

#endif //NERPLUS_TABLE_H
