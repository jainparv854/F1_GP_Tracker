#ifndef GRANDPRIX_H
#define GRANDPRIX_H
#include "Session.h"
#include <iostream>
#include <vector>
#include <string>
class GrandPrix{
    private:
        std::string gpName;
        std::string trackName;
        std::vector <Session> sessions;
        bool isCancelled{false};
    public:
        GrandPrix(std::string name, std::string track) : gpName(name), trackName(track) {}
        void addSession(Session s){
            sessions.push_back(s);
    }
        void displayRaceWeekendInfo() const{
            if(isCancelled){
                std::cout << "The Grand Prix " << gpName << " at " << trackName << " has been cancelled." << std::endl;
                return;
            }else{
                std::cout << "Grand Prix: " << gpName << std::endl;
                std::cout << "Track: " << trackName << std::endl;
                std::cout << "Sessions: " << std::endl;
                for(const auto& session : sessions){
                    std::cout << "  - " << session.sessionType << " on " << session.dateTime << std::endl;
                }
            }
        }
};
#endif