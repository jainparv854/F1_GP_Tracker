#ifndef Driver_H
#define Driver_H
#include <string>
#include <iostream>
class Driver
{
private:
    std::string name;
    int points;
    bool isChampion;

public:
    Driver(std::string n, int p, bool isC) : name(n), points(p), isChampion(isC) {}
    void display()
    {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Points: " << points << std::endl;
        std::cout << "Champion: " << (isChampion ? "Yes" : "No") << std::endl;
    }
    std::string getName()
    {
        return name;
    }
    int getPoints()
    {
        return points;
    }
};
#endif