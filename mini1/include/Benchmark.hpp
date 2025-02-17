#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP


#include <chrono>
#include <iostream>
#include "CollisionDataset.hpp"

class Benchmark {
public:

    // Benchmark the data loading process.
    static void benchmarkLoad(const std::string &filename, int runTimes) {
        double totalLoadTime = 0.0;
        for (int i = 0; i < runTimes; i++) {
            CollisionDataset dataset;
            auto start = std::chrono::high_resolution_clock::now();
            if (!dataset.loadFromCSV(filename)) {
                std::cerr << "Failed to load dataset from CSV file on run " << i << ".\n";
                return;
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            totalLoadTime += elapsed.count();
        }
        std::cout << "Average data loading time over " << runTimes 
                  << " runs: " << totalLoadTime / runTimes << " seconds.\n";
    }

    // Benchmark the search by date range API.
    static void benchmarkSearchByDate(const CollisionDataset &dataset,
                                      const std::string &startDate,
                                      const std::string &endDate,
                                      int runTimes) {
        double totalSearchTime = 0.0;
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByDateRange(startDate, endDate);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            totalSearchTime += elapsed.count();
        }
        std::cout << "Average date range search time over " << runTimes 
                  << " runs: " << totalSearchTime / runTimes << " seconds.\n";
    }

    // You can add similar benchmarking methods for other APIs.
    static void benchmarkSearchByBorough(const CollisionDataset &dataset,
                                           const std::string &borough,
                                           int runTimes) {
        double totalSearchTime = 0.0;
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByBorough(borough);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            totalSearchTime += elapsed.count();
        }
        std::cout << "Average borough search time over " << runTimes 
                  << " runs: " << totalSearchTime / runTimes << " seconds.\n";
    }

    static void benchmarkSearchByZipCode(const CollisionDataset &dataset,
                                           const std::string &zipCode,
                                           int runTimes) {
        double totalSearchTime = 0.0;
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByZipCode(zipCode);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            totalSearchTime += elapsed.count();
        }
        std::cout << "Average zip code search time over " << runTimes 
                  << " runs: " << totalSearchTime / runTimes << " seconds.\n";
    }

    static void benchmarkSearchByInjuryThreshold(const CollisionDataset &dataset,
                                           int minInjuries,
                                           int runTimes) {
        double totalSearchTime = 0.0;
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByInjuryThreshold(minInjuries);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            totalSearchTime += elapsed.count();
        }
        std::cout << "Average injury threshold search time over " << runTimes 
                  << " runs: " << totalSearchTime / runTimes << " seconds.\n";
    }


};


#endif // BENCHMARK_HPP