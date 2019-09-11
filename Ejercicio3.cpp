#include <iostream>

#define RAIZ 1

using namespace std;

struct nodo {
	int dato;
	nodo* sig;
};

nodo** vector;
nodo** vectorPunterosFinal;
nodo** heap;
int tope;

int posicionPadre(int pos)
{
	return pos / 2;
}

int posicionHijoIzq(int pos) {
	return pos * 2;
}

int posicionHijoDer(int pos) {
	return pos * 2 + 1;
}

int obtenerPosMinimoHijo(int pos) {
	int posIzq = posicionHijoIzq(pos);
	int posDer = posicionHijoDer(pos);
	if (posDer > tope) {
		return posIzq;
	}
	else {
		if (heap[posIzq]->dato > heap[posDer]->dato) {
			return posDer;
		}
		else {
			return posIzq;
		}
	}
}

void insertarAlFinal(int elemento, int posicion) {
	//nodo* lista = vector[posicion];
	nodo* ultimo = vectorPunterosFinal[posicion];
	nodo* aIns = new nodo();
	aIns->dato = elemento;
	aIns->sig = NULL;
	if (ultimo == NULL) {
		vector[posicion] = aIns;
	}
	else {
		ultimo->sig = aIns;
	}
	vectorPunterosFinal[posicion] = aIns;
}

void intercambiar(int pos1, int pos2)
{
	nodo* intermedio = heap[pos1];
	heap[pos1] = heap[pos2];
	heap[pos2] = intermedio;
}

void flotar(int pos) {
	if (pos != RAIZ) {
		int posPadre = posicionPadre(pos);
		if (heap[pos] != NULL && heap[posPadre] != NULL) {
			if (heap[pos]->dato < heap[posPadre]->dato) {
				intercambiar(pos, posPadre);
				flotar(posPadre);
			}
		}
	}
}

void insertarEnHeap(nodo* nuevo) {
	if (nuevo != NULL) {
		tope++;
		heap[tope] = nuevo;
		flotar(tope);
	}
}

bool esHoja(int pos) {
	return posicionHijoIzq(pos) > tope;
}

nodo* obtenerMinimo() {
	return heap[RAIZ];
}

void hundir(int pos) {
	if (!esHoja(pos)) {
		int posMinimoHijo = obtenerPosMinimoHijo(pos);
		if (heap[posMinimoHijo] != NULL && heap[pos] != NULL) {
			if (heap[posMinimoHijo]->dato < heap[pos]->dato) {
				intercambiar(posMinimoHijo, pos);
				hundir(posMinimoHijo);
			}
		}
	}
}

void eliminarMinimo() {
	nodo* min = heap[RAIZ];
	heap[RAIZ] = heap[tope];
	tope--;
	hundir(RAIZ);
	insertarEnHeap(min->sig);
}

bool estaVacio(int cant) {
	for (int i = 1; i <= cant; i++) {
		nodo* lista = heap[i];
		if (lista != NULL) {
			return false;
		}
	}
	return true;
}

int main() {
	int k;
	cin >> k;
	tope = 0;
	vector = new nodo * [k + 1];
	vectorPunterosFinal = new nodo * [k + 1];
	for (int i = 1; i <= k; i++) {
		vector[i] = NULL;
		vectorPunterosFinal[i] = NULL;
	}
	for (int i = 1; i <= k; i++) {
		int cantElem;
		cin >> cantElem;
		for (int j = 0; j < cantElem; j++) {
			int elemento;
			cin >> elemento;
			insertarAlFinal(elemento, i);
		}
	}
	heap = new nodo * [k + 1];
	for (int i = 1; i <= k; i++) {
		insertarEnHeap(vector[i]);
	}
	while (tope!=0) {
		nodo* min = obtenerMinimo();
		cout << min->dato << endl;
		eliminarMinimo();
	}
	return 0;
}
