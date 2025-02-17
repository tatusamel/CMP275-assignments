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

    // TODO: add additional search methods.

    const std::vector<CollisionRecord> &getRecords() const;

private:

    std::vector<CollisionRecord> records;
};

#endif // COLLISION_DATASET_HPP