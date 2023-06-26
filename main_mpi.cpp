#include <iostream>
//#include <string>
#include "src/table.h"
#include <mpi.h>


int main(int argc, char* argv[]) {

    int process_rank, size;

    double start, end;


    MPI::MPI_Init(&argc, &argv);
    MPI::MPI_Comm_size(MPI::COMM_WORLD, &size);
    MPI::MPI_Comm_rank(MPI::COMM_WORLD, &process_rank);


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


    Table table = Table(text_filename, regex_filename);

    start = MPI_Wtime();



//    printf("Hello World from process %d of %d\n", process_rank, size);

    int div = table.r/size;

    for (int i = process_rank*div; i < (process_rank+1)*div; i++) {
        for (int j = 1; j < table.c; j++) {
            table.data[j][i] = table.match(table.data[0][i], table.regex[j]);
        }

    }

    if (process_rank == 0){

        end = MPI_Wtime();
//        std::cout << "Execution time: " + std::to_string((end-start));

        table.write_csv("./data/result_parallel.csv");

        table.count_matches();

    }

    return 0;
}
