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
    int a;
    int b;
    int myId;
    int numOfProcs;
    int myRow;
    int myCol;
    int myResult;
    int myBottomNeighbour;
    int myLeftNeighbour;
    int myTopNeighbour;
    int myRightNeighbour;
    MPI_Status stat;

    void setMyRowAndCol();

};


#endif //PROJ3_WORKER_H
