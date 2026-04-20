#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H
#include <string>
#include <iostream>
#include "Driver.h"
class Constructor{
private:
    std::string name;
    Driver drivers[2];
    int totalPoints{0};
    public:
    Constructor(std::string n, Driver d1, Driver d2) : name(n), drivers{d1, d2} {}
    void calculateTotalPoints() {
        totalPoints = drivers[0].getPoints() + drivers[1].getPoints();
    }
    void display() {
        std::cout << "Constructor: " << name << std::endl;
        std::cout << "Total Points: " << totalPoints << std::endl;
        std::cout << "Drivers: " << std::endl;
        drivers[0].display();
        drivers[1].display();
    }
};
#endif