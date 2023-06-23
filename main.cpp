#include <fstream>
#include <iostream>

#define MAX_ROWS 8192
#define MAX_COLS 24

int main() {
    std::ifstream text_file("./data/data.txt");
    std::ifstream regex_file("./data/regex.txt");
    std::string table[MAX_COLS][MAX_ROWS];
    std::string columns[MAX_COLS];
    std::string regex[MAX_COLS];
    std::string line;
    int r = 0;  // number of rows
    int c = 0;  // number of columns

    columns[0] = "text";

    if (text_file.is_open()) {
        while (std::getline(text_file, line) && r < MAX_ROWS) {
            table[0][r] = line;
            r++;
        }
        text_file.close();
    } else {
        std::cout << "Unable to open file.\n";
    }

    if (regex_file.is_open()) {
        while (std::getline(regex_file, line) && c < MAX_COLS) {
            if (c % 2 == 0) {
                columns[c/2] = line;
            } else {
                regex[c/2] = line;
            }
            c++;
        }
        c = c / 2;
        regex_file.close();
    } else {
        std::cout << "Unable to open file.\n";
    }

    for (int i = 0; i < c; i++) {
        std::cout << columns[i] << ": " << regex[i] << "\n";
    }
    std::cout << "\n";

    for (int i = 0; i < 10; i++) {
        std::cout << table[0][i] << "\n\n";
    }
}
