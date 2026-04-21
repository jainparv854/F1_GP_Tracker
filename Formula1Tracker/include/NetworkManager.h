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
                    int points = std::stoi(item["points"].get<std::string>());
                    standings.push_back(Driver(name, points, false));
                }
                std::cout << "LIVE STANDINGS SYNCED! 🏁" << std::endl;
            } catch (...) {
                std::cerr << "JSON Parsing Failed! 🧩" << std::endl;
            }
        } else {
            std::cerr << "API Error: " << r.status_code << " 💀" << std::endl;
        }
    }
};