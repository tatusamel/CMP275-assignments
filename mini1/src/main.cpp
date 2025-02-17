#include <iostream>
#include "CollisionDataset.hpp"
#include "Benchmark.hpp"
#include "ParallelBenchmark.hpp"

int main() {
    const std::string filename = "../data/Motor_Vehicle_Collisions.csv";
    const int RUN_TIMES = 10;

    std::cout << "\n=== Original Sequential Benchmarks ===\n";
    Benchmark::benchmarkLoad(filename, RUN_TIMES);

    // Create a dataset and load data once.
    CollisionDataset dataset;
    if (!dataset.loadFromCSV(filename)) {
        std::cerr << "Failed to load dataset from CSV file.\n";
        return 1;
    }

    // Test with different thread counts
    const int thread_counts[] = {2, 4, 8};
    std::string startDate = "2020-01-01";
    std::string endDate   = "2020-12-31";
    
    for (int threads : thread_counts) {
        std::cout << "\n=== Testing with " << threads << " threads ===\n";
        
        // Compare search by date range
        ParallelBenchmark::compareSearchByDate(dataset, startDate, endDate, RUN_TIMES, threads);

        // Compare search by borough
        ParallelBenchmark::compareSearchByBorough(dataset, "BROOKLYN", RUN_TIMES, threads);

        // Compare search by injury threshold
        ParallelBenchmark::compareSearchByInjuryThreshold(dataset, 5, RUN_TIMES, threads);
    }

    // Also test with max available threads
    int max_threads = omp_get_max_threads();
    std::cout << "\n=== Testing with maximum available threads (" << max_threads << ") ===\n";
    ParallelBenchmark::compareSearchByDate(dataset, startDate, endDate, RUN_TIMES, max_threads);
    ParallelBenchmark::compareSearchByBorough(dataset, "BROOKLYN", RUN_TIMES, max_threads);
    ParallelBenchmark::compareSearchByInjuryThreshold(dataset, 5, RUN_TIMES, max_threads);
    
    return 0;
}