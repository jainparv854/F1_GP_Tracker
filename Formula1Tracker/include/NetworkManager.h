#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <iostream>
#include "Driver.h"

using json = nlohmann::json;

class networkManager{
    public:
        static void fetchLiveStandings(std::vector<Driver>& standings) {

        cpr::Response r = cpr::Get(
            cpr::Url{"https://api.jolpi.ca/ergast/f1/current/driverStandings.json"},
            cpr::Header{{"User-Agent", "F1TrackerProject/1.0"}}
        );

        if (r.status_code == 200) {
            try {
                auto data = json::parse(r.text);
                auto list = data["MRData"]["StandingsTable"]["StandingsLists"][0]["DriverStandings"];
                
                standings.clear();
                for (auto& item : list) {
                    std::string name = item["Driver"]["familyName"].get<std::string>();
                    std::string team = item["Constructors"][0]["name"].get<std::string>();
                    float points = std::stof(item["points"].get<std::string>());
                    standings.push_back(Driver(name, team, points, false));
                }
                std::cout << "LIVE STANDINGS SYNCED! 🏁" << std::endl;
            } catch (...) {
                std::cerr << "JSON Parsing Failed! 🧩" << std::endl;
            }
        } else {
            std::cerr << "API Error: " << r.status_code << " 💀" << std::endl;
        }
    }

    static void fetchConstructorStandings(std::vector<Constructor>& constructors, const std::vector<Driver>& drivers) {
        cpr::Response r = cpr::Get(cpr::Url{"https://api.jolpi.ca/ergast/f1/current/constructorStandings.json"},
            cpr::Header{{"User-Agent", "F1TrackerProject/1.0"}}
        );
        
        if (r.status_code == 200) {
            auto data = json::parse(r.text);
            auto list = data["MRData"]["StandingsTable"]["StandingsLists"][0]["ConstructorStandings"];
            
            constructors.clear();
            for (auto& item : list) {
                std::string name = item["Constructor"]["name"];
                float points = static_cast<float>(std::stof(item["points"].get<std::string>()));

                std::vector<Driver> teamDrivers;
                for (const auto& d : drivers) {
                    if (d.getTeamName() == name) {
                        teamDrivers.push_back(d);
                    }
                }
                constructors.push_back(Constructor(name, teamDrivers[0], teamDrivers[1], static_cast<float>(points)));
            }
            std::cout << "CONSTRUCTOR STANDINGS SYNCED! 🏎️" << std::endl;
        }
    }
};