#include <iostream>

using namespace std;
typedef pair<int, int> pii;

struct node
{
    int initialCoordinate;
    int finalCoordinate;
    int height;
};

struct nodeResult
{
    pii *result;
    int capacity;
    int quantityOfElements;
    nodeResult(int capacity)
    {
        capacity = capacity;
        result = new pii[capacity];
        quantityOfElements = 0;
    }
};

int quantityOfShades;
node **shades;

void initializeShades()
{
    for (int i = 0; i < quantityOfShades; i++)
    {
        shades[i] = NULL;
    }
}

nodeResult *add(nodeResult *currentNode, pii newNode)
{
    if (currentNode->quantityOfElements > 0 && currentNode->result[currentNode->quantityOfElements - 1].second == newNode.second)
    {
        return currentNode;
    }
    if (currentNode->quantityOfElements > 0 && currentNode->result[currentNode->quantityOfElements - 1].first == newNode.first)
    {
        currentNode->result[currentNode->quantityOfElements - 1].second = currentNode->result[currentNode->quantityOfElements - 1].second > newNode.second ? currentNode->result[currentNode->quantityOfElements - 1].second : newNode.second;

        return currentNode;
    }
    currentNode->result[currentNode->quantityOfElements] = newNode;
    currentNode->quantityOfElements++;
}

nodeResult *merge(nodeResult *left, nodeResult *right, int lenghtLeft, int lengthRight)
{
    nodeResult *result = new nodeResult(left->quantityOfElements + right->quantityOfElements);
    int height1 = 0, height2 = 0;

    int i = 0;
    int j = 0;
    while (i < left->quantityOfElements && j < right->quantityOfElements)
    {
        if (left->result[i].first < right->result[j].first)
        {

            int leftPosition = left->result[i].first;
            height1 = left->result[i].second;
            pii newNode;
            newNode.first = leftPosition;
            newNode.second = height2 > height1 ? height2 : height1;
            result = add(result, newNode);
            i++;
        }
        else
        {
            int rightPosition = right->result[j].first;
            height2 = right->result[j].second;
            pii newNode;
            newNode.first = rightPosition;
            newNode.second = height2 > height1 ? height2 : height1;
            result = add(result, newNode);
            j++;
        }
    }
    while (i < left->quantityOfElements)
    {
        result = add(result, left->result[i]);

        i++;
    }
    while (j < right->quantityOfElements)
    {
        result = add(result, right->result[j]);
        j++;
    }
    return result;
}

nodeResult *getContours(node **shades, int left, int right)
{
    nodeResult *l;
    nodeResult *r;
    if (left == right)
    {
        nodeResult *result = new nodeResult(2);
        result->result[0].first = shades[left]->initialCoordinate;
        result->result[0].second = shades[left]->height;
        result->result[1].first = shades[left]->finalCoordinate;
        result->result[1].second = 0;
        result->quantityOfElements++;
        result->quantityOfElements++;
        return result;
    }
    else
    {
        int middle = (right + left) / 2;
        l = getContours(shades, left, middle);
        r = getContours(shades, middle + 1, right);
        return merge(l, r, middle - left + 1, right - middle);
    }
}

void printContours(pii *result, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << result[i].first << " " << result[i].second << endl;
    }
}

int main()
{
    cin >> quantityOfShades;
    shades = new node *[quantityOfShades];
    initializeShades();
    for (int i = 0; i < quantityOfShades; i++)
    {
        int initialCoordinate;
        int finalCoordinate;
        int height;
        cin >> initialCoordinate >> finalCoordinate >> height;
        node *newNode = new node();
        newNode->initialCoordinate = initialCoordinate;
        newNode->finalCoordinate = finalCoordinate;
        newNode->height = height;
        shades[i] = newNode;
    }
    nodeResult *result = getContours(shades, 0, quantityOfShades - 1);
    printContours(result->result, result->quantityOfElements);
    return 0;
}
