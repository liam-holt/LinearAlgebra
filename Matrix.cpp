//
// Created by liam on 8/6/20.
//

const bool Verbose = false; //debugging

#include "Matrix.h"

Matrix::Matrix()
        : rows(1), columns(1)
{}

Matrix::Matrix(int rows, int columns)
        : rows(rows), columns(columns)
{
    //build matrix
    for (int row = 0; row < rows; ++row)
    {
        vector<double> temp(columns, 0);
        matrix.push_back(temp);
    }
}

void Matrix::PrintMatrix()
{
    for (auto& row : matrix)
    {
        for (auto& cell : row)
        {
            cout << left << setw(10)
                 << setprecision(3) << cell << ' ';
        }
        cout << endl;
    }
}

bool Matrix::Validate(string input)
{
    bool hasDecimalPoint = false;
    bool valid = true;

    //empty string
    if (input.empty())
    {
        valid = false;
    }

    for (int character = 0; character < input.length(); ++character)
    {
        //negative only in front
        if (input[character] == '-' && character != 0)
        {
            valid = false;
        }
        //only one decimal
        if (input[character] == '.' && hasDecimalPoint)
        {
            valid = false;
        }
        else if (input[character] == '.')
        {
            hasDecimalPoint = true;
        }
        //only negatives, decimals, and numbers
        if (!(isdigit(input[character]) || input[character] == '.'
              || input[character] == '-'))
        {
            valid = false;
        }
    }
    return valid;
}

void Matrix::FillMatrix()
{
    string cell; //user input for each cell

    for (int row = 0; row < rows; ++row)
    {
        for (int column = 0; column < columns; ++column)
        {
            do
            {
                cout << "Please enter a number for cell ("
                     << row + 1 << "," << column + 1 << ")\n";
                getline(cin, cell);
            }
            while (cin.fail() || !Validate(cell));

            matrix.at(row).at(column) = stod(cell);
        }
    }
}

void Matrix::MultiplyRow(vector<double>& row, double multiplier)
{
    for (double& cell : row)
    {
        cell *= multiplier;
    }
}

void Matrix::AddRows(vector<double>& row1, const vector<double>& row2,
                     const double& multiplier)
{
    for (unsigned int cell = 0; cell < row1.size(); ++cell)
    {
        row1.at(cell) += multiplier * row2.at(cell);
    }
}

void Matrix::SwapRows(vector<double>& row1, vector<double>& row2)
{
    double temp;

    for (unsigned int cell = 0; cell < row1.size(); ++cell)
    {
        temp = row1.at(cell);
        row1.at(cell) = row2.at(cell);
        row2.at(cell) = temp;
    }
}

void Matrix::ReducedRowEchelon()
{
    int pivot = 0;
    int nonZero;

    //while pivots remain
    while (pivot < matrix.size() && pivot < matrix.at(0).size())
    {

        nonZero = pivot;

        //find first non-zero in current pivot column
        while (nonZero < matrix.size() && !matrix.at(nonZero).at(pivot))
        {
            nonZero++;
        }
        //if out of bounds, no possible pivot, skip column
        if (nonZero == matrix.size())
        {
            pivot++;
        }
        else
        {
            //if pivot in column is not in pivot-row, swap those rows
            if (pivot != nonZero)
            {
                SwapRows(matrix.at(pivot), matrix.at(nonZero));
            }
            //multiply pivot row by reciprocal
            MultiplyRow(matrix.at(pivot),
                        (1 / matrix.at(pivot).at(pivot)));

            //Add every other row with
            //pivotRow * negative of row's pivot-column cell
            for (unsigned int row = 0; row < matrix.size(); ++row)
            {
                if (row != pivot)
                {
                    AddRows(matrix.at(row), matrix.at(pivot),
                            -matrix.at(row).at(pivot));
                }
            }
            //repeat for next column
            pivot++;
        }
    }
}

//
double Matrix::Determinant(const Matrix& matrix)
{
    //Det(A_11) = A_11
    if (matrix.rows <= 1 && matrix.columns <= 1)
    {
        return matrix.matrix.at(0).at(0);
    }
    else
    {
        double sum = 0.0;
        //make a smaller matrix out of the non-pivot rows/columns
        for (unsigned int pivot = 0; pivot < matrix.columns; ++pivot)
        {
            Matrix temp(matrix.rows - 1, matrix.columns - 1);
            unsigned int largerRow = 1, largerCol, smallerRow = 0, smallerCol;

            while (smallerRow < temp.rows)
            {
                smallerCol = 0, largerCol = 0;

                while (smallerCol < temp.columns)
                {
                    // don't copy values in pivot col
                    if (largerCol == pivot)
                    {
                        largerCol++;
                    }
                    temp.matrix.at(smallerRow).at(smallerCol) = \
                        matrix.matrix.at(largerRow).at(largerCol);

                    largerCol++, smallerCol++;
                }
                largerRow++, smallerRow++;
            }
            //if pivot is even
            if (!(pivot % 2))
            {
                sum += matrix.matrix.at(0).at(pivot) * Determinant(temp);
            }
            else
            {
                sum -= matrix.matrix.at(0).at(pivot) * Determinant(temp);
            }
        }
        return sum;
    }
}

Matrix& Matrix::operator=(const Matrix& matrixB)
{
    //if param != this object
    if (this != &matrixB)
    {
        this->rows = matrixB.rows;
        this->columns = matrixB.columns;
        this->matrix.resize(rows);

        //empty rows
        while (!this->matrix.empty())
        {
            this->matrix.pop_back();
        }

        //rebuild matrix
        for (unsigned int row = 0; row < matrix.size(); ++row)
        {
            vector<double> temp(columns);
            this->matrix.push_back(temp);
        }

        //copy cells from param matrix to this object
        for (unsigned int row = 0; row < rows; ++row)
        {
            for (unsigned int column = 0; column < columns; ++column)
            {
                this->matrix.at(row).at(column) = \
                    matrixB.matrix.at(row).at(column);
            }
        }
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix& matrixB)
{
    //if this object != param
    if (this != &matrixB)
    {
        //if left matrix columns != right matrix rows you cannot A x B
        if (this->columns != matrixB.rows)
        {
            cout << "These cannot be multiplied. \n";
            return *this;
        }
        else
        {
            //make new matrix of proper size
            Matrix temp(this->rows, matrixB.columns);

            //for each AxB_ij cell
            for (unsigned int row = 0; row < temp.rows; ++row)
            {
                for (unsigned int column = 0; column < temp.columns; ++column)
                {
                    double cell = 0.0;

                    //cell = A_i0 * B_0j + A_i1 * B_1j + ... + A_ik * B_kj
                    for (unsigned int iterator = 0; iterator < temp.rows;
                         ++iterator)
                    {
                        cell += this->matrix.at(row).at(iterator) * \
                                matrixB.matrix.at(iterator).at(column);
                    }
                    temp.matrix.at(row).at(column) = cell;
                }
            }
            return temp;
        }
    }
    return *this;
}


int Matrix::GetRows()
{ return rows; }

void Matrix::SetRows(int& rows)
{ this->rows = rows; }

int Matrix::GetColumns()
{ return columns; }

void Matrix::SetColumns(int& columns)
{ this->columns = columns; }

vector<vector<double> >& Matrix::GetMatrix()
{ return matrix; }

void Matrix::SetMatrix(vector<vector<double> >& matrix)
{ this->matrix = matrix; }