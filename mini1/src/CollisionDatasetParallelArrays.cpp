#include "CollisionDatasetParallelArrays.hpp"
#include "CSVParser.hpp"
#include "CollisionRecord.hpp"
#include <fstream>
#include <iostream>
#include <omp.h>

bool CollisionDatasetParallelArrays::loadFromCSV(const std::string &filename) {
    CSVParser parser(filename);
    if (!parser.parseParallelArrays(*this)) {
        std::cerr << "Failed to parse file into parallel arrays.\n";
        return false;
    }
    return true;
}

std::vector<CollisionRecord> CollisionDatasetParallelArrays::getRecords() const {
    std::vector<CollisionRecord> res;
    size_t n = crashDates.size();
    res.resize(n);
    #pragma omp parallel for schedule(dynamic)
    for (size_t i = 0; i < n; i++) {
        CollisionRecord r;
        r.crashDate = crashDates[i];
        r.crashTime = crashTimes[i];
        r.borough = boroughs[i];
        r.zipCode = zipCodes[i];
        r.latitude = latitudes[i];
        r.longitude = longitudes[i];
        r.location = locations[i];
        r.onStreetName = onStreetNames[i];
        r.crossStreetName = crossStreetNames[i];
        r.offStreetName = offStreetNames[i];
        r.personsInjured = personsInjured[i];
        r.personsKilled = personsKilled[i];
        r.pedestriansInjured = pedestriansInjured[i];
        r.pedestriansKilled = pedestriansKilled[i];
        r.cyclistsInjured = cyclistsInjured[i];
        r.cyclistsKilled = cyclistsKilled[i];
        r.motoristsInjured = motoristsInjured[i];
        r.motoristsKilled = motoristsKilled[i];
        r.contributingFactorVehicle1 = contributingFactorVehicle1[i];
        r.contributingFactorVehicle2 = contributingFactorVehicle2[i];
        r.contributingFactorVehicle3 = contributingFactorVehicle3[i];
        r.contributingFactorVehicle4 = contributingFactorVehicle4[i];
        r.contributingFactorVehicle5 = contributingFactorVehicle5[i];
        r.collisionID = collisionIDs[i];
        r.vehicleTypeCode1 = vehicleTypeCode1[i];
        r.vehicleTypeCode2 = vehicleTypeCode2[i];
        r.vehicleTypeCode3 = vehicleTypeCode3[i];
        r.vehicleTypeCode4 = vehicleTypeCode4[i];
        r.vehicleTypeCode5 = vehicleTypeCode5[i];
        res[i] = r;
    }
    return res;
}

std::vector<CollisionRecord> CollisionDatasetParallelArrays::searchByDateRange(const std::string &startDate,
                                                                               const std::string &endDate) const {
    
    std::time_t startTimestamp = CollisionRecord::convertToTimestamp(startDate);
    std::time_t endTimestamp = CollisionRecord::convertToTimestamp(endDate);
    
    std::vector<CollisionRecord> result;
    size_t n = crashDates.size();
    #pragma omp parallel
    {
        std::vector<CollisionRecord> local;
        #pragma omp for nowait schedule(dynamic)
        for (size_t i = 0; i < n; i++) {
            if (crashDates[i] >= startTimestamp && crashDates[i] <= endTimestamp) {
                CollisionRecord r;
                r.crashDate = crashDates[i];
                r.crashTime = crashTimes[i];
                r.borough = boroughs[i];
                r.zipCode = zipCodes[i];
                r.latitude = latitudes[i];
                r.longitude = longitudes[i];
                r.location = locations[i];
                r.onStreetName = onStreetNames[i];
                r.crossStreetName = crossStreetNames[i];
                r.offStreetName = offStreetNames[i];
                r.personsInjured = personsInjured[i];
                r.personsKilled = personsKilled[i];
                r.pedestriansInjured = pedestriansInjured[i];
                r.pedestriansKilled = pedestriansKilled[i];
                r.cyclistsInjured = cyclistsInjured[i];
                r.cyclistsKilled = cyclistsKilled[i];
                r.motoristsInjured = motoristsInjured[i];
                r.motoristsKilled = motoristsKilled[i];
                r.contributingFactorVehicle1 = contributingFactorVehicle1[i];
                r.contributingFactorVehicle2 = contributingFactorVehicle2[i];
                r.contributingFactorVehicle3 = contributingFactorVehicle3[i];
                r.contributingFactorVehicle4 = contributingFactorVehicle4[i];
                r.contributingFactorVehicle5 = contributingFactorVehicle5[i];
                r.collisionID = collisionIDs[i];
                r.vehicleTypeCode1 = vehicleTypeCode1[i];
                r.vehicleTypeCode2 = vehicleTypeCode2[i];
                r.vehicleTypeCode3 = vehicleTypeCode3[i];
                r.vehicleTypeCode4 = vehicleTypeCode4[i];
                r.vehicleTypeCode5 = vehicleTypeCode5[i];
                local.push_back(r);
            }
        }
        #pragma omp critical
        result.insert(result.end(), local.begin(), local.end());
    }
    return result;
}

std::vector<CollisionRecord> CollisionDatasetParallelArrays::searchByBorough(const std::string &borough) const {
    std::vector<CollisionRecord> result;
    size_t n = boroughs.size();
    #pragma omp parallel
    {
        std::vector<CollisionRecord> local;
        #pragma omp for nowait schedule(dynamic)
        for (size_t i = 0; i < n; i++) {
            if (boroughs[i] == borough) {
                CollisionRecord r;
                r.crashDate = crashDates[i];
                r.crashTime = crashTimes[i];
                r.borough = boroughs[i];
                r.zipCode = zipCodes[i];
                r.latitude = latitudes[i];
                r.longitude = longitudes[i];
                r.location = locations[i];
                r.onStreetName = onStreetNames[i];
                r.crossStreetName = crossStreetNames[i];
                r.offStreetName = offStreetNames[i];
                r.personsInjured = personsInjured[i];
                r.personsKilled = personsKilled[i];
                r.pedestriansInjured = pedestriansInjured[i];
                r.pedestriansKilled = pedestriansKilled[i];
                r.cyclistsInjured = cyclistsInjured[i];
                r.cyclistsKilled = cyclistsKilled[i];
                r.motoristsInjured = motoristsInjured[i];
                r.motoristsKilled = motoristsKilled[i];
                r.contributingFactorVehicle1 = contributingFactorVehicle1[i];
                r.contributingFactorVehicle2 = contributingFactorVehicle2[i];
                r.contributingFactorVehicle3 = contributingFactorVehicle3[i];
                r.contributingFactorVehicle4 = contributingFactorVehicle4[i];
                r.contributingFactorVehicle5 = contributingFactorVehicle5[i];
                r.collisionID = collisionIDs[i];
                r.vehicleTypeCode1 = vehicleTypeCode1[i];
                r.vehicleTypeCode2 = vehicleTypeCode2[i];
                r.vehicleTypeCode3 = vehicleTypeCode3[i];
                r.vehicleTypeCode4 = vehicleTypeCode4[i];
                r.vehicleTypeCode5 = vehicleTypeCode5[i];
                local.push_back(r);
            }
        }
        #pragma omp critical
        result.insert(result.end(), local.begin(), local.end());
    }
    return result;
}

std::vector<CollisionRecord> CollisionDatasetParallelArrays::searchByZipCode(const int &zipCode) const {
    std::vector<CollisionRecord> result;
    size_t n = zipCodes.size();
    #pragma omp parallel
    {
        std::vector<CollisionRecord> local;
        #pragma omp for nowait schedule(dynamic)
        for (size_t i = 0; i < n; i++) {
            if (zipCodes[i] == zipCode) {
                CollisionRecord r;
                r.crashDate = crashDates[i];
                r.crashTime = crashTimes[i];
                r.borough = boroughs[i];
                r.zipCode = zipCodes[i];
                r.latitude = latitudes[i];
                r.longitude = longitudes[i];
                r.location = locations[i];
                r.onStreetName = onStreetNames[i];
                r.crossStreetName = crossStreetNames[i];
                r.offStreetName = offStreetNames[i];
                r.personsInjured = personsInjured[i];
                r.personsKilled = personsKilled[i];
                r.pedestriansInjured = pedestriansInjured[i];
                r.pedestriansKilled = pedestriansKilled[i];
                r.cyclistsInjured = cyclistsInjured[i];
                r.cyclistsKilled = cyclistsKilled[i];
                r.motoristsInjured = motoristsInjured[i];
                r.motoristsKilled = motoristsKilled[i];
                r.contributingFactorVehicle1 = contributingFactorVehicle1[i];
                r.contributingFactorVehicle2 = contributingFactorVehicle2[i];
                r.contributingFactorVehicle3 = contributingFactorVehicle3[i];
                r.contributingFactorVehicle4 = contributingFactorVehicle4[i];
                r.contributingFactorVehicle5 = contributingFactorVehicle5[i];
                r.collisionID = collisionIDs[i];
                r.vehicleTypeCode1 = vehicleTypeCode1[i];
                r.vehicleTypeCode2 = vehicleTypeCode2[i];
                r.vehicleTypeCode3 = vehicleTypeCode3[i];
                r.vehicleTypeCode4 = vehicleTypeCode4[i];
                r.vehicleTypeCode5 = vehicleTypeCode5[i];
                local.push_back(r);
            }
        }
        #pragma omp critical
        result.insert(result.end(), local.begin(), local.end());
    }
    return result;
}

std::vector<CollisionRecord> CollisionDatasetParallelArrays::searchByInjuryThreshold(int minInjuries) const {
    std::vector<CollisionRecord> result;
    size_t n = personsInjured.size();
    #pragma omp parallel
    {
        std::vector<CollisionRecord> local;
        #pragma omp for nowait schedule(dynamic)
        for (size_t i = 0; i < n; i++) {
            int totalInjuries = personsInjured[i] + pedestriansInjured[i] +
                                 cyclistsInjured[i] + motoristsInjured[i];
            if (totalInjuries >= minInjuries) {
                CollisionRecord r;
                r.crashDate = crashDates[i];
                r.crashTime = crashTimes[i];
                r.borough = boroughs[i];
                r.zipCode = zipCodes[i];
                r.latitude = latitudes[i];
                r.longitude = longitudes[i];
                r.location = locations[i];
                r.onStreetName = onStreetNames[i];
                r.crossStreetName = crossStreetNames[i];
                r.offStreetName = offStreetNames[i];
                r.personsInjured = personsInjured[i];
                r.personsKilled = personsKilled[i];
                r.pedestriansInjured = pedestriansInjured[i];
                r.pedestriansKilled = pedestriansKilled[i];
                r.cyclistsInjured = cyclistsInjured[i];
                r.cyclistsKilled = cyclistsKilled[i];
                r.motoristsInjured = motoristsInjured[i];
                r.motoristsKilled = motoristsKilled[i];
                r.contributingFactorVehicle1 = contributingFactorVehicle1[i];
                r.contributingFactorVehicle2 = contributingFactorVehicle2[i];
                r.contributingFactorVehicle3 = contributingFactorVehicle3[i];
                r.contributingFactorVehicle4 = contributingFactorVehicle4[i];
                r.contributingFactorVehicle5 = contributingFactorVehicle5[i];
                r.collisionID = collisionIDs[i];
                r.vehicleTypeCode1 = vehicleTypeCode1[i];
                r.vehicleTypeCode2 = vehicleTypeCode2[i];
                r.vehicleTypeCode3 = vehicleTypeCode3[i];
                r.vehicleTypeCode4 = vehicleTypeCode4[i];
                r.vehicleTypeCode5 = vehicleTypeCode5[i];
                local.push_back(r);
            }
        }
        #pragma omp critical
        result.insert(result.end(), local.begin(), local.end());
    }
    return result;
}

std::vector<CollisionRecord> CollisionDatasetParallelArrays::searchByLocationBounds(double minLat, double maxLat,
                                                                                   double minLong, double maxLong) const {
    std::vector<CollisionRecord> result;
    size_t n = latitudes.size();
    #pragma omp parallel
    {
        std::vector<CollisionRecord> local;
        #pragma omp for nowait schedule(dynamic)
        for (size_t i = 0; i < n; i++) {
            if (latitudes[i] >= minLat && latitudes[i] <= maxLat &&
                longitudes[i] >= minLong && longitudes[i] <= maxLong) {
                CollisionRecord r;
                r.crashDate = crashDates[i];
                r.crashTime = crashTimes[i];
                r.borough = boroughs[i];
                r.zipCode = zipCodes[i];
                r.latitude = latitudes[i];
                r.longitude = longitudes[i];
                r.location = locations[i];
                r.onStreetName = onStreetNames[i];
                r.crossStreetName = crossStreetNames[i];
                r.offStreetName = offStreetNames[i];
                r.personsInjured = personsInjured[i];
                r.personsKilled = personsKilled[i];
                r.pedestriansInjured = pedestriansInjured[i];
                r.pedestriansKilled = pedestriansKilled[i];
                r.cyclistsInjured = cyclistsInjured[i];
                r.cyclistsKilled = cyclistsKilled[i];
                r.motoristsInjured = motoristsInjured[i];
                r.motoristsKilled = motoristsKilled[i];
                r.contributingFactorVehicle1 = contributingFactorVehicle1[i];
                r.contributingFactorVehicle2 = contributingFactorVehicle2[i];
                r.contributingFactorVehicle3 = contributingFactorVehicle3[i];
                r.contributingFactorVehicle4 = contributingFactorVehicle4[i];
                r.contributingFactorVehicle5 = contributingFactorVehicle5[i];
                r.collisionID = collisionIDs[i];
                r.vehicleTypeCode1 = vehicleTypeCode1[i];
                r.vehicleTypeCode2 = vehicleTypeCode2[i];
                r.vehicleTypeCode3 = vehicleTypeCode3[i];
                r.vehicleTypeCode4 = vehicleTypeCode4[i];
                r.vehicleTypeCode5 = vehicleTypeCode5[i];
                local.push_back(r);
            }
        }
        #pragma omp critical
        result.insert(result.end(), local.begin(), local.end());
    }
    return result;
}
