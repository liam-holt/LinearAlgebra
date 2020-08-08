#include <iostream>

#include "Matrix.h"

//Input: A string for "row" or "column"
//Output: User input for their dimension size

int GetDimension(const string& dimension);

int main() {
    int rows; //number of rows for the matrix
    int columns; //number of columns for the matrix

    rows = GetDimension("rows");
    columns = GetDimension("columns");

    Matrix matrix(rows,columns);
    Matrix matrix2(rows, columns);
    matrix.FillMatrix();
    matrix.PrintMatrix();
    matrix2.FillMatrix();
    matrix2.PrintMatrix();

    Matrix matrix3 = matrix * matrix2;

    matrix3.PrintMatrix();
#if 0
    matrix.MultiplyRows(matrix.GetMatrix().at(0),
                        (1.0 / matrix.GetMatrix().at(0).at(0)));
    cout << endl;
    matrix.PrintMatrix();
    matrix.AddRows(matrix.GetMatrix().at(1), matrix.GetMatrix().at(0),
                   -matrix.GetMatrix().at(1).at(0));
    cout << endl;
    matrix.PrintMatrix();
    matrix.SwapRows(matrix.GetMatrix().at(0),
                    matrix.GetMatrix().at(1));
    cout << endl;
    matrix.PrintMatrix();

    matrix.ReducedRowEchelon();
    cout << endl;
    matrix.PrintMatrix();
#endif


    return 0;
}

int GetDimension(const string& dimension) {
    int dim; //user input for dimension

    //get user input and validate
    do {
        cout << "How many " << dimension
             << " do you want for your matrix?\n";
        cin >> dim;
        cin.clear();
        cin.ignore(numeric_limits< streamsize > :: max(), '\n');

        if (cin.fail() || dim < 1) {
            cout << "Please enter an integer >= 1.\n";
        }
    } while (cin.fail() || dim < 1);

    return dim;
}