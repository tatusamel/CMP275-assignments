#ifndef CSV_PARSER_HPP
#define CSV_PARSER_HPP

#include <string>
#include <vector>
#include "CollisionRecord.hpp"
#include "CollisionDatasetParallelArrays.hpp"  // For new parse function

class CSVParser {  
public:

    CSVParser(const std::string filename) : filename(filename) {}

    bool parse();
    bool parseParallel();
    std::vector<CollisionRecord> getRecords() const;

    // New function to directly parse into an object-of-arrays
    bool parseParallelArrays(class CollisionDatasetParallelArrays &dataset);

private:

    std::string filename;
    std::vector<CollisionRecord> records;

    std::vector<std::string> splitCSV(const std::string &line);
    static inline std::string ltrim(std::string &s);
    static inline std::string rtrim(std::string &s);
    static inline std::string trim(std::string &s);
};

#endif // CSV_PARSER_HPP