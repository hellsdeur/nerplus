#include <iostream>
#include "src/table.h"

int main(int argc, char* argv[]) {
    std::string text_filename;
    std::string regex_filename;

    if (argc == 3) {
        text_filename = argv[1];
        regex_filename = argv[2];
    } else {
        std::cout << "Please, enter a text file and a regex file as parameters\n";
        return 0;
    }

    Table table = Table(text_filename, regex_filename);

    table.print_regex_maps();

    table.print_text(0, 10);

    return 0;
}
