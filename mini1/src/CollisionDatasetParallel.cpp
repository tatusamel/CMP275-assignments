#include "CollisionDatasetParallel.hpp"
#include "CSVParser.hpp"
#include <fstream>
#include <iostream>
#include <omp.h>

// Load CSV using parallel parser
bool CollisionDatasetParallel::loadFromCSV(const std::string &filename) {
    CSVParser parser(filename);
    if (!parser.parseParallel()) {
        return false;
    }
    records = parser.getRecords();
    return true;
}

std::vector<CollisionRecord> CollisionDatasetParallel::searchByDateRange(const std::string &startDate, const std::string &endDate) const {
    std::vector<CollisionRecord> result;
    #pragma omp parallel
    {
        std::vector<CollisionRecord> local;
        #pragma omp for nowait schedule(dynamic)
        for (size_t i = 0; i < records.size(); i++) {
            if (records[i].crashDate >= startDate && records[i].crashDate <= endDate) {
                local.push_back(records[i]);
            }
        }
        #pragma omp critical
        result.insert(result.end(), local.begin(), local.end());
    }
    return result;
}

std::vector<CollisionRecord> CollisionDatasetParallel::searchByBorough(const std::string &borough) const {
    std::vector<CollisionRecord> result;
    #pragma omp parallel
    {
        std::vector<CollisionRecord> local;
        #pragma omp for nowait schedule(dynamic)
        for (size_t i = 0; i < records.size(); i++) {
            if (records[i].borough == borough) {
                local.push_back(records[i]);
            }
        }
        #pragma omp critical
        result.insert(result.end(), local.begin(), local.end());
    }
    return result;
}

std::vector<CollisionRecord> CollisionDatasetParallel::searchByZipCode(const std::string &zipCode) const {
    std::vector<CollisionRecord> result;
    #pragma omp parallel
    {
        std::vector<CollisionRecord> local;
        #pragma omp for nowait schedule(dynamic)
        for (size_t i = 0; i < records.size(); i++) {
            if (records[i].zipCode == zipCode) {
                local.push_back(records[i]);
            }
        }
        #pragma omp critical
        result.insert(result.end(), local.begin(), local.end());
    }
    return result;
}

std::vector<CollisionRecord> CollisionDatasetParallel::searchByInjuryThreshold(int minInjuries) const {
    std::vector<CollisionRecord> result;
    #pragma omp parallel
    {
        std::vector<CollisionRecord> local;
        #pragma omp for nowait schedule(dynamic)
        for (size_t i = 0; i < records.size(); i++) {
            int totalInjuries = records[i].personsInjured + records[i].pedestriansInjured +
                                 records[i].cyclistsInjured + records[i].motoristsInjured;
            if (totalInjuries >= minInjuries) {
                local.push_back(records[i]);
            }
        }
        #pragma omp critical
        result.insert(result.end(), local.begin(), local.end());
    }
    return result;
}

std::vector<CollisionRecord> CollisionDatasetParallel::searchByLocationBounds(double minLat, double maxLat,
                                                                               double minLong, double maxLong) const {
    std::vector<CollisionRecord> result;
    #pragma omp parallel
    {
        std::vector<CollisionRecord> local;
        #pragma omp for nowait schedule(dynamic)
        for (size_t i = 0; i < records.size(); i++) {
            if (records[i].latitude >= minLat && records[i].latitude <= maxLat &&
                records[i].longitude >= minLong && records[i].longitude <= maxLong) {
                local.push_back(records[i]);
            }
        }
        #pragma omp critical
        result.insert(result.end(), local.begin(), local.end());
    }
    return result;
}

const std::vector<CollisionRecord>& CollisionDatasetParallel::getRecords() const {
    return records;
}
