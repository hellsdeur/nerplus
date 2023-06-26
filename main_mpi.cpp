#include <iostream>
#include <mpi.h>
#include "src/table.h"

int main(int argc, char* argv[]) {
    // get necessary filenames
    std::string text_filename;
    std::string regex_filename;

    if (argc == 3) {
        text_filename = argv[1];
        regex_filename = argv[2];
    } else {
        std::cout << "Please, enter a text file and a regex file as parameters.\n";
        return 0;
    }

    // loading data
    Table table = Table(text_filename, regex_filename);

    // start of parallel processing
    double begin = MPI_Wtime();

    MPI::Init(argc, argv);
    int size = MPI::COMM_WORLD.Get_size();
    int process_rank = MPI::COMM_WORLD.Get_rank();

    printf("Hello World from process %d of %d\n", process_rank, size);

//    int div = table.r/size;
//
//    for (int i = process_rank*div; i < (process_rank+1)*div; i++) {
//        for (int j = 1; j < table.c; j++) {
//            table.data[j][i] = table.match(table.data[0][i], table.regex[j]);
//        }
//    }

//    if (process_rank == 0) {
//
//    }

    MPI::Finalize();

    double end = omp_get_wtime();

    // end of sequential processing
    double time_spent = end - begin;

    // output
    std::cout << "Execution time: " + std::to_string(time_spent);
//    table.write_csv("./data/result_parallel_omp.csv");
    table.count_matches();

    return 0;
}
