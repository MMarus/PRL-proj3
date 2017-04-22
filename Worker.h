//
// Created by archie on 4/22/17.
//

#ifndef PROJ3_WORKER_H
#define PROJ3_WORKER_H


#include "Matrices.h"
#include <mpi.h>


class Worker {

public:
    Worker(int id, int numprocs);
    void loadMatrices();
    void readValuesByMaster();
    void sendValuesToMaster();
    void computeMyNumber();
    void writeValuesByMaster();

private:
    Matrices matrices;
    int myId;
    int numOfProcs;
    int myRow;
    int myCol;
    int myResult;               //moje hodnota
    MPI_Status stat;            //struct- obsahuje kod- source, tag, error
    void setMyRowAndCol();

};


#endif //PROJ3_WORKER_H
