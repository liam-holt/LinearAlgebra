#include <iostream>
#include <limits>
#include "Matrix.h"

using namespace  std;

enum choices {reducedRowEschalon=1, multiply, determinant, quit};

//Input: A string for "row" or "column"
//Output: User input for their dimension size

int GetDimension(const string& dimension);
int MainMenu();
void ReducedRowEschalon();
void MatrixMultiplication();
void Determinant();

int main() {
    int choice;
    string restart;

    do {
        choice = MainMenu();

        switch (choice) {
            case reducedRowEschalon:
                ReducedRowEschalon();
                break;
            case multiply:
                MatrixMultiplication();
                break;
            case determinant:
                Determinant();
                break;
            default:
                break;
        }

        int replay = -1;

        while (choice != quit && choice != replay) {


            cout << "Would you like to do something else? (y/n)\n";
            getline(cin, restart);

            for (char &i : restart) {
                i = tolower(i);
            }

            if (restart == "y" || restart == "yes") {
                choice = replay;
            } else if (restart == "n" || restart == "no") {
                choice = quit;
            }
        }

    } while (choice != quit);



#if 0
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

int MainMenu() {
    int choice;
    do {
        cout << "What would you like to do?\n"
             << "1. Reduced Row Eschalon Form\n"
             << "2. Matrix Multiplication\n"
             << "3. Determinant\n"
             << "4. Quit\n";

        cin >> choice;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (cin.fail() || choice > quit || choice < 1);

    return choice;
}

void ReducedRowEschalon(){
    int rows;
    int columns;

    rows = GetDimension("rows");
    columns =  GetDimension("columns");

    Matrix matrix(rows, columns);
    matrix.FillMatrix();
    cout << "Matrix A:\n";
    matrix.PrintMatrix();
    cout << "\nMatrix A RREF:\n";
    matrix.ReducedRowEchelon();
    matrix.PrintMatrix();
    cout << endl;
}

void MatrixMultiplication(){
    int rows;
    int columns;

    cout << "Building Matrix A:\n";
    rows = GetDimension("rows");
    columns = GetDimension("columns");

    Matrix matrixA(rows, columns);
    matrixA.FillMatrix();
    cout << "Matrix A:\n";
    matrixA.PrintMatrix();

    cout << "Building Matrix B:\n";
    rows = columns;
    columns = GetDimension("columns");

    Matrix matrixB(rows, columns);
    matrixB.FillMatrix();
    cout << "Matrix B:\n";
    matrixB.PrintMatrix();

    Matrix matrixAxB = matrixA * matrixB;
    cout << "\nMatrix A x B: \n";
    matrixAxB.PrintMatrix();
    cout << endl;
}

void Determinant () {
    int rows = GetDimension("rows and columns");
    int columns = rows;

    Matrix matrix(rows, columns);
    matrix.FillMatrix();

    cout << "Matrix A:\n";
    matrix.PrintMatrix();

    double determinant = matrix.Determinant(matrix);

    cout << "|A| :\n" << determinant << endl;



}