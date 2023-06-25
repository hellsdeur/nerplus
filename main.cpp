#include <iostream>
#include "src/table.h"
#include <omp.h>


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
    double start = omp_get_wtime();

    Table table = Table(text_filename, regex_filename);

//    table.print_regex_maps();

//    table.print_text(0, 10);
    omp_set_num_threads(1);

    #pragma omp parallel
    {
    #pragma omp for
        for (int i = 0; i < table.r; i++) {
            for (int j = 1; j < table.c; j++) {
                table.data[j][i] = table.match(table.data[0][i], table.regex[j]);
            }

        }
        std::cout << "Thread " + std::to_string(omp_get_thread_num()) + " terminou a execução \n";
    }

    double end = omp_get_wtime();

//    for (int i = 0; i < table.c; i++) {
//        std::cout << table.columns[i] << "\n";
//    }


    table.write_csv("./data/result_parallel.csv");

    std::cout << "Tempo de execução: " + std::to_string((end-start));


    return 0;
}
