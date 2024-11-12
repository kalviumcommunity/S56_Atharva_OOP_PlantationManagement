#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

class DateUtility
{
public:
    static string formatDate(time_t time)
    {
        tm *tm = localtime(&time);
        char buffer[11];
        strftime(buffer, sizeof(buffer), "%d/%m/%Y", tm);
        return buffer;
    }

    static int daysSince(time_t date)
    {
        time_t now = time(nullptr);
        double diff = difftime(now, date) / (60 * 60 * 24);
        return static_cast<int>(diff);
    }

    static time_t parseDate(const string &dateStr)
    {
        tm tm = {};
        istringstream ss(dateStr);
        ss >> get_time(&tm, "%d/%m/%Y");
        return mktime(&tm);
    }
};

class PlantCounter
{
public:
    static int totalTrees;
    static int totalFlowers;

    static void addTrees(int count) { totalTrees += count; }
    static void addFlowers(int count) { totalFlowers += count; }

    static void displayTotalCounts()
    {
        cout << "Total number of trees: " << totalTrees << endl;
        cout << "Total number of flowers: " << totalFlowers << endl;
    }
};

int PlantCounter::totalTrees = 0;
int PlantCounter::totalFlowers = 0;

class Plant
{
public:
    Plant(string name = "", int numberOfPlants = 0, time_t plantingDate = time(nullptr))
        : name(name), numberOfPlants(numberOfPlants), plantingDate(plantingDate) {}

    virtual ~Plant() {}

    virtual void display() const = 0;

    void setName(string newName) { this->name = newName; }
    void setNumberOfPlants(int numPlants) { this->numberOfPlants = numPlants; }
    void setPlantingDate(time_t newDate) { this->plantingDate = newDate; }

    string getName() const { return this->name; }
    int getNumberOfPlants() const { return this->numberOfPlants; }

protected:
    time_t getPlantingDate() const { return this->plantingDate; }

private:
    string name;
    int numberOfPlants;
    time_t plantingDate;
};

class Tree : public Plant
{
public:
    Tree(string name, int numberOfPlants, time_t plantingDate)
        : Plant(name, numberOfPlants, plantingDate)
    {
        PlantCounter::addTrees(numberOfPlants);
    }

    void display() const override
    {
        cout << "Tree: " << getName() << ", Number of trees: " << getNumberOfPlants()
             << ", Planted on: " << DateUtility::formatDate(getPlantingDate())
             << ", Days since planting: " << DateUtility::daysSince(getPlantingDate()) << endl;
    }
};

class FruitTree : public Tree
{
public:
    FruitTree(string name, int numberOfPlants, time_t plantingDate)
        : Tree(name, numberOfPlants, plantingDate) {}

    void display() const override
    {
        cout << "Fruit Tree: " << getName() << ", Number of trees: " << getNumberOfPlants()
             << ", Planted on: " << DateUtility::formatDate(getPlantingDate())
             << ", Days since planting: " << DateUtility::daysSince(getPlantingDate()) << endl;
    }
};

class Flower : public Plant
{
public:
    Flower(string name, int numberOfPlants, time_t plantingDate)
        : Plant(name, numberOfPlants, plantingDate)
    {
        PlantCounter::addFlowers(numberOfPlants);
    }

    void display() const override
    {
        cout << "Flower: " << getName() << ", Number of flowers: " << getNumberOfPlants()
             << ", Planted on: " << DateUtility::formatDate(getPlantingDate())
             << ", Days since planting: " << DateUtility::daysSince(getPlantingDate()) << endl;
    }
};

// Factory class to create plants
class PlantFactory
{
public:
    static Plant *createPlant(char type, const string &name, int numberOfPlants, const string &plantingDateStr)
    {
        time_t plantingDate = DateUtility::parseDate(plantingDateStr);

        if (type == 't' || type == 'T')
        {
            char isFruitTree;
            cout << "Is it a fruit tree (y/n)? ";
            cin >> isFruitTree;
            cin.ignore();

            if (isFruitTree == 'y' || isFruitTree == 'Y')
                return new FruitTree(name, numberOfPlants, plantingDate);
            else
                return new Tree(name, numberOfPlants, plantingDate);
        }
        else if (type == 'f' || type == 'F')
        {
            return new Flower(name, numberOfPlants, plantingDate);
        }
        else
        {
            cout << "Invalid plant type." << endl;
            return nullptr;
        }
    }
};

void addPlant(vector<Plant *> &plants)
{
    string name, plantingDateStr;
    int numberOfPlants;
    char type;

    cout << "Enter type of plant (t for Tree, f for Flower): ";
    cin >> type;
    cin.ignore();

    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter number of plants: ";
    cin >> numberOfPlants;
    cin.ignore();

    cout << "Enter planting date (DD/MM/YYYY): ";
    getline(cin, plantingDateStr);

    Plant *newPlant = PlantFactory::createPlant(type, name, numberOfPlants, plantingDateStr);
    if (newPlant != nullptr)
    {
        plants.push_back(newPlant);
    }
}

void displayAllPlants(const vector<Plant *> &plants)
{
    for (const auto &plant : plants)
    {
        plant->display();
    }
}

void displayTotalPlants()
{
    PlantCounter::displayTotalCounts();
}

Plant *findPlantByName(const vector<Plant *> &plants, const string &name)
{
    for (const auto &plant : plants)
    {
        if (plant->getName() == name)
            return plant;
    }
    return nullptr;
}

int main()
{
    vector<Plant *> plants;
    int choice;

    while (true)
    {
        cout << "\nPlantation Management System" << endl;
        cout << "1. Add a new plant" << endl;
        cout << "2. Display all plants" << endl;
        cout << "3. Count total plants" << endl;
        cout << "4. Search plant by name" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        cin.ignore();

        switch (choice)
        {
        case 1:
            addPlant(plants);
            break;
        case 2:
            displayAllPlants(plants);
            break;
        case 3:
            displayTotalPlants();
            break;
        case 4:
        {
            string name;
            cout << "Enter the name of the plant to search: ";
            getline(cin, name);
            Plant *plant = findPlantByName(plants, name);
            if (plant)
                plant->display();
            else
                cout << "Plant not found." << endl;
            break;
        }
        case 5:
            for (auto plant : plants)
                delete plant;
            plants.clear();
            cout << "Exiting the system. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}
