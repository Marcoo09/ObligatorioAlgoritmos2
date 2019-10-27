#include <iostream>

using namespace std;

struct node
{
    int w;
    node *sig;
};

int numberOfVertices;
int numberOfEdges;
node **graph;
bool *visited;
int *paths;
bool isThereACycle = false;

void initializeVisitedAndPathsArray()
{
    visited = new bool[numberOfVertices + 1];
    paths = new int[numberOfVertices + 1];
    for (int i = 1; i <= numberOfVertices; i++)
    {
        visited[i] = false;
        paths[i] = 0;
    }
}

void initializeGraph()
{
    for (int i = 1; i <= numberOfVertices; i++)
    {
        graph[i] = NULL;
    }
}

void DFS(int origin)
{
    visited[origin] = true;
    paths[origin] = 1;
    node *adjacents = graph[origin];
    while (adjacents != NULL)
    {
        if (!visited[adjacents->w])
        {
            DFS(adjacents->w);
        }
        else
        {
            if (paths[adjacents->w])
            {
                isThereACycle = true;
            }
        }
        adjacents = adjacents->sig;
    }
    paths[origin] = 0;
}

int hasCycles()
{
    for (int i = 1; i <= numberOfVertices; i++)
    {
        if (!visited[i])
        {
            DFS(i);
        }
    }
    return isThereACycle ? 1 : 0;
}

int main()
{
    cin >> numberOfVertices;
    cin >> numberOfEdges;
    graph = new node *[numberOfVertices + 1];
    initializeVisitedAndPathsArray();
    initializeGraph();
    for (int i = 0; i < numberOfEdges; i++)
    {
        int v;
        int w;
        cin >> v >> w;
        node *newNode = new node();
        newNode->w = w;
        newNode->sig = graph[v];
        graph[v] = newNode;
    }
    int itHasCycles = hasCycles();
    cout << itHasCycles;
    return 0;
}
