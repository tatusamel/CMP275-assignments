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
const std::vector<CollisionRecord> &CollisionDataset::getRecords() const {
    return records;
}