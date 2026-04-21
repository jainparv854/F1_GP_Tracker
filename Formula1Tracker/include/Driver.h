#ifndef Driver_H
#define Driver_H
#include <string>
#include <iostream>
class Driver{
private:
    std::string name;
    int points;
public:
    Driver(std::string n, int p) : name(n), points(p) {}
    void display() const{
        std::cout << "Name: " << name << "\t\t" << points << std::endl;
    }
    std::string getName() const{
        return name;
    }

    int getPoints() const{
        return points;
    }

    Driver& operator+(int pointsEarned){
        this->points += pointsEarned;
        return *this;
    }

    bool operator>(const Driver& other) const{
        return this->points > other.points;
    }
};
#endif