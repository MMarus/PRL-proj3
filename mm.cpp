/*
 * algorithm: mesh matrix multiplication
 * author: Marek Marusic
 *
 */

#include <mpi.h>
#include <fstream>
#include <sstream>
#include "tags.h"
#include "Matrices.h"
#include "Worker.h"

void firstCpu();

using namespace std;


int main(int argc, char *argv[])
{
    int numprocs;               //pocet procesoru
    int myid;                   //muj rank
    Matrices matrices;


    //MPI INIT
    MPI_Init(&argc,&argv);                          // inicializace MPI
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);       // zjistíme, kolik procesů běží
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);           // zjistíme id svého procesu

    Worker worker(myid, numprocs);
    worker.loadMatrices();

    //meranie start
    worker.computeMyNumber();
    //meranie stop

    if(myid == 0){
        worker.readValuesByMaster();
        worker.writeValuesByMaster();
    } else {
        worker.sendValuesToMaster();
    }

    MPI_Finalize();
    return 0;

}


