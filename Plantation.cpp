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
        cout << "Plant: " << name << ", Number of plants: " << numberOfPlants << endl;
    }

    void setName(string newName)
    {
        name = newName;
    }

protected:
    string getName() const
    {
        return name;
    }

    int getNumberOfPlants() const
    {
        return numberOfPlants;
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
        cout << "Tree: " << getName() << ", Number of trees: " << getNumberOfPlants() << endl;
    }
};

class Flower : public Plant
{
public:
    Flower(string name, int numberOfPlants)
        : Plant(name, numberOfPlants) {}

    void display() const
    {
        cout << "Flower: " << getName() << ", Number of flowers: " << getNumberOfPlants() << endl;
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
