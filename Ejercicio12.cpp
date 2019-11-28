#include <iostream>

using namespace std;

bool **matrix;
int *set;
int *mSet;

void initializeMatrix(int n, int m)
{
    matrix = new bool *[n + 1];
    for (int i = 0; i <= n; i++)
    {
        matrix[i] = new bool[m + 1];
        for (int j = 0; j <= m; j++)
        {
            matrix[i][j] = false;
        }
    }

    for (int i = 0; i <= n; i++)
    {
        matrix[i][0] = true;
    }
}

void isPossibleToDoTheSum(int n, int sum)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= sum; j++)
        {
            if (set[i - 1] > j)
            {
                matrix[i][j] = matrix[i - 1][j];
            }
            else
            {
                matrix[i][j] = matrix[i - 1][j] || matrix[i - 1][j - set[i - 1]];
            }
        }
    }
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
    initializeMatrix(sizeOfSet, maxValue);
    for (int i = 0; i < quantityOfM; i++)
    {
        int m;
        cin >> m;
        mSet[i] = m;
    }
    isPossibleToDoTheSum(sizeOfSet, maxValue);
    for (int i = 0; i < quantityOfM; i++)
    {
        if (i == quantityOfM - 1)
        {
            cout << (matrix[sizeOfSet][mSet[i]] == true ? 1 : 0);
        }
        else
        {
            cout << (matrix[sizeOfSet][mSet[i]] == true ? 1 : 0) << endl;
        }
    }

    return 0;
}