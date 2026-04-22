#ifndef SESSION_H
#define SESSION_H
#include <iostream>
#include <string>
class Session{
    private:
        std::string sessionType;
        std::string dateTime;
    public:
        friend class GrandPrix;
        Session(std::string type, std::string dt) : sessionType(type), dateTime(dt) {}

        std::string toIst(std::string utc){
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
};
#endif