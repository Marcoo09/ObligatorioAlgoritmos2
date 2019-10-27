#include <iostream>
#include <string>
using namespace std;

struct nodo
{
	string dato;
	nodo *sig;
};

unsigned int funcHash(string &key, int tableSize)
{
	unsigned int hashVal = 0;
	for (int i = 0; i < key.length(); i++)
	{
		hashVal = 37 * hashVal + key[i];
	}
	return hashVal % tableSize;
}

void insertar(int posicion, nodo **&tabla, const string &key)
{
	nodo *aIns = new nodo;
	aIns->dato = key;
	aIns->sig = tabla[posicion];
	tabla[posicion] = aIns;
}

int existePalabra(string &key, int pos, nodo **&tabla, int tableSize)
{
	nodo *q = new nodo;
	q = tabla[pos];
	if (pos < 0 || pos > tableSize - 1)
	{
		return 0;
	}
	while (q != NULL)
	{
		if (key == q->dato)
		{
			return 1;
		}
		q = q->sig;
	}
	return 0;
}

int main()
{
	int n;
	cin >> n;
	int size = 0.75 * n;
	nodo **tabla = new nodo *[size];
	for (int i = 0; i < size; i++)
	{
		tabla[i] = NULL;
	}
	string palabra;
	for (int i = 0; i < n; i++)
	{
		cin >> palabra;
		int posicion = funcHash(palabra, size);
		insertar(posicion, tabla, palabra);
	}
	int m;
	cin >> m;
	int *retorno = new int[m];
	string palabraConsulta;
	for (int i = 0; i < m; i++)
	{
		cin >> palabraConsulta;
		int pos = funcHash(palabraConsulta, size);
		retorno[i] = existePalabra(palabraConsulta, pos, tabla, size);
	}
	for (int i = 0; i < m; i++)
	{
		cout << retorno[i] << endl;
	}
	return 0;
}