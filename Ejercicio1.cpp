#include <iostream>
using namespace std;

int n;
bool varioAltura;

struct nodo
{
	int dato;
	int bal;
	nodo *der;
	nodo *izq;
};

void insertarEnAvl(nodo *&avl, int elemento)
{
	if (avl == NULL)
	{
		avl = new nodo;
		avl->dato = elemento;
		avl->bal = 0;
		avl->izq = avl->der = NULL;
		varioAltura = true;
	}
	else if (avl->dato > elemento)
	{
		insertarEnAvl(avl->izq, elemento);
		if (varioAltura)
		{
			switch (avl->bal)
			{
			case 1:
				avl->bal = 0;
				varioAltura = false;
				break;
			case 0:
				avl->bal = -1;
				varioAltura = false;
				break;
			case -1:
				if (avl->izq->bal == -1)
				{
					//II
					nodo *p1 = avl->izq;
					avl->izq = p1->der;
					p1->der = avl;
					avl->bal = 0;
					avl = p1;
				}
				else
				{
					//ID
					nodo *p1 = avl->izq;
					nodo *p2 = p1->der; //este es el que separamos
					p1->der = p2->izq;
					p2->izq = p1;
					avl->izq = p2->der;
					p2->der = avl;
					avl->bal = p2->bal == -1 ? 1 : 0;
					p1->bal = p2->bal == 1 ? -1 : 0;
					avl = p2;
				}
				avl->bal = 0;
				varioAltura = false;
			default:
				varioAltura = false;
				break;
			}
		}
	}
	else
	{
		insertarEnAvl(avl->der, elemento);
		if (varioAltura)
		{
			switch (avl->bal)
			{
			case -1:
				avl->bal = 0;
				varioAltura = false;
				break;
			case 0:
				avl->bal = 1;
				break;
			case 1:
				nodo *p1 = avl->der;
				if (p1->bal == 1)
				{
					//DD
					avl->der = p1->izq;
					p1->izq = avl;
					avl->bal = 0;
					avl = p1;
				}
				else
				{
					//DI
					nodo *p2 = p1->izq;
					p1->izq = p2->der;
					p2->der = p1;
					avl->der = p2->izq;
					p2->izq = avl;
					avl->bal = p2->bal == 1 ? -1 : 0;
					p1->bal = p2->bal == -1 ? 1 : 0;
					avl = p2;
				}
				avl->bal = 0;
				varioAltura = false;
			}
		}
	}
}

void imprimirInOrder(nodo *avl)
{
	if (avl != NULL)
	{
		imprimirInOrder(avl->izq);
		cout << avl->dato << endl;
		imprimirInOrder(avl->der);
	}
}

int main()
{
	cin >> n;
	nodo *avl = NULL;
	for (int i = 0; i < n; i++)
	{
		int elemento;
		cin >> elemento;
		insertarEnAvl(avl, elemento);
	}
	imprimirInOrder(avl);
}
