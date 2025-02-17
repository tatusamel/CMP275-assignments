#include <iostream>
#include "CollisionDataset.hpp"
#include "Benchmark.hpp"

int main() {
    const std::string filename = "../data/Motor_Vehicle_Collisions.csv";
    const int RUN_TIMES = 10;

    Benchmark::benchmarkLoad(filename, RUN_TIMES);

    // Create a dataset and load data once.
    CollisionDataset dataset;
    if (!dataset.loadFromCSV(filename)) {
        std::cerr << "Failed to load dataset from CSV file.\n";
        return 1;
    }

    // Benchmark search by date range.
    std::string startDate = "2020-01-01";
    std::string endDate   = "2020-12-31";
    Benchmark::benchmarkSearchByDate(dataset, startDate, endDate, RUN_TIMES);

    // Benchmark search by borough (for example, "BROOKLYN").
    Benchmark::benchmarkSearchByBorough(dataset, "BROOKLYN", RUN_TIMES);

    // Benchmark search by zip code (for example, "11201").
    Benchmark::benchmarkSearchByZipCode(dataset, "11201", RUN_TIMES);

    // Benchmark search by injury threshold (for example, minimum 5 injuries).
    Benchmark::benchmarkSearchByInjuryThreshold(dataset, 5, RUN_TIMES);
    
    return 0;
}
