//
// Created by archie on 4/22/17.
//

#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>
#include <fstream>
#include "Matrices.h"

using namespace std;

Matrices::Matrices() {}

void Matrices::loadMatrices() {
    readMatrix("mat1", 1);
    readMatrix("mat2", 2);

    if(mat1Size != mat1.size())
        throw std::runtime_error("Bad mat1 file.");


    for (int i = 1; i < mat1.size(); ++i) {
        if(mat1[i-1].size() != mat1[i].size()) {
            throw std::runtime_error("Error: mat1 the rows does not have same # of numbers.");
        }
    }

    if(mat2Size != mat2[0].size())
        throw std::runtime_error("Bad mat2 file.");


    for (int i = 1; i < mat2.size(); ++i) {
        if(mat2[i-1].size() != mat2[i].size()) {
            throw std::runtime_error("Error: mat2 the rows does not have same # of numbers.");
        }
    }

    if(mat1[0].size() != mat2.size())
        throw std::runtime_error("Error: mat1 has different number of cols than mat2 rows.");

    resultRows = mat1Size;
    resultCols = mat2Size;
//    cerr << "resultRows " << resultRows<<" resultCols "<<resultCols << endl;
    sameDimensionOfMatrices = mat1[0].size();
}

void Matrices::readMatrix(string filename, int matrixId) {
    int firstLine = 0;
    std::string line;
    fstream fin;

    vector<vector<int>> matrix;
    fin.open(filename, ios::in);

    if(!fin.good()){
        cerr << "Error: not good file" << endl;
        return;
    }

    while ( getline( fin, line ) ) {
        istringstream is( line );
        matrix.push_back(vector<int>( istream_iterator<int>(is), istream_iterator<int>() ) );
    }

    firstLine = matrix[0][0];
    matrix.erase(matrix.begin());

    if(matrixId == 1) {
        swap(matrix, mat1);
        mat1Size = firstLine;
    } else {
        swap(matrix, mat2);
        mat2Size = firstLine;
    }

}

void Matrices::writeFirstMatrix() {
    cout << mat1.size() << ":" << mat1[0].size() << endl;

    for (int i = 0; i < mat1.size(); ++i) {
        cout << mat1[i][0];
        for (int j = 1; j < mat1[i].size(); ++j) {
            cout << " " << mat1[i][j];
        }
        cout << endl;
    }
}
