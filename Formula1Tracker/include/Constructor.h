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
    
    friend void to_json(nlohmann::json& j, const Constructor& c);

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
inline void to_json(nlohmann::json& j, const Constructor& c){
    j = nlohmann::json{
        {"name", c.name},
        {"totalPoints", c.totalPoints},
        {"drivers", {c.drivers[0], c.drivers[1]}}
    };
}
#endif