#include <mpi.h>
#include <iostream>

#include <stdlib.h>

int main(int argc, char *argv[]) {
    MPI::Init(argc, argv);

    int rank = MPI::COMM_WORLD.Get_rank();
    int size = MPI::COMM_WORLD.Get_size();

    std::cout << "Returned: " << system("sleep 2") << " ";
    std::cout << "Hello World! I am " << rank << " of " << size <<
              std::endl;

    MPI::Finalize();
    return (0);
}