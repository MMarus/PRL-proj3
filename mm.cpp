/*
 * algorithm: mesh matrix multiplication
 * author: Marek Marusic
 *
 */

#include <mpi.h>
#include <fstream>
#include "Matrices.h"
#include "Worker.h"

void firstCpu();

using namespace std;


int main(int argc, char *argv[])
{
    int numprocs;               //pocet procesoru
    int myid;                   //muj rank
    Matrices matrices;
    timespec tS;

    //MPI INIT
    MPI_Init(&argc,&argv);                          // inicializace MPI
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);       // zjistíme, kolik procesů běží
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);           // zjistíme id svého procesu

    Worker worker(myid, numprocs);
    worker.loadMatrices();

    //meranie start
    if(myid == 0) {
        tS.tv_sec = 0;
        tS.tv_nsec = 0;
        clock_settime(CLOCK_PROCESS_CPUTIME_ID, &tS);
    }

    worker.computeMyNumber();

    //meranie stop
    if(myid == 0) {
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tS);
        //Zapis merania casu
        fstream fout;
        fout.open("times", ios::app);
        fout << numprocs << ";" << tS.tv_sec << ";" << tS.tv_nsec << endl;
        fout.close();
    }

    if(myid == 0){
        worker.readValuesByMaster();
        worker.writeValuesByMaster();
    } else {
        worker.sendValuesToMaster();
    }

    MPI_Finalize();
    return 0;

}


