#include "CollisionDataset.hpp"
#include <omp.h>

bool CollisionDataset::loadFromCSV(const std::string &filename) {
    CSVParser parser(filename);
    if (!parser.parse()) {
        return false;
    }

    records = parser.getRecords();
    return true;
}

std::vector<CollisionRecord> CollisionDataset::searchByDateRange(const std::string &startDate,
                                                               const std::string &endDate) const {
    std::vector<CollisionRecord> result;
    #pragma omp parallel
    {
        std::vector<CollisionRecord> local_result;
        #pragma omp for nowait
        for (size_t i = 0; i < records.size(); i++) {
            if (records[i].crashDate >= startDate && records[i].crashDate <= endDate) {
                local_result.push_back(records[i]);
            }
        }
        #pragma omp critical
        result.insert(result.end(), local_result.begin(), local_result.end());
    }
    return result;
}

std::vector<CollisionRecord> CollisionDataset::searchByBorough(const std::string &borough) const {
    std::vector<CollisionRecord> result;
    #pragma omp parallel
    {
        std::vector<CollisionRecord> local_result;
        #pragma omp for nowait
        for (size_t i = 0; i < records.size(); i++) {
            if (records[i].borough == borough) {
                local_result.push_back(records[i]);
            }
        }
        #pragma omp critical
        result.insert(result.end(), local_result.begin(), local_result.end());
    }
    return result;
}

std::vector<CollisionRecord> CollisionDataset::searchByZipCode(const std::string &zipCode) const {
    std::vector<CollisionRecord> result;
    #pragma omp parallel
    {
        std::vector<CollisionRecord> local_result;
        #pragma omp for nowait
        for (size_t i = 0; i < records.size(); i++) {
            if (records[i].zipCode == zipCode) {
                local_result.push_back(records[i]);
            }
        }
        #pragma omp critical
        result.insert(result.end(), local_result.begin(), local_result.end());
    }
    return result;
}

std::vector<CollisionRecord> CollisionDataset::searchByInjuryThreshold(int minInjuries) const {
    std::vector<CollisionRecord> result;
    #pragma omp parallel
    {
        std::vector<CollisionRecord> local_result;
        #pragma omp for nowait
        for (size_t i = 0; i < records.size(); i++) {
            int totalInjuries = records[i].personsInjured + records[i].pedestriansInjured +
                               records[i].cyclistsInjured + records[i].motoristsInjured;
            if (totalInjuries >= minInjuries) {
                local_result.push_back(records[i]);
            }
        }
        #pragma omp critical
        result.insert(result.end(), local_result.begin(), local_result.end());
    }
    return result;
}

std::vector<CollisionRecord> CollisionDataset::searchByLocationBounds(double minLat, double maxLat,
                                                                       double minLong, double maxLong) const {
    std::vector<CollisionRecord> result;
    #pragma omp parallel
    {
        std::vector<CollisionRecord> local_result;
        #pragma omp for nowait
        for (size_t i = 0; i < records.size(); i++) {
            if (records[i].latitude >= minLat && records[i].latitude <= maxLat &&
                records[i].longitude >= minLong && records[i].longitude <= maxLong) {
                local_result.push_back(records[i]);
            }
        }
        #pragma omp critical
        result.insert(result.end(), local_result.begin(), local_result.end());
    }
    return result;
}

const std::vector<CollisionRecord> &CollisionDataset::getRecords() const {
    return records;
}