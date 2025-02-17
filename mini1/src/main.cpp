#include <iostream>
#include <chrono>
#include "CollisionDataset.hpp"

int main () {

    CollisionDataset dataset;
    const std::string filename = "data/Motor_Vehicle_Collisions_-_Crashes.csv";

    const int RUN_TIMES = 10;
    double totalLoadTime = 0.0;

    for(int i = 0; i < RUN_TIMES; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        if (!dataset.loadFromCSV(filename)) {
            std::cerr << "Failed to load dataset from CSV file." << "\n";
            return 1;
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        
        totalLoadTime += elapsed.count();
    }

    std::cout << "Average data loading time over " << RUN_TIMES << " runs: "
              << totalLoadTime / RUN_TIMES << " seconds.\n";

    std::string startDate = "2020-01-01";
    std::string endDate = "2020-12-31";
    double totalSearchTime = 0.0;

    for(int i = 0; i < RUN_TIMES; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        auto results = dataset.searchByDateRange(startDate, endDate);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        
        totalSearchTime += elapsed.count();
    }

    std::cout << "Average search time over " << RUN_TIMES << " runs: "
              << totalSearchTime / RUN_TIMES << " seconds.\n";


    return 0;
}
