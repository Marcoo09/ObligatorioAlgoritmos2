#include <iostream>

using namespace std;

#define ROOT 1

struct node
{
    int data;
    int distanceToOrigin;
    node *sig;
};

node **heap;
int top = 0;

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

node *getMin()
{
    return heap[ROOT];
}

bool isLeaf(int pos)
{
    return leftSonPosition(pos) > top;
}

int getMinSonPositionForData(int pos)
{
    int leftPos = leftSonPosition(pos);
    int rightPos = rightSonPosition(pos);
    if (rightPos > top)
    {
        return leftPos;
    }
    else if (heap[leftPos]->data > heap[rightPos]->data)
    {
        return rightPos;
    }
    else
    {
        return leftPos;
    }
}

int getMinSonPositionForDistanceToOrigin(int pos)
{
    int leftPos = leftSonPosition(pos);
    int rightPos = rightSonPosition(pos);
    if (rightPos > top)
    {
        return leftPos;
    }
    else if (heap[leftPos]->distanceToOrigin > heap[rightPos]->distanceToOrigin)
    {
        return rightPos;
    }
    else
    {
        return leftPos;
    }
}

void sink(int pos)
{
    cout << "pos " << pos << endl;
    if (!isLeaf(pos))
    {
        cout << "no es hoja" << endl;
        int sonPosition = getMinSonPositionForDistanceToOrigin(pos);
        cout << "sonPosition " << sonPosition << endl;
        if (heap[sonPosition] != NULL && heap[pos] != NULL)
        {
            cout << "entre al primer if " << endl;
            if (heap[sonPosition]->distanceToOrigin < heap[pos]->distanceToOrigin)
            {
                cout << "entre  al if anidado" << endl;
                swap(sonPosition, pos);
                sink(sonPosition);
            }
            // else if (heap[sonPosition]->distanceToOrigin == heap[pos]->distanceToOrigin)
            // {
            //     cout << "entre al else if anidado" << endl;
            //     if (heap[sonPosition]->data < heap[pos]->data)
            //     {
            //         cout << "entre al if dentro del else if" << endl;
            //         swap(sonPosition, pos);
            //         sink(sonPosition);
            //     }
            // }
            cout << "no entre a ninguno" << endl;
        }
    }
}

void swap(int pos1, int pos2)
{
    node *mediumNode = heap[pos1];
    heap[pos1] = heap[pos2];
    heap[pos2] = mediumNode;
}

void deleteMin()
{
    node *min = heap[ROOT];
    cout << "el min es " << min->data << endl;
    heap[ROOT] = heap[top];
    top--;
    cout << "el top es " << top << endl;
    sink(ROOT);
}

void floatUp(int pos)
{
    if (pos != ROOT)
    {
        int fatherPos = fatherPosition(pos);
        if (heap[pos] != NULL && heap[fatherPos] != NULL)
        {
            if (heap[pos]->distanceToOrigin < heap[fatherPos]->distanceToOrigin)
            {
                swap(pos, fatherPos);
                floatUp(fatherPos);
            }
            else if ((heap[pos]->distanceToOrigin) == (heap[fatherPos]->distanceToOrigin))
            {
                if (heap[pos]->data < heap[fatherPos]->data)
                {
                    swap(pos, fatherPos);
                    floatUp(fatherPos);
                }
            }
        }
    }
}

void enqeue(node *newNode)
{
    if (newNode != NULL)
    {
        top++;
        heap[top] = newNode;
        floatUp(top);
    }
}

void printTopologicalOrder(int *result, int vertices)
{
    for (int i = 0; i < vertices; i++)
    {
        cout << result[i] << endl;
    }
}

int main()
{
    int quantityOfVertices;
    int quantityOfEdges;
    cin >> quantityOfVertices;
    cin >> quantityOfEdges;
    node **graph = new node *[quantityOfVertices + 1];
    int *entryGrade = new int[quantityOfVertices + 1];
    int *printArray = new int[quantityOfVertices + 1];
    heap = new node *[quantityOfVertices + 1];
    int cont = 1;
    //Fill initialGrap
    for (int i = 1; i <= quantityOfVertices; i++)
    {
        graph[i] = NULL;
    }
    for (int i = 1; i <= quantityOfVertices; i++)
    {
        entryGrade[i] = 0;
        printArray[i] = 0;
        heap[i] = NULL;
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
        entryGrade[edgeFinal]++;
    }
    for (int j = 1; j <= quantityOfVertices; j++)
    {
        if (entryGrade[j] == 0)
        {
            cout << "el vertice " << j << " tiene grado 0" << endl;
            node *newNode = new node();
            newNode->data = j;
            newNode->distanceToOrigin = 0;
            newNode->sig = NULL;
            enqeue(newNode);
        }
    }
    while (top != 0)
    {
        cout << "entre " << endl;
        int vertice = getMin()->data;
        cout << "con vertice " << vertice << endl;
        deleteMin();
        cout << "borre el min " << endl;
        printArray[cont] = vertice;
        cont++;
        cout << "cont" << cont << endl;
        node *adjacent = graph[vertice];
        while (adjacent != NULL)
        {
            cout << "recorro los adjacentes, estoy en " << adjacent->data << endl;
            entryGrade[adjacent->data]--;
            if (entryGrade[adjacent->data] == 0)
            {
                cout << "agrego el adyacente " << adjacent->data << " a la cola" << endl;
                adjacent->distanceToOrigin = graph[vertice]->distanceToOrigin + 1;
                enqeue(adjacent);
            }
            adjacent = adjacent->sig;
        }
    }
    printTopologicalOrder(printArray, quantityOfVertices);
    return 0;
}