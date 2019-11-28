#include <iostream>

using namespace std;

#define ROOT 1

struct node
{
    int data;
    node *sig;
};

struct heapNode
{
    int data;
    int distanceToOrigen;
};

heapNode *heap;
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

heapNode getMin()
{
    return heap[ROOT];
}

bool isLeaf(int pos)
{
    return leftSonPosition(pos) > top;
}

int getMinSonPositionForDistanceToOrigin(int pos)
{
    int leftPos = leftSonPosition(pos);
    int rightPos = rightSonPosition(pos);
    if (rightPos > top)
    {
        return leftPos;
    }
    else if (heap[leftPos].distanceToOrigen > heap[rightPos].distanceToOrigen)
    {
        return rightPos;
    }
    else if (heap[leftPos].distanceToOrigen < heap[rightPos].distanceToOrigen)
    {
        return leftPos;
    }
    else
    {
        if (heap[leftPos].data < heap[rightPos].data)
        {
            return leftPos;
        }
        else
        {
            return rightPos;
        }
    }
}

void exchanges(int pos1, int pos2)
{
    heapNode mediumNode = heap[pos1];
    heap[pos1] = heap[pos2];
    heap[pos2] = mediumNode;
}

void sink(int pos)
{
    if (!isLeaf(pos))
    {
        int sonPosition = getMinSonPositionForDistanceToOrigin(pos);
        if (heap[sonPosition].distanceToOrigen < heap[pos].distanceToOrigen)
        {
            exchanges(sonPosition, pos);
            sink(sonPosition);
        }
        else if (heap[sonPosition].distanceToOrigen == heap[pos].distanceToOrigen)
        {
            if (heap[sonPosition].data < heap[pos].data)
            {
                exchanges(sonPosition, pos);
                sink(sonPosition);
            }
        }
    }
}

void deleteMin()
{
    heap[ROOT] = heap[top];
    top--;
    sink(ROOT);
}

void floatUp(int pos)
{
    if (pos != ROOT)
    {
        int fatherPos = fatherPosition(pos);
        if (heap[pos].distanceToOrigen < heap[fatherPos].distanceToOrigen)
        {
            exchanges(pos, fatherPos);
            floatUp(fatherPos);
        }
        else if ((heap[pos].distanceToOrigen) == (heap[fatherPos].distanceToOrigen))
        {
            if (heap[pos].data < heap[fatherPos].data)
            {
                exchanges(pos, fatherPos);
                floatUp(fatherPos);
            }
        }
    }
}

void enqeue(heapNode newNode)
{
    top++;
    heap[top] = newNode;
    floatUp(top);
}

int main()
{
    int quantityOfVertices;
    int quantityOfEdges;
    cin >> quantityOfVertices;
    cin >> quantityOfEdges;
    node **graph = new node *[quantityOfVertices + 1];
    int *entryGrade = new int[quantityOfVertices + 1];
    heap = new heapNode[quantityOfVertices + 1];
    //int cont = 1;
    //Fill initialGrap
    for (int i = 0; i <= quantityOfVertices; i++)
    {
        graph[i] = NULL;
    }
    for (int i = 0; i <= quantityOfVertices; i++)
    {
        entryGrade[i] = 0;
        heap[i].data = 0;
        heap[i].distanceToOrigen = 0;
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
        newNode->sig = graph[verticeToInsert];
        //Insert the new edge in the vertice
        graph[verticeToInsert] = newNode;
        entryGrade[edgeFinal]++;
    }
    for (int j = 1; j <= quantityOfVertices; j++)
    {
        if (entryGrade[j] == 0)
        {
            heapNode newNode;
            newNode.data = j;
            newNode.distanceToOrigen = 0;
            enqeue(newNode);
        }
    }
    while (top != 0)
    {
        heapNode vertice = getMin();
        deleteMin();
        cout << vertice.data << endl;
        node *adjacent = graph[vertice.data];
        heapNode toAdd;
        while (adjacent != NULL)
        {
            toAdd.data = adjacent->data;
            entryGrade[adjacent->data]--;
            if (entryGrade[adjacent->data] == 0)
            {
                toAdd.distanceToOrigen = vertice.distanceToOrigen + 1;
                enqeue(toAdd);
            }
            adjacent = adjacent->sig;
        }
    }
    return 0;
}