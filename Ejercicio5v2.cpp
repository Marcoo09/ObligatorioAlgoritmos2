#include <iostream>
#define INF 999999
#define RAIZ 1
using namespace std;


struct TablaDijkstra {
	bool conocido;
	int anterior;
	int costo;
};

struct Nodo {
	int vertice;
	int costo;
};

struct nodoL {
	int vertice;
	int costo;
	nodoL* sig;
};

Nodo* heap;
int tope;
TablaDijkstra* tablaDijkstra;
int* hashing;



void inicializarTabla(int cantVertices, int origen) {
	tablaDijkstra = new TablaDijkstra[cantVertices + 1];
	for (int i = 1; i <= cantVertices; i++) {
		tablaDijkstra[i].conocido = false;
		tablaDijkstra[i].costo = INF;
		tablaDijkstra[i].anterior = -1;
	}
	tablaDijkstra[origen].costo = 0;
}




int posicionPadre(int pos)
{
	return pos / 2;
}

int posicionHijoIzq(int pos)
{
	return pos * 2;
}

int posicionHijoDer(int pos)
{
	return pos * 2 + 1;
}

int obtenerPosMinimoHijo(int pos)
{
	int posIzq = posicionHijoIzq(pos);
	int posDer = posicionHijoDer(pos);
	if (posDer > tope)
	{
		return posIzq;
	}
	else
	{
		if (heap[posIzq].costo > heap[posDer].costo)
		{
			return posDer;
		}
		else
		{
			return posIzq;
		}
	}
}


void intercambiar(int pos1, int pos2)
{
	Nodo intermedio = heap[pos1];
	heap[pos1] = heap[pos2];
	heap[pos2] = intermedio;
}

void flotar(int pos)
{
	if (pos != RAIZ)
	{
		int posPadre = posicionPadre(pos);
		{
			
			if (heap[pos].costo < heap[posPadre].costo)
			{
				hashing[heap[pos].vertice] = posPadre;
				hashing[heap[posPadre].vertice] = pos;
				intercambiar(pos, posPadre);
				flotar(posPadre);
			}
		}
	}

}

void insertarEnHeap(Nodo nuevo)
{
	tope++;
	heap[tope] = nuevo;
	flotar(tope);
}

void inicializarHeap(int origen, int cantVertices) {
	heap = new Nodo[cantVertices + 1];
	for (int i = 1; i <= cantVertices; i++) {
		Nodo nuevo;
		nuevo.vertice = i;
		if (i != origen) {
			nuevo.costo = INF;
		}
		else {
			nuevo.costo = 0;
		}
		insertarEnHeap(nuevo);
	}
}


bool esHoja(int pos)
{
	return posicionHijoIzq(pos) > tope;
}



void hundir(int pos)
{
	if (!esHoja(pos))
	{
		int posMinimoHijo = obtenerPosMinimoHijo(pos);
		if (heap[posMinimoHijo].costo < heap[pos].costo)
		{
			hashing[heap[pos].vertice] = posMinimoHijo;
			hashing[heap[posMinimoHijo].vertice] = pos;
			intercambiar(posMinimoHijo, pos);
			hundir(posMinimoHijo);
		}
	}
}

void eliminarMinimo()
{
	Nodo min = heap[RAIZ];
	heap[RAIZ] = heap[tope];
	tope--;
	hundir(RAIZ);
}

void modificarCosto(int vertice, int nuevoCosto) {
	int indiceHeap = hashing[vertice];
	heap[indiceHeap].costo = nuevoCosto;
	hundir(indiceHeap);
	flotar(indiceHeap);
}


void Dijkstra(nodoL** g, int cantVertices, int origen) {
	inicializarTabla(cantVertices, origen);
	while (tope > 0) {
		Nodo min = heap[RAIZ];
		eliminarMinimo();
		tablaDijkstra[min.vertice].conocido = true;
		nodoL* ady = g[min.vertice];
		while (ady != NULL) {
			if (!tablaDijkstra[ady->vertice].conocido) {
				if (tablaDijkstra[ady->vertice].costo > tablaDijkstra[min.vertice].costo + ady->costo) {
					tablaDijkstra[ady->vertice].costo = tablaDijkstra[min.vertice].costo + ady->costo;
					tablaDijkstra[ady->vertice].anterior = min.vertice;
					modificarCosto(ady->vertice, tablaDijkstra[min.vertice].costo + ady->costo);
				}
			}
			ady = ady->sig;
		}
	}
}

void imprimirTabla(int cantVertices) {
	for (int i = 1; i <= cantVertices; i++) {
		if (tablaDijkstra[i].costo == 0 || tablaDijkstra[i].costo == INF) {
			cout << -1 << endl;
		}
		else {
			cout << tablaDijkstra[i].costo << endl;
		}
	}
}

int main()
{
	int cantVertices;
	int cantAristas;
	cin >> cantVertices;
	cin >> cantAristas;
	nodoL** grafo = new nodoL * [cantVertices + 1];
	hashing = new int[cantVertices + 1];
	for (int i = 0; i <= cantVertices; i++) hashing[i] = i;
	for (int i = 0; i <= cantVertices; i++) grafo[i] = NULL;
	for (int i = 0; i < cantAristas; i++) {
		int v;
		int w;
		int costo;
		cin >> v >> w >> costo;
		nodoL* nuevoNodo = new nodoL();
		nuevoNodo->vertice = w;
		nuevoNodo->costo = costo;
		nuevoNodo->sig = grafo[v];
		grafo[v] = nuevoNodo;
	}
	int cantVerticesConsulta;
	cin >> cantVerticesConsulta;
	for (int i = 0; i < cantVerticesConsulta; i++) {
		int origen = 0;
		cin >> origen;
		inicializarHeap(origen, cantVertices);
		Dijkstra(grafo, cantVertices, origen);
		imprimirTabla(cantVertices);
		for (int i = 0; i <= cantVertices; i++) hashing[i] = i;
	}

}
