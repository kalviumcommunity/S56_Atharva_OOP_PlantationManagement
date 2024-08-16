#include <iostream>
#include <string>
using namespace std;

class Plant
{
public:
    Plant(string name = "", int numberOfPlants = 0)
        : name(name), numberOfPlants(numberOfPlants) {}

    void display() const
    {
        cout << "Plant: " << this->getName() << ", Number of plants: " << this->getNumberOfPlants() << endl;
    }

    void setName(string newName)
    {
        this->name = newName;
    }

    void setNumberOfPlants(int numPlants)
    {
        this->numberOfPlants = numPlants;
    }

protected:
    string getName() const
    {
        return this->name;
    }

    int getNumberOfPlants() const
    {
        return this->numberOfPlants;
    }

private:
    string name;
    int numberOfPlants;
};

class Tree : public Plant
{
public:
    static int totalTrees;

    Tree(string name = "", int numberOfPlants = 0)
        : Plant(name, numberOfPlants)
    {
        totalTrees++;
    }

    void display() const
    {
        cout << "Tree: " << this->getName() << ", Number of trees: " << this->getNumberOfPlants() << endl;
    }

    static void displayTotalTrees()
    {
        cout << "Total number of trees: " << totalTrees << endl;
    }
};

int Tree::totalTrees = 0;

class Flower : public Plant
{
public:
    static int totalFlowers;

    Flower(string name = "", int numberOfPlants = 0)
        : Plant(name, numberOfPlants)
    {
        totalFlowers++;
    }

    void display() const
    {
        cout << "Flower: " << this->getName() << ", Number of flowers: " << this->getNumberOfPlants() << endl;
    }

    static void displayTotalFlowers()
    {
        cout << "Total number of flowers: " << totalFlowers << endl;
    }
};

int Flower::totalFlowers = 0;

int main()
{
    int numTrees, numFlowers;

    cout << "Enter the number of trees: ";
    cin >> numTrees;

    cout << "Enter the number of flowers: ";
    cin >> numFlowers;

    Tree **trees = new Tree *[numTrees];
    Flower **flowers = new Flower *[numFlowers];

    for (int i = 0; i < numTrees; ++i)
    {
        trees[i] = new Tree;
        string name;
        int numberOfPlants;

        cout << "Enter name for tree " << i + 1 << ": ";
        cin >> name;
        cout << "Enter number of trees for " << name << ": ";
        cin >> numberOfPlants;

        trees[i]->setName(name);
        trees[i]->setNumberOfPlants(numberOfPlants);
    }

    for (int i = 0; i < numFlowers; ++i)
    {
        flowers[i] = new Flower;
        string name;
        int numberOfPlants;

        cout << "Enter name for flower " << i + 1 << ": ";
        cin >> name;
        cout << "Enter number of flowers for " << name << ": ";
        cin >> numberOfPlants;

        flowers[i]->setName(name);
        flowers[i]->setNumberOfPlants(numberOfPlants);
    }

    cout << "\nTrees:\n";
    for (int i = 0; i < numTrees; ++i)
    {
        trees[i]->display();
    }

    cout << "\nFlowers:\n";
    for (int i = 0; i < numFlowers; ++i)
    {
        flowers[i]->display();
    }

    cout << endl;
    Tree::displayTotalTrees();
    Flower::displayTotalFlowers();

    for (int i = 0; i < numTrees; ++i)
    {
        delete trees[i];
    }
    delete[] trees;

    for (int i = 0; i < numFlowers; ++i)
    {
        delete flowers[i];
    }
    delete[] flowers;

    return 0;
}
