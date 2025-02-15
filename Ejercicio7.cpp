#include <iostream>
#define INF 9999
using namespace std;

int numberOfEdges;
int numberOfVertices;
int **graph;
bool *visited;

void initializeGraph()
{
	graph = new int *[numberOfVertices + 1];
	for (int i = 1; i <= numberOfVertices; i++)
	{
		graph[i] = new int[numberOfVertices + 1];
		for (int j = 1; j <= numberOfVertices; j++)
		{
			graph[i][j] = INF;
		}
	}
}

void initializeVisitedArray()
{
	visited = new bool[numberOfVertices + 1];
	for (int i = 1; i <= numberOfVertices; i++)
		visited[i] = false;
}

void DFS(int origin)
{
	visited[origin] = true;
	for (int w = 1; w <= numberOfVertices; w++)
	{
		if (graph[origin][w] == 1)
		{
			if (!visited[w])
			{
				DFS(w);
			}
		}
	}
}

int numberOfComponents()
{
	int quantityOfComponents = 0;
	for (int i = 1; i <= numberOfVertices; i++)
	{
		if (!visited[i])
		{
			DFS(i);
			quantityOfComponents++;
		}
	}
	return quantityOfComponents;
}

int main()
{
	cin >> numberOfVertices;
	cin >> numberOfEdges;
	initializeGraph();
	initializeVisitedArray();
	for (int i = 1; i <= numberOfEdges; i++)
	{
		int v;
		int w;
		cin >> v >> w;
		graph[v][w] = 1;
		graph[w][v] = 1;
	}
	int components = numberOfComponents();
	cout << components;
	return 0;
}
