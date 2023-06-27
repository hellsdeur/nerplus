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

    double begin_total = MPI_Wtime();
    double begin_proc = MPI_Wtime();

    MPI::Init(argc, argv);
    int size = MPI::COMM_WORLD.Get_size();
    int process_rank = MPI::COMM_WORLD.Get_rank();


    int div = MAX_ROWS/size;
    if ((div*size) < MAX_ROWS)
        div++;

//    printf("div %d\n", div);



    for (int i = process_rank*div; ((i < (process_rank+1)*div) && (i <MAX_ROWS)); i++) {
        for (int j = 1; j < table.c; j++) {
            table.data[j][i] = table.match(table.data[0][i], table.regex[j]);
        }
    }

    double end_proc = MPI_Wtime();
    double begin_com = MPI_Wtime();

    if (process_rank == 0) {
        int source;


        for (int i = (process_rank+1)*div; i < MAX_ROWS; i++) {
            for (int j = 1; j < table.c; j++) {
                source = i/div;
//                printf("process %d i =  %d, j = %d, from=%d tag %d \n", process_rank, i , j, source, (i*100+j));
                MPI::Status status;
                MPI::COMM_WORLD.Probe(source, (i*100+j), status);
                int l = status.Get_count(MPI::CHAR);
                char *buf = new char[l];

                MPI::COMM_WORLD.Recv(buf, l, MPI::CHAR, source, (i*100+j), status);
                std::string temp(buf, l);

                table.data[j][i] = temp;
                delete [] buf;
        }
    }


    }
    else{
        for (int i = process_rank*div; ((i < (process_rank+1)*div) && (i <MAX_ROWS)); i++)
            for (int j = 1; j < table.c; j++) {
//                printf("process %d i =  %d, j = %d, to=%d, tag %d\n", process_rank, i , j, 0, (i * 100 + j));

                MPI::COMM_WORLD.Send(table.data[j][i].c_str(), table.data[j][i].length(), MPI::CHAR, 0, (i * 100 + j));
            }

    }
    double end_com = MPI_Wtime();

    double end_total = MPI_Wtime();


    MPI::Finalize();


    // end of sequential processing
    double time_spent_total = end_total - begin_total;
    double time_spent_proc = end_proc - begin_proc;
    double time_spent_com = end_com - begin_com;

    // output
    if (process_rank==0){
        printf("Execution time: %f\n", time_spent_total);
        printf("Communication time: %f\n", time_spent_com);
        printf("Processing time: %f\n", time_spent_proc);

        table.write_csv("./data/result_parallel_mpi.csv");
        table.count_matches();

    }


    return 0;
}
