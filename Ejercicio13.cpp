
#include <iostream>

#define MAX_INT 2147483647

using namespace std;

int **matrix;
bool **visitados;
int columns;
int rows;
int threshold;
int sol = 0;
int movx[4] = {1, 0, -1, 0};
int movy[4] = {0, 1, 0, -1};

void initializeVisitedMatrix(int n, int m)
{
    visitados = new bool *[n];
    for (int i = 0; i < n; i++)
    {
        visitados[i] = new bool[m];
        for (int j = 0; j < m; j++)
        {
            visitados[i][j] = false;
        }
    }
}

void initializeMatrix(int n, int m)
{
    matrix = new int *[n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[m];
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] = -1;
        }
    }
}

bool esPosicionValida(int x, int y)
{
    return x >= 0 && y >= 0 && y < columns && x < rows;
}

void laberintoBT(int xi, int yi, int xf, int yf, int &sumaOptima, int sumaActual)
{
    if (xi == xf && yi == yf)
    { //is solution
        if (sumaActual < sumaOptima)
        {
            sumaOptima = sumaActual;
        }
    }
    else
    { //is not solution
        for (int i = 0; i < 4; i++)
        {
            int posibleX = xi + movx[i];
            int posibleY = yi + movy[i];
            if (esPosicionValida(posibleX, posibleY))
            {
                int posibleValor = matrix[posibleX][posibleY];
                if (posibleValor != 0 && !visitados[posibleX][posibleY] && sumaActual + posibleValor < threshold)
                {
                    //add to solution
                    visitados[posibleX][posibleY] = true;
                    int sumaNueva = sumaActual + posibleValor;
                    laberintoBT(posibleX, posibleY, xf, yf, sumaOptima, sumaNueva);
                    //delete of solution
                    visitados[posibleX][posibleY] = false;
                }
            }
        }
    }
}

int result(int xi, int yi, int xf, int yf)
{
    int sumaOptima = MAX_INT;
    int sumaActual = matrix[xi][yi];
    visitados[xi][yi] = true;
    laberintoBT(xi, yi, xf, yf, sumaOptima, sumaActual);
    return sumaOptima;
}

int main()
{

    cin >> columns >> rows;
    cin >> threshold; // K
    initializeMatrix(rows, columns);
    initializeVisitedMatrix(rows, columns);
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
        initializeVisitedMatrix(rows, columns);
        int x1, y1, x2, y2; // Intiial: (x1,y1), final: (x2,y2)
        cin >> y1 >> x1 >> y2 >> x2;
        x1--;
        y1--;
        x2--;
        y2--;
        int resultado = result(x1, y1, x2, y2);
        cout << resultado << endl;
    }
}