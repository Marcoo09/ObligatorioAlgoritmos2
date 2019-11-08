#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int cases;
int kFloorsToMove;
int heightBuilding;
int quantityOfFloorsAttended;
//1 == O && 0 == C && -1 if atendido o atendió
int *building;

void initializeBuildingArray()
{
    building = new int[heightBuilding];
    for (int i = 0; i < heightBuilding; i++)
        building[i] = 0;
}

bool isFactible(int index)
{
    return index >= 0 && index < heightBuilding && building[index] == 0;
}

int getOptimumIndex(int i)
{
    int betterIndex = -1;
    bool founded = false;
    int k = kFloorsToMove;
    while (k >= 1 && !founded)
    {
        if (isFactible(i + k))
        {
            betterIndex = i + k;
            building[i + k] = -1;
            founded = true;
        }
        else if (isFactible(i - k))
        {
            betterIndex = i - k;
            building[i - k] = -1;
            founded = true;
        }
        else
        {
            k--;
        }
    }
    return betterIndex;
}

int getQuantityOfFloorsAttended()
{
    int returnedValue = 0;
    for (int i = 0; i < heightBuilding; i++)
    {
        int currentValue = building[i];
        //He/She is O
        if (currentValue == 1)
        {
            int optimumIndex = getOptimumIndex(i);
            if (optimumIndex != -1)
            {
                building[i] = -1;
                returnedValue++;
            }
        }
    }
    return returnedValue;
}

void printArray()
{
    for (int i = 0; i < heightBuilding; i++)
    {
        cout << building[i] << " aa" << endl;
    }
}

int main()
{
    cin >> cases;
    for (int i = 0; i < cases; i++)
    {
        quantityOfFloorsAttended = 0;
        cin >> kFloorsToMove;
        cin >> heightBuilding;
        initializeBuildingArray();
        char c;
        string line;
        cin.ignore();
        getline(cin, line);
        // cout << "line " << line << endl;
        istringstream iss(line);
        int index = 0;
        while (iss >> c)
        {
            if (c != ' ')
            {
                if (c == 'C')
                {
                    building[index] = 0;
                }
                else
                {
                    building[index] = 1;
                }
                index++;
            }
        }
        quantityOfFloorsAttended = getQuantityOfFloorsAttended();
        cout << quantityOfFloorsAttended << " " << endl;
    }
    return 0;
}
