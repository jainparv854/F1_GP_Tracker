#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <iostream>
#include "Driver.h"

using json = nlohmann::json;

class networkManager{
    public:
        static void fetchLiveStandings(std::vector<Driver>& standings){
            cpr::Response r = cpr::Get(cpr::Url{"http://ergast.com/api/f1/current/driverStandings.json"});
            if(r.status_code == 200){
                auto data = json::parse(r.text);
                auto list = data["MRData"]["StandingsTable"]["StandingsLists"][0]["DriverStandings"];
                standings.clear();
                for(const auto& item : list){
                    std::string name = item["Driver"]["givenName"].get<std::string>() + " " + item["Driver"]["familyName"].get<std::string>();
                    int points = std::stoi(item["points"].get<std::string>());
                    standings.push_back(Driver(name, points));
                }
                std::cout << "Live Standings Synced! 🛰️" << std::endl;
            }else{
                std::cerr << "Failed to fetch live standings. Status code: " << r.status_code << " 💀" << std::endl;
            }
        }
};