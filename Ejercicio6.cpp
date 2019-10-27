
#define ROOT 1
using namespace std;

struct edgeNode {
	int v;
	int w;
	int c;
};

struct listNode {
	int w;
	int c;
};

edgeNode* costHeap;

int* sets;
#include <iostream>

int top;
int numberOfEdges;

int numberOfVertices;

void initalizeSets() {
	for (int i = 1; i <= numberOfVertices; i++) sets[i] = 0;
}


int find(int e) {
	if (sets[e] == 0) {
		return e;
	}
	else {
		sets[e] = find(sets[e]);
		return sets[e];
	}
}

void merge(int e1, int e2) {
	sets[find(e2)] = find(e1);
}


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

int minimumSonPosition(int pos)
{
	int leftPos = leftSonPosition(pos);
	int rightPos = rightSonPosition(pos);
	if (rightPos > top)
	{
		return leftPos;
	}
	else
	{
		if (costHeap[leftPos].c > costHeap[rightPos].c)
		{
			return rightPos;
		}
		else
		{
			return leftPos;
		}
	}
}

bool isLeaf(int pos)
{
	return leftSonPosition(pos) > top;
}

void swap(int pos1, int pos2)
{
	edgeNode middle = costHeap[pos1];
	costHeap[pos1] = costHeap[pos2];
	costHeap[pos2] = middle;
}

void toSink(int pos)
{
	if (!isLeaf(pos))
	{
		int minimumSon = minimumSonPosition(pos);
		if (costHeap[minimumSon].c < costHeap[pos].c)
		{
			swap(minimumSon, pos);
			toSink(minimumSon);
		}
	}
}

void floatUp(int pos)
{
	if (pos != ROOT)
	{
		int fatherPos = fatherPosition(pos);
		{
			if (costHeap[pos].c < costHeap[fatherPos].c)
			{
				swap(pos, fatherPos);
				floatUp(fatherPos);
			}
		}
	}

}
void insertInHeap(edgeNode newNode)
{
	top++;
	costHeap[top] = newNode;
	floatUp(top);
}

edgeNode getMinimum()
{
	return costHeap[ROOT];
}

void removeMinimum()
{
	edgeNode min = costHeap[ROOT];
	costHeap[ROOT] = costHeap[top];
	top--;
	toSink(ROOT);
}

int costOfMinimumSpanningTree() {
	int ret = 0;
	int cont = 0;
	for (int i = 1; i <= numberOfEdges && cont < numberOfVertices - 1; i++) {
		edgeNode min = getMinimum();
		removeMinimum();
		int v = min.v;
		int w = min.w;
		int c = min.c;
		if (find(w) != find(v)) {
			merge(v, w);
			ret += c;
			cont++;
		}
	}
	return ret;
}

int main()
{
	top = 0;
	cin >> numberOfVertices;
	cin >> numberOfEdges;
	sets = new int[numberOfVertices + 1];
	initalizeSets();
	costHeap = new edgeNode[numberOfEdges + 1];
	for (int i = 1; i <= numberOfEdges; i++) {
		int v;
		int w;
		int c;
		cin >> v >> w >> c;
		edgeNode edgeToAdd;
		edgeToAdd.v = v;
		edgeToAdd.w = w;
		edgeToAdd.c = c;
		insertInHeap(edgeToAdd);
	}
	int cost = costOfMinimumSpanningTree();
	cout << cost;
	return 0;
}

