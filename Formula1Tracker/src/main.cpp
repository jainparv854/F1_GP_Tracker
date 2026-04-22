#include "../include/json.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "../include/Driver.h"
#include "../include/Constructor.h"
#include "../include/Session.h"
#include "../include/GrandPrix.h"
#include "../include/NetworkManager.h"
using namespace std;
using json = nlohmann::json;

void showDriverStandings(vector<Driver>& drivers){
    sort(drivers.begin(), drivers.end(), greater<Driver>());
    for(const auto& d : drivers){
        d.display();
    }
}

void showConstructorStandings(vector<Constructor>& constructors){
    sort(constructors.begin(), constructors.end(), greater<Constructor>());
    for(auto& c : constructors){
        c.display();
    }
}

int main(){
    vector<Driver> seasonStandings;
    networkManager::fetchLiveStandings(seasonStandings);
    std::cout << "Name \t\t\tConstructor \t\t\tPoints" << std::endl;
    showDriverStandings(seasonStandings);

    vector<Constructor> constructorStandings;
    networkManager::fetchConstructorStandings(constructorStandings, seasonStandings);
    cout << "Constructor \t\t\tPoints \t\t\tDrivers" << endl;
    showConstructorStandings(constructorStandings);
    return 0;
}
