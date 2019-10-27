#include <iostream>
using namespace std;

struct nodoL
{
    int vertice;
    int costo;
    nodoL *sig;
};

struct Tabla
{
    int costo;
    int anterior;
    int costo;
};

void inicializarTabla(int origen, )
{
}

void dijkstra(int origen)
{
}

int main()
{
    int cantVertices;
    int cantAristas;
    cin >> cantVertices;
    cin >> cantAristas;
    nodoL **grafo = new nodoL *[cantVertices + 1];
    for (int i = 0; i < cantAristas; i++)
    {
        int v;
        int w;
        int costo;
        cin >> v >> w >> costo;
        nodoL *nuevoNodo = new nodoL();
        nuevoNodo->vertice = w;
        nuevoNodo->costo = costo;
        nuevoNodo->sig = grafo[v];
        grafo[v] = nuevoNodo;
    }
    int cantVerticesConsulta;
    int verticeConsulta;
    cin >> cantVerticesConsulta;
    for (int i = 1; i <= cantVerticesConsulta; i++)
    {
        cin >> verticeConsulta;
        dijkstra(verticeConsulta);
    }
}