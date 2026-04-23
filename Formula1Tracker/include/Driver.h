#ifndef Driver_H
#define Driver_H
#include <string>
#include <iostream>
class Driver{
private:
    std::string name;
    std::string teamName;
    float points;
    bool isChampion;
public:
    Driver(std::string n, std::string t, float p, bool isC) : name(n), teamName(t), points(p), isChampion(isC) {}
    void display() const{
        std::cout  << name << " \t\t\t" << teamName << " \t\t\t" << points << std::endl;
        if(isChampion){
            std::cout << "World Champion" << std::endl;
        }
    }
    std::string getName() const{
        return name;
    }
    std::string getTeamName() const{
        return teamName;
    }

    float getPoints() const{
        return points;
    }

    bool operator>(const Driver& other) const{
        return this->points > other.points;
    }
    
};
inline void to_json(nlohmann::json& j, const Driver& d) {
    j = nlohmann::json{{"name", d.getName()}, {"teamName", d.getTeamName()}, {"points", d.getPoints()}};
}
#endif
