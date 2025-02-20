#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP


#include <chrono>
#include <iostream>
#include "CollisionDataset.hpp"
#include "CollisionDatasetParallel.hpp" // Added for parallel benchmarks
#include <omp.h> // Added for setting thread count

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

    // Benchmark the search by location bounds API.
    static void benchmarkSearchByLocationBounds(const CollisionDataset &dataset,
                                                double minLat, double maxLat,
                                                double minLong, double maxLong,
                                                int runTimes) {
        double totalSearchTime = 0.0;
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByLocationBounds(minLat, maxLat, minLong, maxLong);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            totalSearchTime += elapsed.count();
        }
        std::cout << "Average location bounds search time over " << runTimes 
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

    // Benchmark the parallel data loading process.
    static void benchmarkLoadParallel(const std::string &filename, int runTimes) {
        double totalLoadTime = 0.0;
        for (int i = 0; i < runTimes; i++) {
            CollisionDatasetParallel dataset;
            auto start = std::chrono::high_resolution_clock::now();
            if (!dataset.loadFromCSV(filename)) {
                std::cerr << "Failed to load parallel dataset from CSV file on run " << i << ".\n";
                return;
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            totalLoadTime += elapsed.count();
        }
        std::cout << "Average parallel data loading time over " << runTimes 
                  << " runs: " << totalLoadTime / runTimes << " seconds.\n";
    }

    // Benchmark the parallel search by date range API.
    static void benchmarkSearchByDateParallel(const CollisionDatasetParallel &dataset,
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
        std::cout << "Average parallel date range search time over " << runTimes 
                  << " runs: " << totalSearchTime / runTimes << " seconds.\n";
    }
    
    // Similarly, add parallel benchmark methods for borough, zipcode, and injury threshold searches.
    static void benchmarkSearchByBoroughParallel(const CollisionDatasetParallel &dataset,
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
        std::cout << "Average parallel borough search time over " << runTimes 
                  << " runs: " << totalSearchTime / runTimes << " seconds.\n";
    }

    static void benchmarkSearchByZipCodeParallel(const CollisionDatasetParallel &dataset,
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
        std::cout << "Average parallel zip code search time over " << runTimes 
                  << " runs: " << totalSearchTime / runTimes << " seconds.\n";
    }

    static void benchmarkSearchByInjuryThresholdParallel(const CollisionDatasetParallel &dataset,
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
        std::cout << "Average parallel injury threshold search time over " << runTimes 
                  << " runs: " << totalSearchTime / runTimes << " seconds.\n";
    }
    
    static void benchmarkSearchByLocationBoundsParallel(const CollisionDatasetParallel &dataset,
                                                   double minLat, double maxLat,
                                                   double minLong, double maxLong,
                                                   int runTimes) {
        double totalSearchTime = 0.0;
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByLocationBounds(minLat, maxLat, minLong, maxLong);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            totalSearchTime += elapsed.count();
        }
        std::cout << "Average parallel location bounds search time over " << runTimes 
                  << " runs: " << totalSearchTime / runTimes << " seconds.\n";
    }
    
    // Optionally, add methods to compare sequential and parallel benchmarks.
    static void compareLoadBenchmarks(const std::string &filename, int runTimes) {
        std::cout << "\nSequential Load Benchmark:\n";
        benchmarkLoad(filename, runTimes);
        int threadCounts[] = {2, 4, 8};
        for (int threads : threadCounts) {
            omp_set_num_threads(threads);
            std::cout << "\nParallel Load Benchmark with " << threads << " threads:\n";
            benchmarkLoadParallel(filename, runTimes);
        }
    }
    
    static void compareSearchByDateBenchmarks(const std::string &filename,
                                                const std::string &startDate,
                                                const std::string &endDate,
                                                int runTimes) {
        CollisionDataset seqDataset;
        if (!seqDataset.loadFromCSV(filename)) {
            std::cerr << "Sequential dataset load failed.\n";
            return;
        }
        std::cout << "\nSequential Date Range Search Benchmark:\n";
        benchmarkSearchByDate(seqDataset, startDate, endDate, runTimes);
        
        int threadCounts[] = {2, 4, 8};
        for (int threads : threadCounts) {
            omp_set_num_threads(threads);
            CollisionDatasetParallel parDataset;
            if (!parDataset.loadFromCSV(filename)) {
                std::cerr << "Parallel dataset load failed.\n";
                return;
            }
            std::cout << "\nParallel Date Range Search Benchmark with " << threads << " threads:\n";
            benchmarkSearchByDateParallel(parDataset, startDate, endDate, runTimes);
        }
    }

    // New: Comparison for search by borough
    static void compareSearchByBoroughBenchmarks(const std::string &filename,
                                                   const std::string &borough,
                                                   int runTimes) {
        CollisionDataset seqDataset;
        if (!seqDataset.loadFromCSV(filename)) {
            std::cerr << "Sequential dataset load failed.\n";
            return;
        }
        std::cout << "\nSequential Borough Search Benchmark:\n";
        benchmarkSearchByBorough(seqDataset, borough, runTimes);
        
        int threadCounts[] = {2, 4, 8};
        for (int threads : threadCounts) {
            omp_set_num_threads(threads);
            CollisionDatasetParallel parDataset;
            if (!parDataset.loadFromCSV(filename)) {
                std::cerr << "Parallel dataset load failed.\n";
                return;
            }
            std::cout << "\nParallel Borough Search Benchmark with " << threads << " threads:\n";
            benchmarkSearchByBoroughParallel(parDataset, borough, runTimes);
        }
    }

    // New: Comparison for search by zip code
    static void compareSearchByZipCodeBenchmarks(const std::string &filename,
                                                 const std::string &zipCode,
                                                 int runTimes) {
        CollisionDataset seqDataset;
        if (!seqDataset.loadFromCSV(filename)) {
            std::cerr << "Sequential dataset load failed.\n";
            return;
        }
        std::cout << "\nSequential Zip Code Search Benchmark:\n";
        benchmarkSearchByZipCode(seqDataset, zipCode, runTimes);
        
        int threadCounts[] = {2, 4, 8};
        for (int threads : threadCounts) {
            omp_set_num_threads(threads);
            CollisionDatasetParallel parDataset;
            if (!parDataset.loadFromCSV(filename)) {
                std::cerr << "Parallel dataset load failed.\n";
                return;
            }
            std::cout << "\nParallel Zip Code Search Benchmark with " << threads << " threads:\n";
            benchmarkSearchByZipCodeParallel(parDataset, zipCode, runTimes);
        }
    }

    // New: Comparison for search by injury threshold
    static void compareSearchByInjuryThresholdBenchmarks(const std::string &filename,
                                                         int minInjuries,
                                                         int runTimes) {
        CollisionDataset seqDataset;
        if (!seqDataset.loadFromCSV(filename)) {
            std::cerr << "Sequential dataset load failed.\n";
            return;
        }
        std::cout << "\nSequential Injury Threshold Search Benchmark:\n";
        benchmarkSearchByInjuryThreshold(seqDataset, minInjuries, runTimes);
        
        int threadCounts[] = {2, 4, 8};
        for (int threads : threadCounts) {
            omp_set_num_threads(threads);
            CollisionDatasetParallel parDataset;
            if (!parDataset.loadFromCSV(filename)) {
                std::cerr << "Parallel dataset load failed.\n";
                return;
            }
            std::cout << "\nParallel Injury Threshold Search Benchmark with " << threads << " threads:\n";
            benchmarkSearchByInjuryThresholdParallel(parDataset, minInjuries, runTimes);
        }
    }

    // New: Comparison for search by location bounds
    static void compareSearchByLocationBoundsBenchmarks(const std::string &filename,
                                                        double minLat, double maxLat,
                                                        double minLong, double maxLong,
                                                        int runTimes) {
        CollisionDataset seqDataset;
        if (!seqDataset.loadFromCSV(filename)) {
            std::cerr << "Sequential dataset load failed.\n";
            return;
        }
        std::cout << "\nSequential Location Bounds Search Benchmark:\n";
        benchmarkSearchByLocationBounds(seqDataset, minLat, maxLat, minLong, maxLong, runTimes);
        
        int threadCounts[] = {2, 4, 8};
        for (int threads : threadCounts) {
            omp_set_num_threads(threads);
            CollisionDatasetParallel parDataset;
            if (!parDataset.loadFromCSV(filename)) {
                std::cerr << "Parallel dataset load failed.\n";
                return;
            }
            std::cout << "\nParallel Location Bounds Search Benchmark with " << threads << " threads:\n";
            benchmarkSearchByLocationBoundsParallel(parDataset, minLat, maxLat, minLong, maxLong, runTimes);
        }
    }

};


#endif // BENCHMARK_HPP