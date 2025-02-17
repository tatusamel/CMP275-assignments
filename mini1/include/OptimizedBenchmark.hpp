#ifndef OPTIMIZED_BENCHMARK_HPP
#define OPTIMIZED_BENCHMARK_HPP

#include <chrono>
#include <iostream>
#include "OptimizedCollisionDataset.hpp"
#include "CollisionDataset.hpp"

class OptimizedBenchmark {
public:

    static void compareImplementations(
        const CollisionDataset& original,
        const OptimizedCollisionDataset& optimized,
        const std::string& startDate,
        const std::string& endDate,
        int runTimes) {
        
        double originalTime = 0.0, optimizedTime = 0.0;
        size_t originalResults = 0, optimizedResults = 0;

        // Test original implementation
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = original.searchByDateRange(startDate, endDate);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            originalTime += elapsed.count();
            if (i == 0) originalResults = results.size();
        }

        // Test optimized implementation
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = optimized.searchByDateRange(startDate, endDate);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            optimizedTime += elapsed.count();
            if (i == 0) optimizedResults = results.size();
        }

        printComparison("Date Range Search",
                       originalTime/runTimes,
                       optimizedTime/runTimes,
                       originalResults,
                       optimizedResults);
    }

private:
    static void printComparison(const std::string& testName,
                              double originalTime,
                              double optimizedTime,
                              size_t originalResults,
                              size_t optimizedResults) {
        std::cout << "\n=== " << testName << " Comparison ===\n"
                  << "Original Time:   " << originalTime << " seconds\n"
                  << "Optimized Time:  " << optimizedTime << " seconds\n"
                  << "Speedup:         " << originalTime/optimizedTime << "x\n"
                  << "Results found:   " << originalResults << " (original) vs "
                  << optimizedResults << " (optimized)\n";
    }
};

#endif // OPTIMIZED_BENCHMARK_HPP