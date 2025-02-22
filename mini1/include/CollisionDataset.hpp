#ifndef COLLISION_DATASET_HPP
#define COLLISION_DATASET_HPP

#include <string>
#include <vector>
#include "CollisionRecord.hpp"
#include "CSVParser.hpp"

class CollisionDataset {

public:
    bool loadFromCSV(const std::string &filename);

    // range search API
    std::vector<CollisionRecord> searchByDateRange(const std::string &startDate, const std::string &endDate) const;
    std::vector<CollisionRecord> searchByBorough(const std::string &borough) const;
    std::vector<CollisionRecord> searchByZipCode(const int &zipCode) const;
    std::vector<CollisionRecord> searchByInjuryThreshold(int minInjuries) const;
    std::vector<CollisionRecord> searchByLocationBounds(double minLat, double maxLat,
                                                        double minLong, double maxLong) const;


    const std::vector<CollisionRecord> &getRecords() const;

private:

    std::vector<CollisionRecord> records;
};

#endif // COLLISION_DATASET_HPP