//
// Created by archie on 4/22/17.
//
#include <mpi.h>
#include "Worker.h"
#include "tags.h"

using namespace std;

Worker::Worker(int id, int numprocs) {
    myId = id;
    numOfProcs = numprocs;
    myResult = 0;
}

void Worker::loadMatrices() {
    matrices.loadMatrices();
    setMyRowAndCol();
}

void Worker::setMyRowAndCol() {
    myRow = myId / matrices.resultCols;
    myCol = myId % matrices.resultCols;
    myLeftNeighbour = myId-1;
    myRightNeighbour = myId+1;
    myTopNeighbour = myId - matrices.resultCols;
    myBottomNeighbour = myId + matrices.resultCols;
}

void Worker::computeMyNumber() {
    for (int i = 0; i < matrices.sameDimensionOfMatrices; ++i) {
        if (myCol == 0)
            a = matrices.mat1[myRow][i];
        else
            MPI_Recv(&a, 1, MPI_INT, myLeftNeighbour, TAGA, MPI_COMM_WORLD, &stat);

        if (myRow == 0)
            b = matrices.mat2[i][myCol];
        else
            MPI_Recv(&b, 1, MPI_INT, myTopNeighbour, TAGB, MPI_COMM_WORLD, &stat);

        myResult += a * b;

        if (myCol != matrices.resultCols-1)
            MPI_Send(&a, 1, MPI_INT, myRightNeighbour, TAGA, MPI_COMM_WORLD);
        if (myRow != matrices.resultRows-1)
            MPI_Send(&b, 1, MPI_INT, myBottomNeighbour, TAGB, MPI_COMM_WORLD);

    }
}

void Worker::readValuesByMaster() {
    matrices.mat1.clear();
    matrices.mat1.resize(matrices.resultRows, vector<int>(matrices.resultCols));
    matrices.mat1[0][0] = myResult;
    for (int i = 1; i < numOfProcs; ++i) {
        MPI_Recv(&matrices.mat1[i/matrices.resultCols][i%matrices.resultCols], 1, MPI_INT, i, TAGRESULT, MPI_COMM_WORLD, &stat);
    }
}

void Worker::writeValuesByMaster() {
    matrices.writeFirstMatrix();
}

void Worker::sendValuesToMaster() {
    MPI_Send(&myResult, 1, MPI_INT, 0, TAGRESULT, MPI_COMM_WORLD);
}





