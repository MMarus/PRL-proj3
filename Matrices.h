//
// Created by archie on 4/22/17.
//

#ifndef PROJ3_MATRICES_H
#define PROJ3_MATRICES_H

#include <vector>
#include <string>

using namespace std;


class Matrices {
public:
    vector<vector <int>> mat1;
    vector<vector <int>> mat2;
    int mat1Size;
    int mat2Size;
    unsigned long sameDimensionOfMatrices;
    int resultRows;
    int resultCols;

    Matrices();
    void loadMatrices();
    void readMatrix(string filename, int matrixId);
    void writeFirstMatrix();
};


#endif //PROJ3_MATRICES_H
