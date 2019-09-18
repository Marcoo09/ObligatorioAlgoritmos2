#include <iostream>

using namespace std;

struct node
{
    int data;
    int distanceToOrigin; //It's the same of grade of incidence
    node *sig;
};

int fatherPosition(int pos)
{
    return pos / 2;
}

int leftSonPosition(int pos)
{
    return pos * 2;
}

int rightSonPosition(int pos)
{
    return pos * 2 + 1;
}

// int obtenerPosMinimoHijo(int pos)
// {
// 	int posIzq = posicionHijoIzq(pos);
// 	int posDer = posicionHijoDer(pos);
// 	if (posDer > tope)
// 	{
// 		return posIzq;
// 	}
// 	else
// 	{
// 		if (heap[posIzq]->dato > heap[posDer]->dato)
// 		{
// 			return posDer;
// 		}
// 		else
// 		{
// 			return posIzq;
// 		}
// 	}
// }

// void insertarAlFinal(int elemento, int posicion)
// {
// 	nodo *ultimo = vectorPunterosFinal[posicion];
// 	nodo *aIns = new nodo();
// 	aIns->dato = elemento;
// 	aIns->sig = NULL;
// 	if (ultimo == NULL)
// 	{
// 		vector[posicion] = aIns;
// 	}
// 	else
// 	{
// 		ultimo->sig = aIns;
// 	}
// 	vectorPunterosFinal[posicion] = aIns;
// }

// void intercambiar(int pos1, int pos2)
// {
// 	nodo *intermedio = heap[pos1];
// 	heap[pos1] = heap[pos2];
// 	heap[pos2] = intermedio;
// }

// void flotar(int pos)
// {
// 	if (pos != RAIZ)
// 	{
// 		int posPadre = posicionPadre(pos);
// 		if (heap[pos] != NULL && heap[posPadre] != NULL)
// 		{
// 			if (heap[pos]->dato < heap[posPadre]->dato)
// 			{
// 				intercambiar(pos, posPadre);
// 				flotar(posPadre);
// 			}
// 		}
// 	}
// }

// void insertarEnHeap(node *nuevo)
// {
// 	if (nuevo != NULL)
// 	{
// 		tope++;
// 		heap[tope] = nuevo;
// 		flotar(tope);
// 	}
// }

int getVerticeWithIncidentZero(node **&graph, int quantityOfVertices)
{
    return 1;
}

void deleteNodeEdgesAndVertices()
{
}

void printTopologicalOrder()
{
}

void enqeue()
{
}

void desenqeue()
{
}

void updateGradesMatrix()
{
}

int main()
{
    node **heap;
    int quantityOfVertices;
    int quantityOfEdges;
    cin >> quantityOfVertices;
    cin >> quantityOfEdges;
    node **graph = new node *[quantityOfVertices];
    //Fill initialGrap
    for (int i = 0; i < quantityOfVertices; i++)
    {
        graph[i] = NULL;
    }
    //Fill with data coming from file
    for (int i = 0; i < quantityOfEdges; i++)
    {
        int verticeToInsert;
        int edgeFinal;
        cin >> verticeToInsert >> edgeFinal;
        //Create the new node which represent the edge
        node *newNode = new node();
        newNode->data = edgeFinal;
        newNode->distanceToOrigin = 0;
        newNode->sig = graph[verticeToInsert];
        //Insert the new edge in the vertice
        graph[verticeToInsert] = newNode;
    }

    for (int j = 0; j < quantityOfVertices; j++)
    {
        int verticeToPrint = getVerticeWithIncidentZero(graph, quantityOfVertices);
        if (verticeToPrint == 0)
        {
            break;
        }
        else
        {
            node *adjacent = graph[verticeToPrint];
            while (adjacent != NULL)
            {
                // enqeue();
                // entryGrade[adjacent->data]--;
                adjacent = adjacent->sig;
            }
        }
    }

    return 0;
}