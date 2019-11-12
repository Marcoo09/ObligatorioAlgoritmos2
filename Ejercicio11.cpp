#include <iostream>

using namespace std;

unsigned long **pascalMatrix;
long long *prevResults;
long long *results;

long long getCombinations(int n, int k)
{
    prevResults = new long long[k + 1];
    results = new long long[k + 1];
    prevResults[0] = 1;
    results[0] = 1;
    for (int p = 1; p <= k; p++)
    {
        prevResults[p] = 0;
        results[p] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j <= k; j++)
        {
            results[j] = prevResults[j - 1] + prevResults[j];
        }
        prevResults = results;
        prevResults = new long long[k + 1];
        for (int p = 0; p <= k; p++)
        {
            prevResults[p] = results[p];
        }
    }
    return results[k];
}

int main()
{
    int maxValue;
    int cases;

    cin >> maxValue >> cases;

    while (cases > 0)
    {
        int n;
        int k;
        cin >> n >> k;
        cout << getCombinations(n, k) << endl;
        cases--;
    }

    return 0;
}