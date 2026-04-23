#include "../include/json.hpp"
#include <iostream>
#include <iomanip>
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

void saveFrontendData(const vector<Driver>& d, const vector<Constructor>& c, const vector<GrandPrix>& gp){
    json j;
    j["standings"] = d;
    j["teams"] = c;
    j["schedule"] = gp;
    ofstream o("data.json");
    if(!o){
        cerr << "[ERROR] Could not create data.json" << endl; 
        return;
    }
    o << setw(4) << j << endl;
    o.close();
    cout << "[SUCCESS] data.json created at: " << std::filesystem::current_path() << endl;
}
int main(){
    vector<Driver> seasonStandings;
    vector<Constructor> constructorStandings;
    vector<GrandPrix> seasonSchedule;

    cout << "[System] Initializing Data Stream... " << endl;
    networkManager::fetchLiveStandings(seasonStandings);
    networkManager::fetchConstructorStandings(constructorStandings, seasonStandings);
    networkManager::fetchSchedule(seasonSchedule);

    cout << "Name \t\t\t Constructor \t\t Points" << endl;
    showDriverStandings(seasonStandings);

    saveFrontendData(seasonStandings, constructorStandings, seasonSchedule);
    cout << "\n[SUCCESS] Open index.html to view telemetry data! 🏎️" << endl;
    return 0;
}
