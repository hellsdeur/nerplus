#include <iostream>
#include <omp.h>
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

    // start of parallel processing
    double begin = omp_get_wtime();

//    omp_set_num_threads(4);

    #pragma omp parallel
    {
    #pragma omp for
        for (int i = 0; i < table.r; i++) {
            for (int j = 1; j < table.c; j++) {
                table.data[j][i] = table.match(table.data[0][i], table.regex[j]);
            }
        }
//        std::cout << "Thread " + std::to_string(omp_get_thread_num()) + " finished.\n";
    }

    double end = omp_get_wtime();

    // end of sequential processing
    double time_spent = end - begin;

    // output
    std::cout << "Execution time: " + std::to_string(time_spent) + '\n';
    table.write_csv("./data/result_parallel_omp.csv");
    table.count_matches();

    return 0;
}
