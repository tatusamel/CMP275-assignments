#ifndef OPTIMIZED_COLLISION_DATASET_HPP
#define OPTIMIZED_COLLISION_DATASET_HPP

#include <vector>
#include <string>
#include <memory>

class OptimizedCollisionDataset {
public:
    // Structure of Arrays (SoA) design
    std::vector<std::string> crashDates;
    std::vector<std::string> crashTimes;
    std::vector<std::string> boroughs;
    std::vector<std::string> zipCodes;
    std::vector<double> latitudes;
    std::vector<double> longitudes;
    std::vector<std::string> locations;
    std::vector<std::string> onStreetNames;
    std::vector<std::string> crossStreetNames;
    std::vector<std::string> offStreetNames;

    // Numeric data grouped together for better vectorization
    std::vector<int> personsInjured;
    std::vector<int> personsKilled;
    std::vector<int> pedestriansInjured;
    std::vector<int> pedestriansKilled;
    std::vector<int> cyclistsInjured;
    std::vector<int> cyclistsKilled;
    std::vector<int> motoristsInjured;
    std::vector<int> motoristsKilled;

    std::vector<std::string> contributingFactorVehicle1;
    std::vector<std::string> contributingFactorVehicle2;
    std::vector<std::string> contributingFactorVehicle3;
    std::vector<std::string> contributingFactorVehicle4;
    std::vector<std::string> contributingFactorVehicle5;

    std::vector<long> collisionIDs;

    std::vector<std::string> vehicleTypeCode1;
    std::vector<std::string> vehicleTypeCode2;
    std::vector<std::string> vehicleTypeCode3;
    std::vector<std::string> vehicleTypeCode4;
    std::vector<std::string> vehicleTypeCode5;

    // Optimized search methods
    std::vector<size_t> searchByDateRange(const std::string& startDate, const std::string& endDate) const;
    std::vector<size_t> searchByBorough(const std::string& borough) const;
    std::vector<size_t> searchByInjuryThreshold(int minInjuries) const;
    
    bool loadFromCSV(const std::string& filename);
    size_t size() const { return crashDates.size(); }

private:
    void reserveSpace(size_t capacity);
};

#endif // OPTIMIZED_COLLISION_DATASET_HPP