#include "CSVParser.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <omp.h> // Added for OpenMP
#include <algorithm> 
#include <sstream>
#include "CollisionRecord.hpp"

// Existing parse() function...
bool CSVParser::parse() {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << "\n";
        return false;
    }
    std::string line;
    if (!std::getline(file, line)) {
        std::cerr << "Empty file or unable to read header!\n";
        return false;
    }
    while (std::getline(file, line)) {
        auto tokens = splitCSV(line);
        if (tokens.size() < 29) {
            continue;
        }
        CollisionRecord record;
        try {
            record.crashDate = tokens[0].empty() ? 0 : CollisionRecord::convertToTimestamp(tokens[0]);
            record.crashTime = tokens[1];
            record.borough = tokens[2];
            record.zipCode = trim(tokens[3]).empty() ? 0 : std::stoi(tokens[3]);
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
                record.crashDate = tokens[0].empty() ? 0 : CollisionRecord::convertToTimestamp(tokens[0]);
                record.crashTime = tokens[1];
                record.borough = tokens[2];
                record.zipCode = trim(tokens[3]).empty() ? 0 : std::stoi(tokens[3]);
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
        if (c == '"') {
            if (inQuotes && i+1 < line.size() && line[i+1] == '"') {
                token.push_back('"');
                i++;
            } else {
                inQuotes = !inQuotes;
            }
        } else if (c == ',' && !inQuotes) {
            tokens.push_back(token);
            token.clear();
        } else {
            token.push_back(c);
        }
    }
    tokens.push_back(token);
    return tokens;
}

// New function: directly parse the CSV into CollisionDatasetParallelArrays
bool CSVParser::parseParallelArrays(CollisionDatasetParallelArrays &dataset) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for parallel arrays: " << filename << "\n";
        return false;
    }
    std::string header;
    if (!std::getline(file, header)) {
        std::cerr << "Empty file or unable to read header!\n";
        return false;
    }
    
    // Read remaining lines into vector
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    
    size_t n = lines.size();
    // Resize dataset arrays
    dataset.crashDates.resize(n);
    dataset.crashTimes.resize(n);
    dataset.boroughs.resize(n);
    dataset.zipCodes.resize(n);
    dataset.latitudes.resize(n);
    dataset.longitudes.resize(n);
    dataset.locations.resize(n);
    dataset.onStreetNames.resize(n);
    dataset.crossStreetNames.resize(n);
    dataset.offStreetNames.resize(n);
    dataset.personsInjured.resize(n);
    dataset.personsKilled.resize(n);
    dataset.pedestriansInjured.resize(n);
    dataset.pedestriansKilled.resize(n);
    dataset.cyclistsInjured.resize(n);
    dataset.cyclistsKilled.resize(n);
    dataset.motoristsInjured.resize(n);
    dataset.motoristsKilled.resize(n);
    dataset.contributingFactorVehicle1.resize(n);
    dataset.contributingFactorVehicle2.resize(n);
    dataset.contributingFactorVehicle3.resize(n);
    dataset.contributingFactorVehicle4.resize(n);
    dataset.contributingFactorVehicle5.resize(n);
    dataset.collisionIDs.resize(n);
    dataset.vehicleTypeCode1.resize(n);
    dataset.vehicleTypeCode2.resize(n);
    dataset.vehicleTypeCode3.resize(n);
    dataset.vehicleTypeCode4.resize(n);
    dataset.vehicleTypeCode5.resize(n);
    
    // Fill arrays in parallel
    #pragma omp parallel for schedule(dynamic)
    for (size_t i = 0; i < n; i++) {
        auto tokens = splitCSV(lines[i]);
        if (tokens.size() < 29) continue;
        dataset.crashDates[i] = tokens[0].empty() ? 0 : CollisionRecord::convertToTimestamp(tokens[0]);
        dataset.crashTimes[i] = tokens[1];
        dataset.boroughs[i] = tokens[2];
        dataset.zipCodes[i] = trim(tokens[3]).empty() ? 0 : std::stoi(tokens[3]);
        dataset.latitudes[i] = tokens[4].empty() ? 0.0 : std::stod(tokens[4]);
        dataset.longitudes[i] = tokens[5].empty() ? 0.0 : std::stod(tokens[5]);
        dataset.locations[i] = tokens[6];
        dataset.onStreetNames[i] = tokens[7];
        dataset.crossStreetNames[i] = tokens[8];
        dataset.offStreetNames[i] = tokens[9];
        dataset.personsInjured[i] = tokens[10].empty() ? 0 : std::stoi(tokens[10]);
        dataset.personsKilled[i] = tokens[11].empty() ? 0 : std::stoi(tokens[11]);
        dataset.pedestriansInjured[i] = tokens[12].empty() ? 0 : std::stoi(tokens[12]);
        dataset.pedestriansKilled[i] = tokens[13].empty() ? 0 : std::stoi(tokens[13]);
        dataset.cyclistsInjured[i] = tokens[14].empty() ? 0 : std::stoi(tokens[14]);
        dataset.cyclistsKilled[i] = tokens[15].empty() ? 0 : std::stoi(tokens[15]);
        dataset.motoristsInjured[i] = tokens[16].empty() ? 0 : std::stoi(tokens[16]);
        dataset.motoristsKilled[i] = tokens[17].empty() ? 0 : std::stoi(tokens[17]);
        dataset.contributingFactorVehicle1[i] = tokens[18];
        dataset.contributingFactorVehicle2[i] = tokens[19];
        dataset.contributingFactorVehicle3[i] = tokens[20];
        dataset.contributingFactorVehicle4[i] = tokens[21];
        dataset.contributingFactorVehicle5[i] = tokens[22];
        dataset.collisionIDs[i] = tokens[23].empty() ? 0 : std::stol(tokens[23]);
        dataset.vehicleTypeCode1[i] = tokens[24];
        dataset.vehicleTypeCode2[i] = tokens[25];
        dataset.vehicleTypeCode3[i] = tokens[26];
        dataset.vehicleTypeCode4[i] = tokens[27];
        dataset.vehicleTypeCode5[i] = tokens[28];
    }
    
    return true;
}

std::string CSVParser::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    return s;
}
std::string CSVParser::rtrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base());
    return s;
}
std::string CSVParser::trim(std::string &s) {
    ltrim(s);
    rtrim(s);
    return s;
}