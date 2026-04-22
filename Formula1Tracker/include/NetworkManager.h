#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <vector>
#include <iostream>
#include "Driver.h"
#include "Session.h"

using json = nlohmann::json;

class networkManager{
    public:
        static std::string toIst(std::string utc){
            int hours = std::stoi(utc.substr(0, 2));
            int minutes = std::stoi(utc.substr(3, 2));
            minutes += 30;
            if(minutes >= 60){
                hours += 1;
                minutes -= 60;
            }
            hours += 5;
            if(hours >= 24){
                hours -= 24;
            }
            std::string hStr = (hours < 10) ? "0" + std::to_string(hours) : std::to_string(hours);
            std::string mStr = (minutes < 10) ? "0" + std::to_string(minutes) : std::to_string(minutes);
            return hStr + ":" + mStr;
        }
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

    static void fetchSchedule(std::vector<GrandPrix>& calendar){
        cpr::Response r = cpr::Get(cpr::Url{"https://api.jolpi.ca/ergast/f1/current.json"},
            cpr::Header{{"User-Agent", "F1TrackerProject/1.0"}});

        if(r.status_code == 200){
            auto data = json::parse(r.text);
            auto list = data["MRData"]["RaceTable"]["Races"];

            calendar.clear();
            for(auto& item : list){
                std::string gpName = item["raceName"];
                std::string trackName = item["Circuit"]["circuitName"];
                GrandPrix gp(gpName, trackName);

                std::string date = item["date"];
                std::string time = item["time"];
                std::string istTime = toIst(time);
                gp.addSession(Session("Race", date + " " + istTime + " IST"));
                if(item.contains("FirstPractice")){
                    std::string fpDate = item["FirstPractice"]["date"];
                    std::string fpTime = item["FirstPractice"]["time"];
                    std::string istFpTime = toIst(fpTime);
                    gp.addSession(Session("FP1", fpDate + " " + istFpTime + " IST"));
                }
                if(item.contains("SecondPractice")){
                    std::string fpDate = item["SecondPractice"]["date"];
                    std::string fpTime = item["SecondPractice"]["time"];
                    std::string istFpTime = toIst(fpTime);
                    gp.addSession(Session("FP2", fpDate + " " + istFpTime + " IST"));
                }
                if(item.contains("ThirdPractice")){
                    std::string fpDate = item["ThirdPractice"]["date"];
                    std::string fpTime = item["ThirdPractice"]["time"];
                    std::string istFpTime = toIst(fpTime);
                    gp.addSession(Session("FP3", fpDate + " " + istFpTime + " IST"));
                }
                if(item.contains("Qualifying")){
                    std::string qDate = item["Qualifying"]["date"];
                    std::string qTime = item["Qualifying"]["time"];
                    std::string istQTime = toIst(qTime);
                    gp.addSession(Session("Qualifying", qDate + " " + istQTime + " IST"));
                }
                if(item.contains("Sprint")){
                    std::string sDate = item["Sprint"]["date"];
                    std::string sTime = item["Sprint"]["time"];
                    std::string istSTime = toIst(sTime);
                    gp.addSession(Session("Sprint", sDate + " " + istSTime + " IST"));
                }
                if(item.contains("SprintQualifying")){
                    std::string sqDate = item["SprintQualifying"]["date"];
                    std::string sqTime = item["SprintQualifying"]["time"];
                    std::string istSqTime = toIst(sqTime);
                    gp.addSession(Session("Sprint Qualifying", sqDate + " " + istSqTime + " IST"));
                }
                calendar.push_back(gp);
            }
            std::cout << "SCHEDULE SYNCED! 📅" << std::endl;
        }
    }
};