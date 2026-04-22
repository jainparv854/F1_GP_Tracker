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

void applyRaceResults(vector<Driver>& grid){
    int pointsDistribution[] = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};
    for(int i = 0; i < 10 && i < grid.size(); i++){
        grid[i] = grid[i] + pointsDistribution[i];
    }
}

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
    std::cout << "Name \t\t\tPoints" << std::endl;
    showDriverStandings(seasonStandings);
    return 0;
}
