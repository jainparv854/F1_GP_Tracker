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
    void display(){
        std::cout << "Name: " << name << std::endl;
        std::cout << "Points: " << points << std::endl;
        if(isChampion){
            std::cout << "Status: World Champion" << std::endl;
        }
    }
    std::string getName(){
        return name;
    }

    int getPoints(){
        return points;
    }

    Driver& operator+(int pointsEarned){
        this->points += pointsEarned;
        return *this;
    }
    
    bool operator>(const Driver& other){
        return this->points > other.points;
    }
};
#endif