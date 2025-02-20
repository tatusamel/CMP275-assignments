#include "OptimizedCollisionDataset.hpp"
#include "CSV_Utils.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <omp.h>

void OptimizedCollisionDataset::reserveSpace(size_t capacity) {
    crashDates.reserve(capacity);
    crashTimes.reserve(capacity);
    boroughs.reserve(capacity);
    zipCodes.reserve(capacity);
    latitudes.reserve(capacity);
    longitudes.reserve(capacity);
    locations.reserve(capacity);
    onStreetNames.reserve(capacity);
    crossStreetNames.reserve(capacity);
    offStreetNames.reserve(capacity);

    crashDates.reserve(capacity);
    crashTimes.reserve(capacity);
    boroughs.reserve(capacity);
    zipCodes.reserve(capacity);
    latitudes.reserve(capacity);
    longitudes.reserve(capacity);
    locations.reserve(capacity);
    onStreetNames.reserve(capacity);
    crossStreetNames.reserve(capacity);
    offStreetNames.reserve(capacity);

     // Numeric injury/fatality data
     personsInjured.reserve(capacity);
     personsKilled.reserve(capacity);
     pedestriansInjured.reserve(capacity);
     pedestriansKilled.reserve(capacity);
     cyclistsInjured.reserve(capacity);
     cyclistsKilled.reserve(capacity);
     motoristsInjured.reserve(capacity);
     motoristsKilled.reserve(capacity);
 
     // Contributing factors
     contributingFactorVehicle1.reserve(capacity);
     contributingFactorVehicle2.reserve(capacity);
     contributingFactorVehicle3.reserve(capacity);
     contributingFactorVehicle4.reserve(capacity);
     contributingFactorVehicle5.reserve(capacity);
 
     // Collision IDs
     collisionIDs.reserve(capacity);
 
     // Vehicle type codes
     vehicleTypeCode1.reserve(capacity);
     vehicleTypeCode2.reserve(capacity);
     vehicleTypeCode3.reserve(capacity);
     vehicleTypeCode4.reserve(capacity);
     vehicleTypeCode5.reserve(capacity);
}

bool OptimizedCollisionDataset::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << "\n";
        return false;
    }

    // Skip header
    std::string header;
    std::getline(file, header);

    // Read file size for pre-allocation
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::getline(file, header); // Skip header again
    
    // Estimate number of records (assuming average line length of 200 characters)
    size_t estimatedRecords = fileSize / 200;
    reserveSpace(estimatedRecords);

    std::string line;
    #pragma omp parallel
    {
        // Local string vectors
        std::vector<std::string> localDates, localTimes, localBoroughs, localZipCodes;
        std::vector<std::string> localLocations, localOnStreets, localCrossStreets, localOffStreets;
        
        // Local numeric vectors
        std::vector<double> localLats, localLongs;
        std::vector<int> localPersonsInjured, localPersonsKilled;
        std::vector<int> localPedsInjured, localPedsKilled;
        std::vector<int> localCyclistsInjured, localCyclistsKilled;
        std::vector<int> localMotoristsInjured, localMotoristsKilled;
        
        // Local contributing factors
        std::vector<std::string> localFactor1, localFactor2, localFactor3, localFactor4, localFactor5;
        
        // Local collision IDs
        std::vector<long> localCollisionIDs;
        
        // Local vehicle types
        std::vector<std::string> localVehicle1, localVehicle2, localVehicle3, localVehicle4, localVehicle5;

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }


        #pragma omp for
        for (size_t i = 0; i < lines.size(); i++) {
            auto tokens = splitCSVLine(lines[i]);
            if (tokens.size() < 29) continue;

            try {
                // Location data
                localDates.push_back(tokens[0]);
                localTimes.push_back(tokens[1]);
                localBoroughs.push_back(tokens[2]);
                localZipCodes.push_back(tokens[3]);
                localLats.push_back(tokens[4].empty() ? 0.0 : std::stod(tokens[4]));
                localLongs.push_back(tokens[5].empty() ? 0.0 : std::stod(tokens[5]));
                localLocations.push_back(tokens[6]);
                localOnStreets.push_back(tokens[7]);
                localCrossStreets.push_back(tokens[8]);
                localOffStreets.push_back(tokens[9]);

                // Injury/fatality data
                localPersonsInjured.push_back(tokens[10].empty() ? 0 : std::stoi(tokens[10]));
                localPersonsKilled.push_back(tokens[11].empty() ? 0 : std::stoi(tokens[11]));
                localPedsInjured.push_back(tokens[12].empty() ? 0 : std::stoi(tokens[12]));
                localPedsKilled.push_back(tokens[13].empty() ? 0 : std::stoi(tokens[13]));
                localCyclistsInjured.push_back(tokens[14].empty() ? 0 : std::stoi(tokens[14]));
                localCyclistsKilled.push_back(tokens[15].empty() ? 0 : std::stoi(tokens[15]));
                localMotoristsInjured.push_back(tokens[16].empty() ? 0 : std::stoi(tokens[16]));
                localMotoristsKilled.push_back(tokens[17].empty() ? 0 : std::stoi(tokens[17]));

                // Contributing factors
                localFactor1.push_back(tokens[18]);
                localFactor2.push_back(tokens[19]);
                localFactor3.push_back(tokens[20]);
                localFactor4.push_back(tokens[21]);
                localFactor5.push_back(tokens[22]);

                // Collision ID
                localCollisionIDs.push_back(tokens[23].empty() ? 0 : std::stol(tokens[23]));

                // Vehicle types
                localVehicle1.push_back(tokens[24]);
                localVehicle2.push_back(tokens[25]);
                localVehicle3.push_back(tokens[26]);
                localVehicle4.push_back(tokens[27]);
                localVehicle5.push_back(tokens[28]);

            } catch (const std::exception& e) {
                // #pragma omp critical
                // {
                //     std::cerr << "Error parsing line: " << line << "\n";
                // }
                continue;
            }
        }

        #pragma omp critical
        {
            // Merge location data
            crashDates.insert(crashDates.end(), localDates.begin(), localDates.end());
            crashTimes.insert(crashTimes.end(), localTimes.begin(), localTimes.end());
            boroughs.insert(boroughs.end(), localBoroughs.begin(), localBoroughs.end());
            zipCodes.insert(zipCodes.end(), localZipCodes.begin(), localZipCodes.end());
            latitudes.insert(latitudes.end(), localLats.begin(), localLats.end());
            longitudes.insert(longitudes.end(), localLongs.begin(), localLongs.end());
            locations.insert(locations.end(), localLocations.begin(), localLocations.end());
            onStreetNames.insert(onStreetNames.end(), localOnStreets.begin(), localOnStreets.end());
            crossStreetNames.insert(crossStreetNames.end(), localCrossStreets.begin(), localCrossStreets.end());
            offStreetNames.insert(offStreetNames.end(), localOffStreets.begin(), localOffStreets.end());

            // Merge injury/fatality data
            personsInjured.insert(personsInjured.end(), localPersonsInjured.begin(), localPersonsInjured.end());
            personsKilled.insert(personsKilled.end(), localPersonsKilled.begin(), localPersonsKilled.end());
            pedestriansInjured.insert(pedestriansInjured.end(), localPedsInjured.begin(), localPedsInjured.end());
            pedestriansKilled.insert(pedestriansKilled.end(), localPedsKilled.begin(), localPedsKilled.end());
            cyclistsInjured.insert(cyclistsInjured.end(), localCyclistsInjured.begin(), localCyclistsInjured.end());
            cyclistsKilled.insert(cyclistsKilled.end(), localCyclistsKilled.begin(), localCyclistsKilled.end());
            motoristsInjured.insert(motoristsInjured.end(), localMotoristsInjured.begin(), localMotoristsInjured.end());
            motoristsKilled.insert(motoristsKilled.end(), localMotoristsKilled.begin(), localMotoristsKilled.end());

            // Merge contributing factors
            contributingFactorVehicle1.insert(contributingFactorVehicle1.end(), localFactor1.begin(), localFactor1.end());
            contributingFactorVehicle2.insert(contributingFactorVehicle2.end(), localFactor2.begin(), localFactor2.end());
            contributingFactorVehicle3.insert(contributingFactorVehicle3.end(), localFactor3.begin(), localFactor3.end());
            contributingFactorVehicle4.insert(contributingFactorVehicle4.end(), localFactor4.begin(), localFactor4.end());
            contributingFactorVehicle5.insert(contributingFactorVehicle5.end(), localFactor5.begin(), localFactor5.end());

            // Merge collision IDs
            collisionIDs.insert(collisionIDs.end(), localCollisionIDs.begin(), localCollisionIDs.end());

            // Merge vehicle types
            vehicleTypeCode1.insert(vehicleTypeCode1.end(), localVehicle1.begin(), localVehicle1.end());
            vehicleTypeCode2.insert(vehicleTypeCode2.end(), localVehicle2.begin(), localVehicle2.end());
            vehicleTypeCode3.insert(vehicleTypeCode3.end(), localVehicle3.begin(), localVehicle3.end());
            vehicleTypeCode4.insert(vehicleTypeCode4.end(), localVehicle4.begin(), localVehicle4.end());
            vehicleTypeCode5.insert(vehicleTypeCode5.end(), localVehicle5.begin(), localVehicle5.end());
        }
    }

    file.close();
    return true;
}

std::vector<size_t> OptimizedCollisionDataset::searchByDateRange(
    const std::string& startDate, const std::string& endDate) const {
    
    std::vector<size_t> indices(crashDates.size());
    std::iota(indices.begin(), indices.end(), 0);
    
    std::vector<size_t> results;
    results.reserve(indices.size() / 10); // Estimate 10% of data will match

    #pragma omp parallel
    {
        std::vector<size_t> localResults;
        localResults.reserve(indices.size() / (omp_get_num_threads() * 10));

        #pragma omp for simd nowait
        for (size_t i = 0; i < indices.size(); i++) {
            if (crashDates[i] >= startDate && crashDates[i] <= endDate) {
                localResults.push_back(i);
            }
        }

        #pragma omp critical
        {
            results.insert(results.end(), localResults.begin(), localResults.end());
        }
    }

    return results;
}

std::vector<size_t> OptimizedCollisionDataset::searchByInjuryThreshold(int minInjuries) const {
    std::vector<size_t> results;
    results.reserve(size() / 10);

    #pragma omp parallel
    {
        std::vector<size_t> localResults;
        localResults.reserve(size() / (omp_get_num_threads() * 10));

        #pragma omp for simd nowait
        for (size_t i = 0; i < size(); i++) {
            int totalInjuries = personsInjured[i] + pedestriansInjured[i] +
                               cyclistsInjured[i] + motoristsInjured[i];
            if (totalInjuries >= minInjuries) {
                localResults.push_back(i);
            }
        }

        #pragma omp critical
        {
            results.insert(results.end(), localResults.begin(), localResults.end());
        }
    }

    return results;
}