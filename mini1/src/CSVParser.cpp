#include "CSVParser.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <omp.h> // Added for OpenMP

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
            // std::cerr << "Invalid line: " << line << "\n";
            continue;
        }

        CollisionRecord record;

        try {
            record.crashDate = tokens[0];
            record.crashTime = tokens[1];
            record.borough = tokens[2];
            record.zipCode = tokens[3];
            record.latitude = tokens[4].empty() ? 0.0 : std::stod(tokens[4]);
            record.longitude = tokens[5].empty() ? 0.0 : std::stod(tokens[5]);
            record.location = tokens[6];
            record.onStreetName = tokens[7];
            record.crossStreetName = tokens[8];
            record.offStreetName = tokens[9];


            record.personsInjured = tokens[10].empty() ? 0 : std::stoi(tokens[10]);
            record.personsKilled = tokens[11].empty() ? 0 : std::stoi(tokens[11]);
            record.pedestriansInjured = tokens[12].empty() ? 0 : std::stoi(tokens[12]);
            record.pedestriansKilled = tokens[13].empty() ? 0 : std::stoi(tokens[13]);
            record.cyclistsInjured = tokens[14].empty() ? 0 : std::stoi(tokens[14]);
            record.cyclistsKilled = tokens[15].empty() ? 0 : std::stoi(tokens[15]);
            record.motoristsInjured = tokens[16].empty() ? 0 : std::stoi(tokens[16]);
            record.motoristsKilled = tokens[17].empty() ? 0 : std::stoi(tokens[17]);

            record.contributingFactorVehicle1 = tokens[18];
            record.contributingFactorVehicle2 = tokens[19];
            record.contributingFactorVehicle3 = tokens[20];
            record.contributingFactorVehicle4 = tokens[21];
            record.contributingFactorVehicle5 = tokens[22];

            record.collisionID = tokens[23].empty() ? 0 : std::stol(tokens[23]);
            
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

bool CSVParser::parseParallel() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << "\n";
        return false;
    }

    std::string header;
    if (!std::getline(file, header)) {
        std::cerr << "Empty file or unable to read header!\n";
        return false;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    std::vector<CollisionRecord> records_parallel;

    #pragma omp parallel
    {
        std::vector<CollisionRecord> threadRecords;
        #pragma omp for nowait schedule(dynamic)
        for (size_t i = 0; i < lines.size(); i++) {
            auto tokens = splitCSV(lines[i]);
            if (tokens.size() < 29) {
                // std::cerr << "Invalid line: " << lines[i] << "\n";
                continue;
            }
            CollisionRecord record;
            try {
                record.crashDate = tokens[0];
                record.crashTime = tokens[1];
                record.borough = tokens[2];
                record.zipCode = tokens[3];
                record.latitude = tokens[4].empty() ? 0.0 : std::stod(tokens[4]);
                record.longitude = tokens[5].empty() ? 0.0 : std::stod(tokens[5]);
                record.location = tokens[6];
                record.onStreetName = tokens[7];
                record.crossStreetName = tokens[8];
                record.offStreetName = tokens[9];
                record.personsInjured = tokens[10].empty() ? 0 : std::stoi(tokens[10]);
                record.personsKilled = tokens[11].empty() ? 0 : std::stoi(tokens[11]);
                record.pedestriansInjured = tokens[12].empty() ? 0 : std::stoi(tokens[12]);
                record.pedestriansKilled = tokens[13].empty() ? 0 : std::stoi(tokens[13]);
                record.cyclistsInjured = tokens[14].empty() ? 0 : std::stoi(tokens[14]);
                record.cyclistsKilled = tokens[15].empty() ? 0 : std::stoi(tokens[15]);
                record.motoristsInjured = tokens[16].empty() ? 0 : std::stoi(tokens[16]);
                record.motoristsKilled = tokens[17].empty() ? 0 : std::stoi(tokens[17]);
                record.contributingFactorVehicle1 = tokens[18];
                record.contributingFactorVehicle2 = tokens[19];
                record.contributingFactorVehicle3 = tokens[20];
                record.contributingFactorVehicle4 = tokens[21];
                record.contributingFactorVehicle5 = tokens[22];
                record.collisionID = tokens[23].empty() ? 0 : std::stol(tokens[23]);
                record.vehicleTypeCode1 = tokens[24];
                record.vehicleTypeCode2 = tokens[25];
                record.vehicleTypeCode3 = tokens[26];
                record.vehicleTypeCode4 = tokens[27];
                record.vehicleTypeCode5 = tokens[28];
            }
            catch (const std::exception &e) {
                std::cerr << "Error parsing line: " << lines[i] << "\n";
                continue;
            }
            threadRecords.push_back(record);
        }
        #pragma omp critical
        {
            records_parallel.insert(records_parallel.end(), threadRecords.begin(), threadRecords.end());
        }
    }
    
    // Merge parallel results into the main records vector.
    // Optionally clear current records before merging.
    records.insert(records.end(), records_parallel.begin(), records_parallel.end());
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