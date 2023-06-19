#include <fstream>
#include <iostream>

//#define MAX_ROWS 1048576
//#define MAX_COLS 16384
#define MAX_ROWS 1000
#define MAX_COLS 64

int main() {
    std::ifstream file("./data/data.csv");
    char sep = ',';
    std::string table[MAX_ROWS][MAX_COLS];
    std::string columns[MAX_COLS];
    std::string line;
    int r = 0;  // number of rows
    int c = 0;  // number of columns
    size_t start_position;
    size_t end_position;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            // header parsing, extract column names
            if (r == 0) {
                start_position = 0;
                end_position = line.find(sep);

                while (end_position != std::string::npos) {
                    columns[c] = line.substr(start_position, end_position-start_position);
                    start_position = end_position + 1;
                    end_position = line.find(sep, start_position);
                    c++;
                }
                columns[c] = line.substr(start_position);
            }
            // data lines parsing, extract columns data
            else {
                start_position = 0;
                end_position = line.find(sep);
                std::cout << line << '\n' << '\n';
            }
            r++;
        }
        file.close();
    } else {
        std::cout << "Unable to open file";
    }

    for (int i = 0; i <= c; i++) {
        std::cout << columns[i] << '\n';
    }
}
