#include <iostream>
#include "src/table.h"

int main(int argc, char* argv[]) {
    std::string text_filename;
    std::string regex_filename;

    if (argc == 3) {
        text_filename = argv[1];
        regex_filename = argv[2];
    } else {
        std::cout << "Please, enter a text file and a regex file as parameters.\n";
        return 0;
    }

    Table table = Table(text_filename, regex_filename);

//    table.print_regex_maps();

//    table.print_text(0, 10);

    for (int i = 0; i < table.r; i++) {
        for (int j = 1; j < table.c; j++) {
            table.data[j][i] = table.match(table.data[0][i], table.regex[j-1]);
        }
    }

//    for (int i = 0; i < table.c; i++) {
//        std::cout << table.columns[i] << "\n";
//    }

    table.write_csv("./data/result.csv");

    return 0;
}
