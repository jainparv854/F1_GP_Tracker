#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H
#include <string>
#include <iostream>
#include "Driver.h"
class Constructor{
private:

    std::string name;
    Driver drivers[2];
    float totalPoints;

    public:
    Constructor(std::string n, const Driver& d1, const Driver& d2, float p) : name(n), drivers{d1, d2}, totalPoints(p) {}
    

    void display() {
        std::cout << name << std::endl;
        std::cout << totalPoints << std::endl;
        std::cout << std::endl;
        drivers[0].display();
        drivers[1].display();
    }

    bool operator>(const Constructor& other) const{
        return this->totalPoints > other.totalPoints;
    }
};
#endif