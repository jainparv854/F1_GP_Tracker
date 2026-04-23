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
        friend void to_json(nlohmann::json& j, const Session& s);
        Session(std::string type, std::string dt) : sessionType(type), dateTime(dt) {}
};
inline void to_json(nlohmann::json& j, const Session& s){
    j = nlohmann::json{
        {"type", s.sessionType},
        {"dateTime", s.dateTime}
    };
}
#endif