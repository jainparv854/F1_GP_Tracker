#include "../include/json.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#ifndef Driver_H
#define Driver_H
class Driver {
public:
    string name;
    int points;
    bool isChampion;

    Driver(string name, int points, bool isChampion) {
        this->name = name;
        this->points = points;
        this->isChampion = isChampion;
    }
    void display() {
        cout << "Name: " << name << endl;
        cout << "Points: " << points << endl;
        cout << "Champion: " << (isChampion ? "Yes" : "No") << endl;
    }
};
int main(){
    Driver d1("Max Verstappen", 395, true);
    Driver d2("Charles Leclerc", 300, false);
    d1.display();
    d2.display();
    return 0;
}
#endif