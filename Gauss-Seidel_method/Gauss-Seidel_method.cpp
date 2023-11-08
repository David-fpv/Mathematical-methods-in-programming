//The Gauss-Seidel method for solving SLOUGH
//Tarasenko David

#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

void showMatrix(int, int, vector<vector<float>>);

void swapLine(vector<float>&, vector<float>&, int);

int isDiagonalElementMoreSumOther(int, vector<float>, int); // тест на сходимость матрицы

int main()
{
    int m = 0; // number of rows
    int n = 0; // number of columns

    cout << "Please enter the count of equations\n";
    cin >> m;

    n = m + 1;

    vector<vector<float>> expanded_matrix(m, vector<float>(n));
    vector<float> array_of_unknowns_last_iteration(m);
    vector<float> array_of_unknowns(m);

    //Matrix Input
    cout << "Enter odds and answers\n";
    for (int i = 0; i < m; i++)
    {
        cout << "enter the coefficients of equation number " << i + 1 << "\n";
        for (int j = 0; j < n; j++)
        {
            cin >> expanded_matrix[i][j];
        }
    }

    //Convergence Block
    for (int i = 0; i < m; i++)
    {
        if (!isDiagonalElementMoreSumOther(i, expanded_matrix[i], m))
        {
            for (int j = i + 1; j < m; j++)
            {
                if (isDiagonalElementMoreSumOther(i, expanded_matrix[j], m))// changed i to j in fitst argument
                {
                    swapLine(expanded_matrix[i], expanded_matrix[j], n);
                    break;
                }
                else if (j + 1 == m)
                {
                    cout << "This matrix cannot be calculated by the method of simple iterations.\n";
                    return 0;
                }
            }
        }
    }

    for (int i = 0; i < m; i++) // divide each row in the matrix by an element of this row, which stands in the main diagonal
    {
        float divider = expanded_matrix[i][i];
        for (int j = 0; j < m + 1; j++)
        {
            expanded_matrix[i][j] /= divider;
        }
    }

    for (int i = 0; i < m; i++) // we write the initial approximations into an array of unknowns
    {
        array_of_unknowns[i] = expanded_matrix[i][m];
    }

    int flag = 1;
    do  // the main part of the algorithm
    {
        for (int i = 0; i < m; i++) // finding approximations-unknowns, which we immediately write to the array of unknowns
        {
            float sum = expanded_matrix[i][m];

            for (int j = 0; j < m; j++)
            {
                if (i != j)
                {
                    float a = expanded_matrix[i][j];
                    float b = array_of_unknowns[j];
                    sum -= a * b;
                }
            }

            array_of_unknowns_last_iteration[i] = array_of_unknowns[i];

            array_of_unknowns[i] = sum;
        }

        // Сhecking accuracy
        for (int i = 0; i < m; i++)
        {
            float error = fabs(array_of_unknowns[i] - array_of_unknowns_last_iteration[i]) / array_of_unknowns[i];
            if (error > 0.0001)
            {
                break;
            }
            if (i + 1 == m)
            {
                flag = 0;
            }
        }

        // Output of intermediate results
        /*for (int i = 0; i < m; i++)
        {
            printf("%f   ", array_of_unknowns[i]);
        }
        printf("\n\n");*/

    } while (flag);

    // Output results
    cout << "\n";
    for (int i = 0; i < m; i++)
    {
        cout << i + 1 << ". " << array_of_unknowns[i] << "\n";
    }

    return 0;
}

void showMatrix(int m, int n, vector<vector<float>> matrix)
{
    for (int i = 0; i < m; i++)
    {
        cout << "\n";
        for (int j = 0; j < n; j++)
        {
            cout << matrix[i][j] << "   ";
        }
    }
    cout << "\n\n";
}

void swapLine(vector<float> &array_line_1, vector<float> &array_line_2, int count)
{
    float buffer;

    for (int i = 0; i < count; i++)
    {
        buffer = array_line_1[i];
        array_line_1[i] = array_line_2[i];
        array_line_2[i] = buffer;
    }
}

int isDiagonalElementMoreSumOther(int number, vector<float> array, int count)
{
    float sum = 0;

    for (int i = 0; i < count; i++)
    {
        if (i != number)
        {
            sum += fabs(array[i]);
        }
    }

    if (fabs(array[number]) > sum)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
