//
// Created by liam on 8/6/20.
//

const bool Verbose = true;

#include "Matrix.h"

Matrix :: Matrix()
    : rows(1), columns(1){}

Matrix :: Matrix (int rows, int columns)
    : rows(rows), columns(columns) {
    //build matrix
    for (int i = 0; i < rows; ++i) {
        vector < double > temp (columns, 0);
        matrix.push_back(temp);
    }
}

void Matrix :: PrintMatrix() {
    for (auto& it : matrix) {
        for (auto& ij : it) {
            cout << left << setw(10)
                 << setprecision(3) << ij << ' ';
        }
        cout << endl;
    }
}

bool Matrix :: Validate (string input) {
    bool firstDot = false;
    bool valid = true;

    //empty string
    if (input.empty()) {
        valid = false;
    }

    for (int i = 0; i < input.length(); ++i) {
        //negative only in front
        if (input[i] == '-' && i != 0) {
            valid = false;
        }
        //only one decimal
        if (input[i] == '.' && firstDot) {
            valid = false;
        }
        else if (input[i] == '.') {
            firstDot = true;
        }
        //only negatives, decimals, and numbers
        if (! (isdigit(input[i]) || input[i] == '.' || input[i] == '-') ) {
            valid = false;
        }
    }

    return valid;
}

void Matrix :: FillMatrix() {
    string cell; //user input for each cell

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            do {
                cout << "Please enter a number for cell ("
                     << i + 1 << "," << j + 1 << ")\n";
                getline(cin, cell);
            } while (cin.fail() || ! Validate(cell));

            matrix.at(i).at(j) = stod(cell);
        }
    }
}

void Matrix :: MultiplyRow(vector < double >& row, double multiplier) {
    for (double & i : row) {
        i *= multiplier;
    }
}

void Matrix :: AddRows(vector < double >& row1, const vector < double >& row2,
                       const double& multiplier) {
    for (unsigned int i = 0; i < row1.size(); ++i) {
        row1.at(i) += multiplier * row2.at(i);
    }
}

void Matrix :: SwapRows (vector < double >& row1, vector < double >& row2){
    double temp;

    for (unsigned int i = 0; i < row1.size(); ++i) {
        temp = row1.at(i);
        row1.at(i) = row2.at(i);
        row2.at(i) = temp;
    }
}

void Matrix :: ReducedRowEchelon() {
    int pivot = 0;
    int nonZero;

    //while pivots remain
    while (pivot < matrix.size() && pivot < matrix.at(0).size()) {

        nonZero = pivot;

        //find first non-zero in current pivot column
        while (nonZero < matrix.size() && !matrix.at(nonZero).at(pivot)) {
            nonZero++;
        }
        //if out of bounds, no possible pivot, skip column
        if (nonZero == matrix.size()) {
            pivot++;
        }
        else {
            //if pivot in column is not in pivot-row, swap those rows
            if (pivot != nonZero) {
                SwapRows(matrix.at(pivot), matrix.at(nonZero));
            }
            //multiply pivot row by reciprocal
            MultiplyRow(matrix.at(pivot),
                        (1 / matrix.at(pivot).at(pivot)));

            //Add every other row with
            //pivotRow * negative of row's pivot-column cell
            for (unsigned int i = 0; i < matrix.size(); ++i) {
                if (i != pivot) {
                    AddRows(matrix.at(i), matrix.at(pivot),
                            -matrix.at(i).at(pivot));
                }
            }
            //repeat for next column
            pivot++;

        }
    }
}

//
double Matrix :: Determinant(const Matrix& matrix) {
    //Det(A_11) = A_11
    if (matrix.rows <= 1 && matrix.columns <= 1) {
        return matrix.matrix[0][0];
    }
    else {
        double sum = 0.0;
        //make a smaller matrix out of the non-pivot rows/columns
        for (unsigned int pivot = 0; pivot < matrix.columns; ++pivot) {
            Matrix temp (matrix.rows - 1, matrix.columns - 1);
            unsigned int largerRow = 1, largerCol, smallerRow = 0, smallerCol;

            while (smallerRow < temp.rows) {
                smallerCol = 0, largerCol = 0;

                while (smallerCol < temp.columns) {
                    // don't copy values in pivot col
                    if (largerCol == pivot) {
                        largerCol++;
                    }
                    temp.matrix.at(smallerRow).at(smallerCol) = \
                        matrix.matrix.at(largerRow).at(largerCol);
                    largerCol++, smallerCol++;
                }
                largerRow++, smallerRow++;
            }
            //if pivot is even
            if (! (pivot % 2)) {
                sum += matrix.matrix.at(0).at(pivot) * Determinant(temp);
            }
            else {
                sum += -1 * matrix.matrix.at(0).at(pivot) * Determinant(temp);
            }
        }
        return sum;
    }
}

Matrix& Matrix :: operator= (const Matrix& m) {
    //if param != this object
    if (this != &m) {
        this->rows = m.rows;
        this->columns = m.columns;
        this->matrix.resize(rows);

        //rebuild matrix
        for (unsigned int i =0; i < matrix.size(); ++i) {
            vector < double > temp (m.columns);
            this->matrix.push_back(temp);
        }

        //copy cells from param matrix to this object
        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < columns; ++j) {
                this->matrix.at(i).at(j) = m.matrix.at(i).at(j);
            }
        }

    }
    return *this;
}

Matrix Matrix:: operator* (const Matrix& m) {
    //if this object != param
    if (this != &m) {
        //if left matrix columns != right matrix rows you cannot A x B
        if (this->columns != m.rows) {
            cout << "These cannot be multiplied. \n";
            return *this;
        }
        else {
            //make new matrix of proper size
            Matrix temp(this->rows, m.columns);

            //for each AxB_ij cell
            for (unsigned int i = 0; i < temp.rows; ++i) {
                for (unsigned int j = 0; j < temp.columns; ++j) {
                    double cell = 0;

                    //cell = A_i0 * B_0j + A_i1 * B_1j + ... + A_ik * B_kj
                    for (unsigned int k = 0; k < temp.rows; ++k) {
                        cell += this->matrix.at(i).at(k) * m.matrix.at(k).at(j);
                    }
                    temp.matrix.at(i).at(j) = cell;
                }
            }
            return temp;
        }
    }
    return *this;
}



int Matrix :: GetRows() {return rows;}
void Matrix :: SetRows(int& rows) {this->rows = rows;}
int Matrix :: GetColumns() {return columns;}
void Matrix :: SetColumns(int& columns) {this->columns = columns;}
vector < vector < double > >& Matrix :: GetMatrix() {return matrix;}
void Matrix :: SetMatrix(vector < vector < double > >& matrix) {this->matrix = matrix;}