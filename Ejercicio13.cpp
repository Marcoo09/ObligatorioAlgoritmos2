#include <iostream>

#define MAX_INT 2147483647

using namespace std;

int **matrix;
int columns;
int rows;
int sol = 0;

void initializeMatrix(int n, int m)
{
    matrix = new int *[n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[m];
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

/* A recursive utility function to solve Maze problem */
bool getWeightOfPath2(int x1, int y1, int x2, int y2, int sum)
{
    // if (x, y is goal) return true
    if (x1 == x2 && y1 == y2)
    {
        sol = sum;
        return true;
    }

    // Check if maze[x][y] is valid
    if (x1 < 0 || x1 >= rows || y1 < 0 || y1 >= columns)
    {
        sol = MAX_INT;
        return false;
    }
    else
    {
        // cout << "hasta acá llegue" << endl;
        /* Move forward in x direction */
        bool a = getWeightOfPath2(x1 + 1, y1, x2, y2, sum + matrix[x1][y1]);
        if (a == true)
            return true;

        // cout << "hasta acá llegue 2 " << endl;
        /* If moving in x direction doesn't give solution then 
           Move down in y direction  */
        bool b = getWeightOfPath2(x1, y1 + 1, x2, y2, sum + matrix[x1][y1]);
        if (b == true)
            return true;
        // cout << "hasta acá llegue 3" << endl;
        /* Move forward in x direction */
        bool c = getWeightOfPath2(x1 - 1, y1, x2, y2, sum + matrix[x1][y1]);
        if (c == true)
            return true;

        // cout << "hasta acá llegue 4 " << endl;
        /* If moving in x direction doesn't give solution then 
           Move down in y direction  */
        bool d = getWeightOfPath2(x1, y1 - 1, x2, y2, sum + matrix[x1][y1]);
        if (d == true)
            return true;

        /* If none of the above movements work then BACKTRACK:  
            unmark x, y as part of solution path */
        return false;
    }

    return false;
}

int getWeightOfPath(int x1, int y1, int x2, int y2, int sum)
{
    // cout << "executed" << endl;
    if (x1 == x2 && y1 == y2)
    {
        cout << "LLEGUEEE" << endl;
        return sum;
    }

    if (x1 < 0 || x1 >= rows || y1 < 0 || y1 >= columns)
    {
        return -1;
    }

    if (x1 < x2)
    {
        //ME MUEVO HACIA LA DERECHA
        // int path1 = getWeightOfPath(x1 + 1, y1, x2, y2, sum + matrix[x1][y1]);
        // int path2 = getWeightOfPath(x1, y1 + 1, x2, y2, sum + matrix[x1][y1]);
        // int path3 = getWeightOfPath(x1, y1 - 1, x2, y2, sum + matrix[x1][y1]);

        // return path1 > path2 ? path2 > path3 ? path3 : path2 : path1;
        int path1;
        int path2;
        if (y1 < y2)
        {
            //ME MUEVO HACIA ABAJO
            cout << x1 << y1 << " es " << matrix[x1][y1] << endl;
            path1 = getWeightOfPath(x1 + 1, y1, x2, y2, sum + matrix[x1][y1]);
            path2 = getWeightOfPath(x1, y1 + 1, x2, y2, sum + matrix[x1][y1]);
            if (path2 == -1)
            {
                return path1;
            }
            else if (path1 == -1)
            {
                return path2;
            }
            return path1 > path2 ? path2 : path1;
        }
        else
        {
            //ME MUEVO HACIA ARRIBA
            cout << x1 << y1 << " es " << matrix[x1][y1] << endl;
            path1 = getWeightOfPath(x1 - 1, y1, x2, y2, sum + matrix[x1][y1]);
            path2 = getWeightOfPath(x1, y1 + 1, x2, y2, sum + matrix[x1][y1]);
            if (path2 == -1)
            {
                return path1;
            }
            else if (path1 == -1)
            {
                return path2;
            }
            return path1 > path2 ? path2 : path1;
        }
    }
    else
    {
        //ME MUEVO HACIA LA IZQUIERDA
        // int path1 = getWeightOfPath(x1 - 1, y1, x2, y2, sum + matrix[x1][y1]);
        // int path2 = getWeightOfPath(x1, y1 + 1, x2, y2, sum + matrix[x1][y1]);
        // int path3 = getWeightOfPath(x1, y1 - 1, x2, y2, sum + matrix[x1][y1]);

        // return path1 > path2 ? path2 > path3 ? path3 : path2 : path1;
        int path1;
        int path2;
        if (y1 < y2)
        {
            //ME MUEVO HACIA ABAJO
            cout << x1 << y1 << " es " << matrix[x1][y1] << endl;
            path1 = getWeightOfPath(x1, y1 - 1, x2, y2, sum + matrix[x1][y1]);
            path2 = getWeightOfPath(x1 + 1, y1, x2, y2, sum + matrix[x1][y1]);
            if (path2 == -1)
            {
                return path1;
            }
            else if (path1 == -1)
            {
                return path2;
            }
            return path1 > path2 ? path2 : path1;
        }

        else
        {
            //ME MUEVO HACIA ARRIBA
            cout << x1 << y1 << " es " << matrix[x1][y1] << endl;
            path1 = getWeightOfPath(x1, y1 - 1, x2, y2, sum + matrix[x1][y1]);
            path2 = getWeightOfPath(x1 - 1, y1, x2, y2, sum + matrix[x1][y1]);
            if (path2 == -1)
            {
                return path1;
            }
            else if (path1 == -1)
            {
                return path2;
            }
            return path1 > path2 ? path2 : path1;
        }
    }
}

int main()
{
    int threshold;
    cin >> columns >> rows;
    cin >> threshold; // K
    initializeMatrix(rows, columns);

    //Load matrix
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            int value;
            cin >> value;
            matrix[i][j] = value;
        }
    }

    int cases;
    cin >> cases;
    for (int i = 0; i < cases; i++)
    {
        int x1, y1, x2, y2; // Intiial: (x1,y1), final: (x2,y2)
        cin >> x1 >> y1 >> x2 >> y2;
        // cout << x1 << y1 << x2 << y2 << endl;
        int weightOfPath = getWeightOfPath(--x1, --y1, --x2, --y2, 0);
        // bool isThereSolution = getWeightOfPath2(x1 - 1, y1 - 1, x2 - 1, y2 - 1, 0);
        // cout << (isThereSolution ? sol : 0) << endl;
        // weightOfPath > threshold ? 0 :
        cout << weightOfPath << endl;
    }

    return 0;
}