#include "CollisionDataset.hpp"

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
    for (const auto &record : records) {
        if (record.crashDate >= startDate && record.crashDate <= endDate) {
            result.push_back(record);
        }
    }
    return result;
}

std::vector<CollisionRecord> CollisionDataset::searchByBorough(const std::string &borough) const {
    std::vector<CollisionRecord> result;
    for (const auto &record : records) {
        // Convert both strings to lower case if needed for case-insensitive comparison
        if (record.borough == borough) {
            result.push_back(record);
        }
    }
    return result;
}

std::vector<CollisionRecord> CollisionDataset::searchByZipCode(const std::string &zipCode) const {
    std::vector<CollisionRecord> result;
    for (const auto &record : records) {
        if (record.zipCode == zipCode) {
            result.push_back(record);
        }
    }
    return result;
}

std::vector<CollisionRecord> CollisionDataset::searchByInjuryThreshold(int minInjuries) const {
    std::vector<CollisionRecord> result;
    for (const auto &record : records) {
        // Sum up different injury counts; you could customize this
        int totalInjuries = record.personsInjured + record.pedestriansInjured +
                            record.cyclistsInjured + record.motoristsInjured;
        if (totalInjuries >= minInjuries) {
            result.push_back(record);
        }
    }
    return result;
}

std::vector<CollisionRecord> CollisionDataset::searchByLocationBounds(double minLat, double maxLat,
                                                                       double minLong, double maxLong) const {
    std::vector<CollisionRecord> result;
    for (const auto &record : records) {
        if (record.latitude >= minLat && record.latitude <= maxLat &&
            record.longitude >= minLong && record.longitude <= maxLong) {
            result.push_back(record);
        }
    }
    return result;
}

const std::vector<CollisionRecord> &CollisionDataset::getRecords() const {
    return records;
}