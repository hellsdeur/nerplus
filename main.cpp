#include <iostream>
#include <time.h>
#include "src/table.h"

int main(int argc, char* argv[]) {
    // get necessary filenames
    std::string text_filename;
    std::string regex_filename;

    if (argc >= 3) {
        text_filename = argv[1];
        regex_filename = argv[2];
    } else {
        std::cout << "Please, enter a text file and a regex file as parameters.\n";
        return 0;
    }

    // loading data
    Table table = Table(text_filename, regex_filename);

    // start of sequential processing
    clock_t begin = clock();

    for (int i = 0; i < table.r; i++) {
        for (int j = 1; j < table.c; j++) {
            table.data[j][i] = table.match(table.data[0][i], table.regex[j]);
        }
    }

    clock_t end = clock();

    // end of sequential processing
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    // output
    std::cout << "Execution time: " + std::to_string(time_spent) + "\n";
    table.write_csv("./data/result_sequential.csv");
    table.count_matches();

    return 0;
}
