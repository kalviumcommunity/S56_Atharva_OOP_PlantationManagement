#include <iostream>
#include <string>
using namespace std;

class Plant
{
public:
    Plant(string name, int numberOfPlants)
        : name(name), numberOfPlants(numberOfPlants) {}

    void display() const
    {
        cout << "Plant: " << this->getName() << ", Number of plants: " << this->getNumberOfPlants() << endl;
    }

    void setName(string newName)
    {
        this->name = newName;
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
    Tree(string name, int numberOfPlants)
        : Plant(name, numberOfPlants) {}

    void display() const
    {
        cout << "Tree: " << this->getName() << ", Number of trees: " << this->getNumberOfPlants() << endl;
    }
};

class Flower : public Plant
{
public:
    Flower(string name, int numberOfPlants)
        : Plant(name, numberOfPlants) {}

    void display() const
    {
        cout << "Flower: " << this->getName() << ", Number of flowers: " << this->getNumberOfPlants() << endl;
    }
};

int main()
{
    Tree oak("Oak", 10);
    Flower rose("Rose", 20);

    oak.display();
    rose.display();

    return 0;
}
