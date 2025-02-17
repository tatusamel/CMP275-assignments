#ifndef PARALLEL_BENCHMARK_HPP
#define PARALLEL_BENCHMARK_HPP

#include <chrono>
#include <iostream>
#include <iomanip>
#include "CollisionDataset.hpp"
#include "Benchmark.hpp"
#include <omp.h>

class ParallelBenchmark {
public:
    static void compareSearchByDate(const CollisionDataset &dataset,
                                  const std::string &startDate,
                                  const std::string &endDate,
                                  int runTimes,
                                  int numThreads = omp_get_max_threads()) {
        double seqTime = 0.0, parTime = 0.0;
        size_t seqResults = 0, parResults = 0;

        // Sequential runs
        omp_set_num_threads(1);
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByDateRange(startDate, endDate);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            seqTime += elapsed.count();
            if (i == 0) seqResults = results.size();
        }

        // Parallel runs with specified number of threads
        omp_set_num_threads(numThreads);
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByDateRange(startDate, endDate);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            parTime += elapsed.count();
            if (i == 0) parResults = results.size();
        }

        printComparison("Date Range Search", seqTime/runTimes, parTime/runTimes, seqResults, parResults);
    }

    static void compareSearchByBorough(const CollisionDataset &dataset,
                                     const std::string &borough,
                                     int runTimes,
                                     int numThreads = omp_get_max_threads()) {
        double seqTime = 0.0, parTime = 0.0;
        size_t seqResults = 0, parResults = 0;

        // Sequential runs
        omp_set_num_threads(1);
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByBorough(borough);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            seqTime += elapsed.count();
            if (i == 0) seqResults = results.size();
        }

        // Parallel runs with specified number of threads
        omp_set_num_threads(numThreads);
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByBorough(borough);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            parTime += elapsed.count();
            if (i == 0) parResults = results.size();
        }

        printComparison("Borough Search", seqTime/runTimes, parTime/runTimes, seqResults, parResults);
    }

    static void compareSearchByInjuryThreshold(const CollisionDataset &dataset,
                                             int minInjuries,
                                             int runTimes,
                                             int numThreads = omp_get_max_threads()) {
        double seqTime = 0.0, parTime = 0.0;
        size_t seqResults = 0, parResults = 0;

        // Sequential runs
        omp_set_num_threads(1);
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByInjuryThreshold(minInjuries);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            seqTime += elapsed.count();
            if (i == 0) seqResults = results.size();
        }

        // Parallel runs with specified number of threads
        omp_set_num_threads(numThreads);
        for (int i = 0; i < runTimes; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            auto results = dataset.searchByInjuryThreshold(minInjuries);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            parTime += elapsed.count();
            if (i == 0) parResults = results.size();
        }

        printComparison("Injury Threshold Search", seqTime/runTimes, parTime/runTimes, seqResults, parResults);
    }

private:
    static void printComparison(const std::string &testName, 
                              double seqTime, 
                              double parTime,
                              size_t seqResults,
                              size_t parResults) {
        std::cout << "\n=== " << testName << " Comparison ===\n";
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "Sequential Time: " << seqTime << " seconds\n";
        std::cout << "Parallel Time:   " << parTime << " seconds\n";
        std::cout << "Speedup:         " << seqTime/parTime << "x\n";
        std::cout << "Results found:   " << seqResults << " (sequential) vs " 
                 << parResults << " (parallel)\n";
        std::cout << "Using " << omp_get_max_threads() << " threads\n";
    }
};

#endif // PARALLEL_BENCHMARK_HPP