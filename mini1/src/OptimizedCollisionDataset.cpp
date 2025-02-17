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
    // ... reserve for all other vectors
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
        std::vector<std::string> localDates, localTimes, localBoroughs;
        std::vector<double> localLats, localLongs;
        // ... other local vectors
        
        #pragma omp while
        while (std::getline(file, line)) {
            auto tokens = splitCSVLine(line);
            if (tokens.size() < 29) continue;

            localDates.push_back(tokens[0]);
            localTimes.push_back(tokens[1]);
            localBoroughs.push_back(tokens[2]);
            // ... process other fields
        }

        #pragma omp critical
        {
            crashDates.insert(crashDates.end(), localDates.begin(), localDates.end());
            crashTimes.insert(crashTimes.end(), localTimes.begin(), localTimes.end());
            // ... merge other vectors
        }
    }

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