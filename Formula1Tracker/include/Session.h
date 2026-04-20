#ifndef SESSION_H
#define SESSION_H
#include <iostream>
#include <string>
class Session{
    private:
        std::string sessionType;
        std::string dateTime;
        bool isPointAwarded;
    public:
        Session(std::string type, std::string dt, bool points) : sessionType(type), dateTime(dt), isPointAwarded(points) {}
        void displaySessionInfo(){
            std::cout << "Session Type: " << sessionType << std::endl;
            std::cout << "Date & Time: " << dateTime << std::endl;
            std::cout << "Points Awarded: " << (isPointAwarded ? "Yes" : "No") << std::endl;
        }
};
#endif