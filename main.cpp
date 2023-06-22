#include <fstream>
#include <iostream>

#define MAX_ROWS 8192
#define MAX_COLS 24

int main() {
    std::ifstream file("./data/data.tsv");
    char sep = '|';
    std::string table[MAX_COLS][MAX_ROWS];
    std::string columns[MAX_COLS];
    std::string line;
    int r = 0;  // number of rows
    int c = 0;  // number of columns
    size_t start_position;
    size_t end_position;

    if (file.is_open()) {
        while (std::getline(file, line) && r < MAX_ROWS) {
            c = 0;                            // index of columns
            start_position = 0;               // position to start looking for sep
            end_position = line.find(sep); // position where sep is found

            while (end_position != std::string::npos) {
                // extract substring from the current start until the number of character up until sep
                std::string text = line.substr(start_position, end_position-start_position);

                // store in columns if first line, store in table otherwise
                if (r == 0)
                    columns[c] = text;
                else
                    table[c][r] = text;

                // start is positioned after sep, end is the next sep
                start_position = end_position + 1;
                end_position = line.find(sep, start_position);
                c++;
            }

            // store last column after last sep
            if (r == 0)
                columns[c] = line.substr(start_position);
            else
                table[c][r] = line.substr(start_position);

            r++;
        }
        file.close();
    } else {
        std::cout << "Unable to open file";
    }

    for (int i = 0; i < MAX_ROWS; i++) {
        std::cout << table[0][i] << "\n\n";
    }
}
