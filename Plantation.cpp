#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
using namespace std;

class Plant
{
public:
    Plant(string name = "", int numberOfPlants = 0, time_t plantingDate = time(nullptr))
        : name(name), numberOfPlants(numberOfPlants), plantingDate(plantingDate) {}

    void display() const
    {
        cout << "Plant: " << this->getName() << ", Number of plants: " << this->getNumberOfPlants()
             << ", Planted on: " << this->formatDate(this->getPlantingDate())
             << ", Days since planting: " << this->daysSincePlanting() << endl;
    }

    void setName(string newName)
    {
        this->name = newName;
    }

    void setNumberOfPlants(int numPlants)
    {
        this->numberOfPlants = numPlants;
    }

    void setPlantingDate(time_t newDate)
    {
        this->plantingDate = newDate;
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

    time_t getPlantingDate() const
    {
        return this->plantingDate;
    }

    string formatDate(time_t time) const
    {
        tm *tm = localtime(&time);
        char buffer[11];
        strftime(buffer, sizeof(buffer), "%d/%m/%Y", tm);
        return buffer;
    }

    int daysSincePlanting() const
    {
        time_t now = time(nullptr);
        double diff = difftime(now, plantingDate) / (60 * 60 * 24);
        return static_cast<int>(diff);
    }

private:
    string name;
    int numberOfPlants;
    time_t plantingDate;
};

class Tree : public Plant
{
public:
    static int totalTrees;

    Tree(string name = "", int numberOfPlants = 0, time_t plantingDate = time(nullptr))
        : Plant(name, numberOfPlants, plantingDate)
    {
        totalTrees++;
    }

    void display() const
    {
        cout << "Tree: " << this->getName() << ", Number of trees: " << this->getNumberOfPlants()
             << ", Planted on: " << this->formatDate(this->getPlantingDate())
             << ", Days since planting: " << this->daysSincePlanting() << endl;
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

    Flower(string name = "", int numberOfPlants = 0, time_t plantingDate = time(nullptr))
        : Plant(name, numberOfPlants, plantingDate)
    {
        totalFlowers++;
    }

    void display() const
    {
        cout << "Flower: " << this->getName() << ", Number of flowers: " << this->getNumberOfPlants()
             << ", Planted on: " << this->formatDate(this->getPlantingDate())
             << ", Days since planting: " << this->daysSincePlanting() << endl;
    }

    static void displayTotalFlowers()
    {
        cout << "Total number of flowers: " << totalFlowers << endl;
    }
};

int Flower::totalFlowers = 0;

time_t parseDate(const string &dateStr)
{
    tm tm = {};
    istringstream ss(dateStr);
    ss >> get_time(&tm, "%d/%m/%Y");
    return mktime(&tm);
}

int main()
{
    int numTrees, numFlowers;

    cout << "Enter the number of trees: ";
    cin >> numTrees;

    cout << "Enter the number of flowers: ";
    cin >> numFlowers;

    Tree **trees = new Tree *[numTrees];
    Flower **flowers = new Flower *[numFlowers];

    cin.ignore();

    for (int i = 0; i < numTrees; ++i)
    {
        trees[i] = new Tree;
        string name;
        int numberOfPlants;
        string plantingDateStr;

        cout << "Enter name for tree " << i + 1 << ": ";
        getline(cin, name);
        cout << "Enter number of trees for " << name << ": ";
        cin >> numberOfPlants;
        cin.ignore();

        cout << "Enter planting date (DD/MM/YYYY) for " << name << ": ";
        getline(cin, plantingDateStr);
        time_t plantingDate = parseDate(plantingDateStr);

        trees[i]->setName(name);
        trees[i]->setNumberOfPlants(numberOfPlants);
        trees[i]->setPlantingDate(plantingDate);
    }

    for (int i = 0; i < numFlowers; ++i)
    {
        flowers[i] = new Flower;
        string name;
        int numberOfPlants;
        string plantingDateStr;

        cout << "Enter name for flower " << i + 1 << ": ";
        getline(cin, name);
        cout << "Enter number of flowers for " << name << ": ";
        cin >> numberOfPlants;
        cin.ignore();

        cout << "Enter planting date (DD/MM/YYYY) for " << name << ": ";
        getline(cin, plantingDateStr);
        time_t plantingDate = parseDate(plantingDateStr);

        flowers[i]->setName(name);
        flowers[i]->setNumberOfPlants(numberOfPlants);
        flowers[i]->setPlantingDate(plantingDate);
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
