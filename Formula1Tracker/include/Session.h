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
};
#endif