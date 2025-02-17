#include "CSVParser.hpp"
#include <fstream>
#include <iostream>
#include <vector>


bool CSVParser::parse() {

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << "\n";
        return false;
    }

    std::string line;
    if (!std::getline(file, line)) {
        std::cerr << "Empty file or unable to read header! "  << "\n";
        return false;
    }

    while (std::getline(file,line)) {

        auto tokens = splitCSV(line);
        if (tokens.size() < 29) {
            std::cerr << "Invalid line: " << line << "\n";
            continue;
        }

        CollisionRecord record;

        try {
            record.crashDate = tokens[0];
            record.crashTime = tokens[1];
            record.borough = tokens[2];
            record.zipCode = tokens[3];
            record.latitude = std::stod(tokens[4]);
            record.longitude = std::stod(tokens[5]);
            record.location = tokens[6];
            record.onStreetName = tokens[7];
            record.crossStreetName = tokens[8];
            record.offStreetName = tokens[9];

            record.personsInjured = std::stoi(tokens[10]);
            record.personsKilled = std::stoi(tokens[11]);
            record.pedestriansInjured = std::stoi(tokens[12]);
            record.pedestriansKilled = std::stoi(tokens[13]);
            record.cyclistsInjured = std::stoi(tokens[14]);
            record.cyclistsKilled = std::stoi(tokens[15]);
            record.motoristsInjured = std::stoi(tokens[16]);
            record.motoristsKilled = std::stoi(tokens[17]);

            record.contributingFactorVehicle1 = tokens[18];
            record.contributingFactorVehicle2 = tokens[19];
            record.contributingFactorVehicle3 = tokens[20];
            record.contributingFactorVehicle4 = tokens[21];
            record.contributingFactorVehicle5 = tokens[22];

            record.collisionID = std::stol(tokens[23]);

            record.vehicleTypeCode1 = tokens[24];
            record.vehicleTypeCode2 = tokens[25];
            record.vehicleTypeCode3 = tokens[26];
            record.vehicleTypeCode4 = tokens[27];
            record.vehicleTypeCode5 = tokens[28];

        } catch (const std::exception &e) {
            std::cerr << "Error parsing line: " << line << "\n";
        }
        records.push_back(record);
    }
    file.close();
    return true;

}

std::vector<CollisionRecord> CSVParser::getRecords() const {
    return records;
}


std::vector<std::string> CSVParser::splitCSV(const std::string &line) {
    std::vector<std::string> tokens;
    std::string token;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];
        
        if ( c == '"') {
            // check if it's an escaped quote
            if (inQuotes && i+1 < line.size() && line[i+1] == '"') {
                token.push_back('"');
                i++;
            }else {
                inQuotes = !inQuotes;
            }
        }else if ( c==',' && !inQuotes) {
            tokens.push_back(token);
            token.clear();
        }
        else {
            token.push_back(c);
        }
    }
    tokens.push_back(token);
    return tokens;
}