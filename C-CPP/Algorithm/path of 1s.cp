/*Suppose u have a square matrix of 0s and 1s only ... find the longest path of 1s available in the matrix and return that .. you can only move right and down ... For e.g.

0 0 0 1 1
1 1 1 0 1
0 1 1 1 0
0 0 1 0 0
1 1 1 1 1

*/

/*
============================================================================
Author         : James Chen
Email          : a.james.chen@gmail.com
Description    : Find the longest path of 1s available in the matrix
Created Date   : 11-July-2013
Last Modified  :
============================================================================
*/

#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>

using namespace std;

void DisplayPath(int* matrix, int rows, int cols, int maxCount)
{
    typedef pair<int, int> Pair;
    vector<Pair> path;
    int prevRow = rows;
    int prevCol = cols;
    for(int i = rows - 1; i >= 0; --i){
        for(int j = cols - 1; j >=0; --j){
            if(matrix[ i * cols + j] == maxCount && i <= prevRow && j <= prevCol){
                path.push_back(make_pair(i, j));
                maxCount --;
                prevRow = i;
                prevCol = j;
            }

            if(maxCount == 0){
                cout << "The path is " << endl;
                for(int i = path.size() - 1; i >= 0; i--){
                    cout << path.size() - i << "th -- ";
                    cout << "[ " << path[i].first << ", " << path[i].second;
                    cout << "] " << endl;
                }

                return;
            }
        }
    }
}

int FindLongest1Sequences(int* matrix, int rows, int cols)
{
    assert(matrix != NULL);
    assert(rows > 0);
    assert(cols > 0);

    int maxCount(0);
    int count(0);

    for(int i = 0; i < rows; i ++){
        for(int j = 0; j < cols; j++){
            int a = (i == 0) ? 0 : matrix[(i - 1) * cols + j];
            int b = (j == 0) ? 0 : matrix[i * cols + j - 1];
            matrix[i * cols + j] = matrix[i * cols + j] ? max(a, b) + 1 : 0;
            maxCount = max(maxCount, matrix[i * cols + j]);
        }
    }

    DisplayPath(matrix, rows, cols, maxCount);

    return maxCount;
}

void DoTest(int* matrix, int rows, int cols)
{
    if(matrix == NULL){
        cout << "The matix is null" << endl;
        return;
    }

    if(rows < 1){
        cout << "The rows of matix is less than 1" << endl;
        return;
    }

    if(cols < 1){
        cout << "The cols of matix is less than 1" << endl;
        return;
    }

    cout << "The matrix is " << endl;
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            cout << setw(3) << matrix[i * cols + j];
        }
        cout << endl;
    }

    int len = FindLongest1Sequences(matrix, rows, cols);
    cout << "The longest length is " << len << endl;
    cout << "---------------------------------------" << endl;

}



int main(int argc, char* argv[])
{
    int matrix[5][5] = {
        {0, 0, 0, 1, 1},
        {1, 1, 1, 0, 1},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 1, 1, 1}
    };

    DoTest(&matrix[0][0], 5, 5);        // Expected return 8

    int matrix1[1][1] = {
        0
    };
    DoTest(&matrix1[0][0], 1, 1);       // Expected return 0

    int matrix2[1][1] = {
        1
    };
    DoTest(&matrix2[0][0], 1, 1);       // Expected return 1

    int matrix3[5][5] = {
        0
    };

    DoTest(&matrix3[0][0], 5, 5);       // Expected return 0

    int matrix4[5][5] = {
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1}
    };

    DoTest(&matrix4[0][0], 5, 5);       // Expected return 9

    int matrix5[5][5] = {
        {1, 1, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 0, 1, 1},
        {1, 1, 1, 1, 1}
    };

    DoTest(&matrix5[0][0], 5, 5);       // Expected return 7

    return 0;
}
