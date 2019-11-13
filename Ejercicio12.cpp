#include <iostream>

using namespace std;

bool **matrix;
int *set;
int *mSet;
void initializeMatrix(int m, int n)
{
    matrix = new bool *[n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new bool[m];
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] = false;
        }
    }

    for (int i = 0; i < n; i++)
    {
        matrix[i][0] = true;
    }
}

int isPossibleToDoTheSum(int n, int m, int index)
{
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            if (i > 0 && j > 0)
            {
                if (set[i] > mSet[index])
                {
                    //s(m,n-1)
                    matrix[i][j] = matrix[i - 1][j];
                }
                else
                {
                    //s(m - e[n],n-1)
                    mSet[index] -= set[i];
                    matrix[i][j] = matrix[i - set[i]][j - 1] || matrix[i - 1][j];
                }
            }
        }
    }
    // cout << endl;
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < m; j++)
    //     {
    //         if (matrix[i][j])
    //         {
    //             cout << 1 << " ";
    //         }
    //         else
    //         {
    //             cout << 0 << " ";
    //         }
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    return matrix[n - 1][index] == true ? 1 : 0;
}

int main()
{

    int sizeOfSet;
    int maxValue;
    int quantityOfM;
    cin >> sizeOfSet;
    set = new int[sizeOfSet];
    for (int i = 0; i < sizeOfSet; i++)
    {
        int value;
        cin >> value;
        set[i] = value;
    }

    cin >> maxValue;
    cin >> quantityOfM;
    mSet = new int[quantityOfM];
    initializeMatrix(sizeOfSet, quantityOfM);

    for (int i = 0; i < quantityOfM; i++)
    {
        int m;
        cin >> m;
        mSet[i] = m;
    }

    for (int i = 0; i < quantityOfM; i++)
    {
        int isPossible = isPossibleToDoTheSum(sizeOfSet, quantityOfM, i);
        cout << isPossible << endl;
    }

    return 0;
}