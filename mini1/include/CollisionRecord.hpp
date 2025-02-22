#ifndef COLLISION_RECORD_HPP
#define COLLISION_RECORD_HPP

#include <string>
#include <chrono>
#include <sstream>

class CollisionRecord {
public:
    std::time_t crashDate;
    std::string crashTime;
    std::string borough;
    int zipCode;
    double latitude;
    double longitude;
    std::string location;
    std::string onStreetName;
    std::string crossStreetName;
    std::string offStreetName;

    int personsInjured;
    int personsKilled;
    int pedestriansInjured;
    int pedestriansKilled;
    int cyclistsInjured;
    int cyclistsKilled;
    int motoristsInjured;
    int motoristsKilled;

    std::string contributingFactorVehicle1;
    std::string contributingFactorVehicle2;
    std::string contributingFactorVehicle3;
    std::string contributingFactorVehicle4;
    std::string contributingFactorVehicle5;

    long collisionID;

    std::string vehicleTypeCode1;
    std::string vehicleTypeCode2;
    std::string vehicleTypeCode3;
    std::string vehicleTypeCode4;
    std::string vehicleTypeCode5;

    static std::time_t convertToTimestamp(const std::string& dateStr) {
        std::tm tm = {};
        std::istringstream ss(dateStr);
        strptime(dateStr.c_str(), "%m/%d/%Y", &tm);
        return std::mktime(&tm);
    }
    
};

#endif // COLLISION_RECORD_HPP