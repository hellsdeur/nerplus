#include <mpi.h>
#include <iostream>
#include <string.h>
#include "src/table.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {

    std::string data[10];
    MPI::Init(argc, argv);

    int size = MPI::COMM_WORLD.Get_size();
    int rank = MPI::COMM_WORLD.Get_rank();


  //  MPI::Comm::Send();

    int div = 10/size;

    if (rank != 0)
    for (int i = rank*div; i < (rank+1)*div; i++){
        data[i] = std::to_string(rank);
    }


    if (rank != 0) {
//        for (int i=0; i<div; i++)
            MPI::COMM_WORLD.Send(data, 20, MPI::CHAR, 0, 0);
//        std::cout << std::to_string(eee.size());
    }
    else{
//        for (int i=0; i<div; i++)
        MPI::Status status;
        MPI::COMM_WORLD.Probe(1, 0, status);
        int l = status.Get_count(MPI::CHAR);

        char *buf = new char[l];
        MPI::COMM_WORLD.Recv(buf, l, MPI::CHAR, 1, 0, status);
        for (int i=0; i<l; i++)
            std::cout << buf[i] <<"\n";
        std::string bla1(buf, l);
        delete [] buf;
//        std::cout << bla1;
//            MPI::COMM_WORLD.Recv(&eee, 4, MPI::CHAR, 1, 0);
    }
//
//
//    if (rank == 0){
//        char aaa[10] = "qqqqqqq";
//        std::string bbb[10];
//        bbb[0] = aaa;
//
//        std::cout << bbb[0];
//
//    }



    MPI::Finalize();
    return (0);
}