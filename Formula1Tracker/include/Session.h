#ifndef SESSION_H
#define SESSION_H
#include <iostream>
#include <string>
class Session{
    private:
        std::string sessionType;
        std::string dateTime;
        std::string sessionResult;
    public:
        friend class GrandPrix;
        Session(std::string type, std::string dt, std::string r) : sessionType(type), dateTime(dt), sessionResult(r) {}
};
#endif