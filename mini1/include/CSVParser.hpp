#ifndef CSV_PARSER_HPP
#define CSV_PARSER_HPP

#include <string>
#include <vector>
#include "CollisionRecord.hpp"

class CSVParser {  
public:

    CSVParser(const std::string filename) : filename(filename) {}

    bool parse();
    std::vector<CollisionRecord> getRecords() const;
    std::vector<std::string> splitCSV(const std::string &line);

private:

    std::string filename;
    std::vector<CollisionRecord> records;

};

#endif // CSV_PARSER_HPP