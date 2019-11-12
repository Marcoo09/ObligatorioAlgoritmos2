#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int cases;
int kFloorsToMove;
int heightBuilding;
int quantityOfFloorsAttended;
int* gang;
int* operators;

void initializeArrays()
{
	gang = new int[heightBuilding];
	operators = new int[heightBuilding];
	for (int i = 0; i < heightBuilding; i++) {
		gang[i] = -1;
		operators[i] = -1;
	}
}


int getQuantityOfFloorsAttended()
{
	int count = 0;
	int index1 = 0;
	int index2 = 0;
	while (gang[index1] != -1 && operators[index2] != -1 && count < heightBuilding) {
		if (abs(gang[index1] - operators[index2]) <= kFloorsToMove) {
			count++;
			index1++;
			index2++;
		}
		else if (gang[index1]<=operators[index2]){
			index1++;
		}
		else {
			index2++;
		}
	}
	return count;
}


int main()
{
	cin >> cases;
	for (int i = 0; i < cases; i++)
	{
		quantityOfFloorsAttended = 0;
		cin >> kFloorsToMove;
		cin >> heightBuilding;
		initializeArrays();
		char c;
		string line;
		cin.ignore();
		getline(cin, line);
		// cout << "line " << line << endl;
		istringstream iss(line);
		int index1 = 0;
		int res1 = 0;
		int index2 = 0;
		int res2 = 0;
		while (iss >> c)
		{
			if (c != ' ')
			{
				if (c == 'C')
				{
					gang[index1] = res1;
					index1++;

				}
				else
				{
					operators[index2] = res2;
					index2++;
				}
				res2++;
				res1++;
			}
		}
		quantityOfFloorsAttended = getQuantityOfFloorsAttended();
		cout << quantityOfFloorsAttended << " " << endl;
	}
	return 0;
}