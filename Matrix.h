//
// Created by liam on 8/6/20.
//

#ifndef LINEARALGEBRA_MATRIX_H
#define LINEARALGEBRA_MATRIX_H

#include <vector>
#include <iostream>
#include <limits> //for user input validation of max stream size
#include <iomanip>

using namespace std;

class Matrix {
public:
    Matrix();
    Matrix (int rows, int columns);

    //Displays matrix
    void PrintMatrix();
    //Validates user input as a double
    bool Validate(string);
    //User input for matrix cell by cell
    void FillMatrix();
    //Input: A row and a multiple
    //Output: changed the row to Row * multiple
    void MultiplyRow(vector < double > &row, double multiplier);
    //Input: two rows and a multiple
    //Output: changes the first row to Row1 + (Multple * Row2)
    void AddRows(vector < double >&, const vector < double >&, const double&);
    //Input: two rows
    //Output: changed the position of the two rows
    void SwapRows (vector < double >&, vector < double >&);
    //Converts matrix to reduced row echelon form
    void ReducedRowEchelon();

    //Overloaded operators
    Matrix& operator= (const Matrix& m);
    Matrix operator* (const Matrix& m);

    //Getters and Setters
    int GetRows();
    void SetRows(int& rows);
    int GetColumns();
    void SetColumns(int& columns);
    vector < vector < double > >& GetMatrix();
    void SetMatrix(vector < vector < double > >& matrix);



private:
    int rows;
    int columns;

    vector < vector < double > > matrix;

};


#endif //LINEARALGEBRA_MATRIX_H
