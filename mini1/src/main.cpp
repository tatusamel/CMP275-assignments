#include <iostream>
#include "CollisionDataset.hpp"
#include "Benchmark.hpp"

int main() {
    const std::string filename = "../data/Motor_Vehicle_Collisions.csv";
    const int RUN_TIMES = 10;

    // Compare sequential and parallel load benchmarks.
    Benchmark::compareLoadBenchmarks(filename, RUN_TIMES);

    // Compare search by date range benchmarks.
    std::string startDate = "2020-01-01";
    std::string endDate   = "2020-12-31";
    Benchmark::compareSearchByDateBenchmarks(filename, startDate, endDate, RUN_TIMES);

    // Compare search by borough benchmarks.
    Benchmark::compareSearchByBoroughBenchmarks(filename, "BROOKLYN", RUN_TIMES);

    // Compare search by zip code benchmarks.
    Benchmark::compareSearchByZipCodeBenchmarks(filename, "11201", RUN_TIMES);

    // Compare search by injury threshold benchmarks.
    Benchmark::compareSearchByInjuryThresholdBenchmarks(filename, 5, RUN_TIMES);

    // Compare search by location bounds benchmarks.
    Benchmark::compareSearchByLocationBoundsBenchmarks(filename, 40.5, 40.9, -74.0, -73.7, RUN_TIMES);

    return 0;
}
