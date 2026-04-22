#ifndef Driver_H
#define Driver_H
#include <string>
#include <iostream>
class Driver{
private:
    std::string name;
    int points;
    bool isChampion;
public:
    Driver(std::string n, int p, bool isC) : name(n), points(p), isChampion(isC) {}
    void display() const{
        std::cout  << name << " \t\t\t" << points << std::endl;
        if(isChampion){
            std::cout << "World Champion" << std::endl;
        }
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