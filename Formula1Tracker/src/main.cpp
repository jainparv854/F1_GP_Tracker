#include "../include/json.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "../include/Driver.h"
#include "../include/Constructor.h"
#include "../include/Session.h"
#include "../include/GrandPrix.h"
using namespace std;
using json = nlohmann::json;
int main(){
    GrandPrix miami("Miami Grand Prix", "Miami International Autodrome");
    Session practice("Practice", "2026-05-03 10:00", "Verstappen fastest, Leclerc 2nd");
    miami.addSession(practice);
    miami.displayRaceWeekendInfo();
    Driver d1("Max Verstappen", 395, true);
    Driver d2("Charles Leclerc", 300, false);
    Constructor Ferrari("Scuderia Ferrari", d1, d2);
    Ferrari.calculateTotalPoints();
    Ferrari.display();
    return 0;
}
