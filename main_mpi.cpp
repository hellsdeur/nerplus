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


    MPI::Init(argc, argv);
    int size = MPI::COMM_WORLD.Get_size();
    int process_rank = MPI::COMM_WORLD.Get_rank();

//    printf("Hello World from process %d of %d\n", process_rank, size);

    double begin = MPI_Wtime();

    int div = table.r/size;

    for (int i = process_rank*div; i < (process_rank+1)*div; i++) {
        for (int j = 1; j < table.c; j++) {
            table.data[j][i] = table.match(table.data[0][i], table.regex[j]);
        }
    }

    if (process_rank == 0) {

        for (int i = (process_rank+1)*div; i < table.r; i++) {
            for (int j = 1; j < table.c; j++) {
                MPI::Status status;
                MPI::COMM_WORLD.Probe(1, (i*100+j), status);
                int l = status.Get_count(MPI::CHAR);
                char *buf = new char[l];
                MPI::COMM_WORLD.Recv(buf, l, MPI::CHAR, 1, (i*100+j), status);
                std::string bla1(buf, l);

//                std::cout << bla1 + '\n';
                table.data[j][i] = bla1;
                delete [] buf;
        }
    }


    }
    else{
        for (int i = process_rank*div; i < (process_rank+1)*div; i++)
            for (int j = 1; j < table.c; j++)
            MPI::COMM_WORLD.Send(table.data[j][i].c_str(), table.data[j][i].length(), MPI::CHAR, 0, (i*100+j));

    }



    MPI::Finalize();

    double end = MPI_Wtime();

    // end of sequential processing
    double time_spent = end - begin;

    // output
    if (process_rank==0){
        std::cout << "Execution time: " + std::to_string(time_spent) + "\n";
        table.write_csv("./data/result_parallel_mpi.csv");
        table.count_matches();

//        char a[] = { 'C', 'O', 'D', 'E' };
//        table.data[2][999] = a;
//        std::cout << table.data[2][999];


    }


    return 0;
}
