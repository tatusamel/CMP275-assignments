#ifndef COLLISION_DATASET_PARALLEL_ARRAYS_HPP
#define COLLISION_DATASET_PARALLEL_ARRAYS_HPP

#include <string>
#include <vector>
#include "CollisionRecord.hpp"

class CollisionDatasetParallelArrays {
public:
    bool loadFromCSV(const std::string &filename);

    std::vector<CollisionRecord> searchByDateRange(const std::string &startDate, const std::string &endDate) const;
    std::vector<CollisionRecord> searchByBorough(const std::string &borough) const;
    std::vector<CollisionRecord> searchByZipCode(const int &zipCode) const;
    std::vector<CollisionRecord> searchByInjuryThreshold(int minInjuries) const;
    std::vector<CollisionRecord> searchByLocationBounds(double minLat, double maxLat,
                                                        double minLong, double maxLong) const;
    // Optional: Return full records vector (reconstructed from arrays)
    std::vector<CollisionRecord> getRecords() const;
    // Object-of-arrays: one vector per field.
    std::vector<std::time_t> crashDates;
    std::vector<std::string> crashTimes;
    std::vector<std::string> boroughs;
    std::vector<int> zipCodes;
    std::vector<double> latitudes;
    std::vector<double> longitudes;
    std::vector<std::string> locations;
    std::vector<std::string> onStreetNames;
    std::vector<std::string> crossStreetNames;
    std::vector<std::string> offStreetNames;
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
private:
};

#endif // COLLISION_DATASET_PARALLEL_ARRAYS_HPP
