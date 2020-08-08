//
// Created by liam on 8/6/20.
//

#include "Matrix.h"

Matrix :: Matrix()
    : rows(1), columns(1){}

Matrix :: Matrix (int rows, int columns)
    : rows(rows), columns(columns) {
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

    if (input.empty()) {
        valid = false;
    }

    for (int i = 0; i < input.length(); ++i) {
        if (input[i] == '-' && i != 0) {
            valid = false;
        }

        if (input[i] == '.' && firstDot) {
            valid = false;
        }
        else if (input[i] == '.') {
            firstDot = true;
        }

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

void Matrix :: MultiplyRows(vector < double >& row, double multiplier) {
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

    while (pivot < matrix.size() && pivot < matrix.at(0).size()) {

        nonZero = pivot;

        while (nonZero < matrix.size() && !matrix.at(nonZero).at(pivot)) {
            nonZero++;
        }
        if (nonZero == matrix.size()) {
            pivot++;
        }
        else {
            if (pivot != nonZero) {
                SwapRows(matrix.at(pivot), matrix.at(nonZero));
            }
            MultiplyRows(matrix.at(pivot),
                         (1 / matrix.at(pivot).at(pivot)));
            for (unsigned int i = 0; i < matrix.size(); ++i) {
                if (i != pivot) {
                    AddRows(matrix.at(i), matrix.at(pivot),
                            -matrix.at(i).at(pivot));
                }
            }
            pivot++;

        }

    }
}

Matrix& Matrix :: operator= (const Matrix& m) {
    if (this != &m) {
        this->rows = m.rows;
        this->columns = m.columns;
        this->matrix.resize(rows);

        for (unsigned int i =0; i < matrix.size(); ++i) {
            vector < double > temp (m.columns);
            this->matrix.push_back(temp);
        }

        for (unsigned int i = 0; i < rows; ++i) {
            for (unsigned int j = 0; j < columns; ++j) {
                this->matrix.at(i).at(j) = m.matrix.at(i).at(j);
            }
        }

    }
    return *this;
}

Matrix Matrix:: operator* (const Matrix& m) {
    if (this != &m) {
        if (this->columns != m.rows) {
            cout << "These cannot be multiplied. \n";
            return *this;
        }
        else {
            Matrix temp(this->rows, m.columns);

            for (unsigned int i = 0; i < temp.rows; ++i) {
                for (unsigned int j = 0; j < temp.columns; ++j) {
                    double cell = 0;

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