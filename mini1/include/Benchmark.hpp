#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP


#include <chrono>
#include <iostream>
#include "CollisionDataset.hpp"
#include "CollisionDatasetParallel.hpp" 
#include "CollisionDatasetParallelArrays.hpp" 
#include <omp.h> 

class Benchmark {
public:


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

    
    static void benchmarkSearchByDate(const CollisionDataset &dataset,
                                      const std::string &startDate,
                                      const std::string &endDate,
                                      int runTimes) {
        double totalSearchTime = 0.0;
        int resultCount = 0; // new: store results count
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByDateRange(startDate, endDate);
            if(i==0) resultCount = results.size();
            auto end = std::chrono::high_resolution_clock::now();
            totalSearchTime += std::chrono::duration<double>(end - start).count();
        }
        std::cout << "Average date range search time over " << runTimes 
                  << " runs: " << totalSearchTime / runTimes 
                  << " seconds. Results found: " << resultCount << ".\n";
    }

    
    static void benchmarkSearchByLocationBounds(const CollisionDataset &dataset,
                                                double minLat, double maxLat,
                                                double minLong, double maxLong,
                                                int runTimes) {
        double totalSearchTime = 0.0;
        int resultCount = 0;
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByLocationBounds(minLat, maxLat, minLong, maxLong);
            if(i==0) resultCount = results.size();
            auto end = std::chrono::high_resolution_clock::now();
            totalSearchTime += std::chrono::duration<double>(end - start).count();
        }
        std::cout << "Average location bounds search time over " << runTimes 
                  << " runs: " << totalSearchTime / runTimes 
                  << " seconds. Results found: " << resultCount << ".\n";
    }

    
    static void benchmarkSearchByBorough(const CollisionDataset &dataset,
                                           const std::string &borough,
                                           int runTimes) {
        double totalSearchTime = 0.0;
        int resultCount = 0;
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByBorough(borough);
            if(i==0) resultCount = results.size();
            auto end = std::chrono::high_resolution_clock::now();
            totalSearchTime += std::chrono::duration<double>(end - start).count();
        }
        std::cout << "Average borough search time over " << runTimes 
                  << " runs: " << totalSearchTime / runTimes 
                  << " seconds. Results found: " << resultCount << ".\n";
    }

    static void benchmarkSearchByZipCode(const CollisionDataset &dataset,
                                           const int &zipCode,
                                           int runTimes) {
        double totalSearchTime = 0.0;
        int resultCount = 0;
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByZipCode(zipCode);
            if(i==0) resultCount = results.size();
            auto end = std::chrono::high_resolution_clock::now();
            totalSearchTime += std::chrono::duration<double>(end - start).count();
        }
        std::cout << "Average zip code search time over " << runTimes 
                  << " runs: " << totalSearchTime / runTimes 
                  << " seconds. Results found: " << resultCount << ".\n";
    }

    static void benchmarkSearchByInjuryThreshold(const CollisionDataset &dataset,
                                           int minInjuries,
                                           int runTimes) {
        double totalSearchTime = 0.0;
        int resultCount = 0;
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByInjuryThreshold(minInjuries);
            if(i==0) resultCount = results.size();
            auto end = std::chrono::high_resolution_clock::now();
            totalSearchTime += std::chrono::duration<double>(end - start).count();
        }
        std::cout << "Average injury threshold search time over " << runTimes 
                  << " runs: " << totalSearchTime / runTimes 
                  << " seconds. Results found: " << resultCount << ".\n";
    }

    
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
        int resultCount = 0;
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByDateRange(startDate, endDate);
            if(i==0) resultCount = results.size();
            auto end = std::chrono::high_resolution_clock::now();
            totalSearchTime += std::chrono::duration<double>(end - start).count();
        }
        std::cout << "Average parallel date range search time over " << runTimes 
                  << " runs: " << totalSearchTime / runTimes 
                  << " seconds. Results found: " << resultCount << ".\n";
    }
    
    static void benchmarkSearchByBoroughParallel(const CollisionDatasetParallel &dataset,
                                                   const std::string &borough,
                                                   int runTimes) {
        double totalSearchTime = 0.0;
        int resultCount = 0;
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByBorough(borough);
            if(i==0) resultCount = results.size();
            auto end = std::chrono::high_resolution_clock::now();
            totalSearchTime += std::chrono::duration<double>(end - start).count();
        }
        std::cout << "Average parallel borough search time over " << runTimes 
                  << " runs: " << totalSearchTime / runTimes 
                  << " seconds. Results found: " << resultCount << ".\n";
    }

    static void benchmarkSearchByZipCodeParallel(const CollisionDatasetParallel &dataset,
                                                   const int &zipCode,
                                                   int runTimes) {
        double totalSearchTime = 0.0;
        int resultCount = 0;
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByZipCode(zipCode);
            if(i==0) resultCount = results.size();
            auto end = std::chrono::high_resolution_clock::now();
            totalSearchTime += std::chrono::duration<double>(end - start).count();
        }
        std::cout << "Average parallel zip code search time over " << runTimes 
                  << " runs: " << totalSearchTime / runTimes 
                  << " seconds. Results found: " << resultCount << ".\n";
    }

    static void benchmarkSearchByInjuryThresholdParallel(const CollisionDatasetParallel &dataset,
                                                   int minInjuries,
                                                   int runTimes) {
        double totalSearchTime = 0.0;
        int resultCount = 0;
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByInjuryThreshold(minInjuries);
            if(i==0) resultCount = results.size();
            auto end = std::chrono::high_resolution_clock::now();
            totalSearchTime += std::chrono::duration<double>(end - start).count();
        }
        std::cout << "Average parallel injury threshold search time over " << runTimes 
                  << " runs: " << totalSearchTime / runTimes 
                  << " seconds. Results found: " << resultCount << ".\n";
    }
    
    static void benchmarkSearchByLocationBoundsParallel(const CollisionDatasetParallel &dataset,
                                                   double minLat, double maxLat,
                                                   double minLong, double maxLong,
                                                   int runTimes) {
        double totalSearchTime = 0.0;
        int resultCount = 0;
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByLocationBounds(minLat, maxLat, minLong, maxLong);
            if(i==0) resultCount = results.size();
            auto end = std::chrono::high_resolution_clock::now();
            totalSearchTime += std::chrono::duration<double>(end - start).count();
        }
        std::cout << "Average parallel location bounds search time over " << runTimes 
                  << " runs: " << totalSearchTime / runTimes 
                  << " seconds. Results found: " << resultCount << ".\n";
    }
    
    // Optionally, add methods to compare sequential and parallel benchmarks.
    static void compareLoadBenchmarks(const std::string &filename, int runTimes) {
        std::cout << "\nSequential Load Benchmark:\n";
        benchmarkLoad(filename, runTimes);
        int threadCounts[] = {2, 4, 8, 16};
        for (int threads : threadCounts) {
            omp_set_num_threads(threads);
            std::cout << "\nParallel Load Benchmark with " << threads << " threads:\n";
            benchmarkLoadParallel(filename, runTimes);
        }
    }
    
    // Modified: Comparison for search by date range using pre-loaded datasets.
    static void compareSearchByDateBenchmarks(const CollisionDataset &seqDataset,
                                              const CollisionDatasetParallel &parDataset,
                                              const std::string &startDate,
                                              const std::string &endDate,
                                              int runTimes) {
        std::cout << "\nSequential Date Range Search Benchmark:\n";
        benchmarkSearchByDate(seqDataset, startDate, endDate, runTimes);
        
        int threadCounts[] = {2, 4, 8, 16};
        for (int threads : threadCounts) {
            omp_set_num_threads(threads);
            std::cout << "\nParallel Date Range Search Benchmark with " << threads << " threads:\n";
            benchmarkSearchByDateParallel(parDataset, startDate, endDate, runTimes);
        }
    }

    // Modified: Comparison for search by borough using pre-loaded datasets.
    static void compareSearchByBoroughBenchmarks(const CollisionDataset &seqDataset,
                                                 const CollisionDatasetParallel &parDataset,
                                                 const std::string &borough,
                                                 int runTimes) {
        std::cout << "\nSequential Borough Search Benchmark:\n";
        benchmarkSearchByBorough(seqDataset, borough, runTimes);
        
        int threadCounts[] = {2, 4, 8, 16};
        for (int threads : threadCounts) {
            omp_set_num_threads(threads);
            std::cout << "\nParallel Borough Search Benchmark with " << threads << " threads:\n";
            benchmarkSearchByBoroughParallel(parDataset, borough, runTimes);
        }
    }

    static void compareSearchByZipCodeBenchmarks(const CollisionDataset &seqDataset,
                                                 const CollisionDatasetParallel &parDataset,
                                                 const int &zipCode,
                                                 int runTimes) {
        std::cout << "\nSequential Zip Code Search Benchmark:\n";
        benchmarkSearchByZipCode(seqDataset, zipCode, runTimes);
        
        int threadCounts[] = {2, 4, 8, 16};
        for (int threads : threadCounts) {
            omp_set_num_threads(threads);
            std::cout << "\nParallel Zip Code Search Benchmark with " << threads << " threads:\n";
            benchmarkSearchByZipCodeParallel(parDataset, zipCode, runTimes);
        }
    }

    // Modified: Comparison for search by injury threshold using pre-loaded datasets.
    static void compareSearchByInjuryThresholdBenchmarks(const CollisionDataset &seqDataset,
                                                         const CollisionDatasetParallel &parDataset,
                                                         int minInjuries,
                                                         int runTimes) {
        std::cout << "\nSequential Injury Threshold Search Benchmark:\n";
        benchmarkSearchByInjuryThreshold(seqDataset, minInjuries, runTimes);
        
        int threadCounts[] = {2, 4, 8, 16};
        for (int threads : threadCounts) {
            omp_set_num_threads(threads);
            std::cout << "\nParallel Injury Threshold Search Benchmark with " << threads << " threads:\n";
            benchmarkSearchByInjuryThresholdParallel(parDataset, minInjuries, runTimes);
        }
    }

    // Modified: Comparison for search by location bounds using pre-loaded datasets.
    static void compareSearchByLocationBoundsBenchmarks(const CollisionDataset &seqDataset,
                                                        const CollisionDatasetParallel &parDataset,
                                                        double minLat, double maxLat,
                                                        double minLong, double maxLong,
                                                        int runTimes) {
        std::cout << "\nSequential Location Bounds Search Benchmark:\n";
        benchmarkSearchByLocationBounds(seqDataset, minLat, maxLat, minLong, maxLong, runTimes);
        
        int threadCounts[] = {2, 4, 8, 16};
        for (int threads : threadCounts) {
            omp_set_num_threads(threads);
            std::cout << "\nParallel Location Bounds Search Benchmark with " << threads << " threads:\n";
            benchmarkSearchByLocationBoundsParallel(parDataset, minLat, maxLat, minLong, maxLong, runTimes);
        }
    }

    // New: Comparison for Phase3 (object-of-arrays) load benchmark.
    static void compareLoadBenchmarksPhase3(const std::string &filename, int runTimes) {
        std::cout << "\nPhase3 (Parallel Arrays) Load Benchmark:\n";
        int threadCounts[] = {2, 4, 8, 16};
        for (int threads : threadCounts) {
            omp_set_num_threads(threads);
            CollisionDatasetParallelArrays dataset;
            auto start = std::chrono::high_resolution_clock::now();
            if (!dataset.loadFromCSV(filename)) {
                std::cerr << "Phase3 load failed with " << threads << " threads.\n";
                return;
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            std::cout << "Phase3 load time with " << threads << " threads: " << elapsed.count() << " seconds.\n";
        }
    }

    // Modified: Comparison for Phase3 search by date range using a pre-loaded dataset.
    static void compareSearchByDateBenchmarksPhase3(const CollisionDatasetParallelArrays &dataset,
                                                    const std::string &startDate,
                                                    const std::string &endDate,
                                                    int runTimes) {
        int threadCounts[] = {2, 4, 8, 16};
        for (int threads : threadCounts) {
            omp_set_num_threads(threads);
            std::cout << "\nPhase3 Date Range Search Benchmark with " << threads << " threads:\n";
            double totalTime = 0.0;
            int resultCount = 0;
            for (int i = 0; i < runTimes; i++) {
                auto start = std::chrono::high_resolution_clock::now();
                auto results = dataset.searchByDateRange(startDate, endDate);
                if(i==0) resultCount = results.size();
                auto end = std::chrono::high_resolution_clock::now();
                totalTime += std::chrono::duration<double>(end - start).count();
            }
            std::cout << "Avg time: " << totalTime / runTimes 
                      << " seconds. Results found: " << resultCount << ".\n";
        }
    }

    // Similarly, add compare functions for borough, zipcode, injury threshold, and location bounds for phase3.
    // e.g.,
    // Modified: Comparison for Phase3 search by borough using a pre-loaded dataset.
    static void compareSearchByBoroughBenchmarksPhase3(const CollisionDatasetParallelArrays &dataset,
                                                       const std::string &borough,
                                                       int runTimes) {
        int threadCounts[] = {2, 4, 8, 16};
        for (int threads : threadCounts) {
            omp_set_num_threads(threads);
            std::cout << "\nPhase3 Borough Search Benchmark with " << threads << " threads:\n";
            double totalTime = 0.0;
            int resultCount = 0;
            for (int i = 0; i < runTimes; i++) {
                auto start = std::chrono::high_resolution_clock::now();
                auto results = dataset.searchByBorough(borough);
                if(i==0) resultCount = results.size();
                auto end = std::chrono::high_resolution_clock::now();
                totalTime += std::chrono::duration<double>(end - start).count();
            }
            std::cout << "Avg time: " << totalTime / runTimes 
                      << " seconds. Results found: " << resultCount << ".\n";
        }
    }

    // New: Comparison for Phase3 search by Zip Code.
    static void compareSearchByZipCodeBenchmarksPhase3(const CollisionDatasetParallelArrays &dataset,
                                                       const int &zipCode,
                                                       int runTimes) {
        int threadCounts[] = {2, 4, 8, 16};
        for (int threads : threadCounts) {
            omp_set_num_threads(threads);
            std::cout << "\nPhase3 Zip Code Search Benchmark with " << threads << " threads:\n";
            double totalTime = 0.0;
            int resultCount = 0;
            for (int i = 0; i < runTimes; i++) {
                auto start = std::chrono::high_resolution_clock::now();
                auto results = dataset.searchByZipCode(zipCode);
                if(i==0) resultCount = results.size();
                auto end = std::chrono::high_resolution_clock::now();
                totalTime += std::chrono::duration<double>(end - start).count();
            }
            std::cout << "Avg time: " << totalTime / runTimes 
                      << " seconds. Results found: " << resultCount << ".\n";
        }
    }

    // New: Comparison for Phase3 search by Injury Threshold.
    static void compareSearchByInjuryThresholdBenchmarksPhase3(const CollisionDatasetParallelArrays &dataset,
                                                               int minInjuries,
                                                               int runTimes) {
        int threadCounts[] = {2, 4, 8, 16};
        for (int threads : threadCounts) {
            omp_set_num_threads(threads);
            std::cout << "\nPhase3 Injury Threshold Search Benchmark with " << threads << " threads:\n";
            double totalTime = 0.0;
            int resultCount = 0;
            for (int i = 0; i < runTimes; i++) {
                auto start = std::chrono::high_resolution_clock::now();
                auto results = dataset.searchByInjuryThreshold(minInjuries);
                if(i==0) resultCount = results.size();
                auto end = std::chrono::high_resolution_clock::now();
                totalTime += std::chrono::duration<double>(end - start).count();
            }
            std::cout << "Avg time: " << totalTime / runTimes 
                      << " seconds. Results found: " << resultCount << ".\n";
        }
    }

    // New: Comparison for Phase3 search by Location Bounds.
    static void compareSearchByLocationBoundsBenchmarksPhase3(const CollisionDatasetParallelArrays &dataset,
                                                              double minLat, double maxLat,
                                                              double minLong, double maxLong,
                                                              int runTimes) {
        int threadCounts[] = {2, 4, 8, 16};
        for (int threads : threadCounts) {
            omp_set_num_threads(threads);
            std::cout << "\nPhase3 Location Bounds Search Benchmark with " << threads << " threads:\n";
            double totalTime = 0.0;
            int resultCount = 0;
            for (int i = 0; i < runTimes; i++) {
                auto start = std::chrono::high_resolution_clock::now();
                auto results = dataset.searchByLocationBounds(minLat, maxLat, minLong, maxLong);
                if(i==0) resultCount = results.size();
                auto end = std::chrono::high_resolution_clock::now();
                totalTime += std::chrono::duration<double>(end - start).count();
            }
            std::cout << "Avg time: " << totalTime / runTimes 
                      << " seconds. Results found: " << resultCount << ".\n";
        }
    }

};


#endif // BENCHMARK_HPP