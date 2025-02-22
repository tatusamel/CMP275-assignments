#include <iostream>
#include "CollisionDataset.hpp"
#include "CollisionDatasetParallel.hpp"
#include "CollisionDatasetParallelArrays.hpp"
#include "Benchmark.hpp"

int main() {
    const std::string filename = "../data/Motor_Vehicle_Collisions.csv";
    const int RUN_TIMES = 10;

    
    Benchmark::compareLoadBenchmarks(filename, RUN_TIMES);

    
    CollisionDataset seqDataset;
    if (!seqDataset.loadFromCSV(filename)) {
        std::cerr << "Failed to load sequential dataset.\n";
        return 1;
    }
    CollisionDatasetParallel parDataset;
    if (!parDataset.loadFromCSV(filename)) {
        std::cerr << "Failed to load parallel dataset.\n";
        return 1;
    }

    
    std::string startDate = "01/01/2020";
    std::string endDate   = "12/31/2020";
    std::string borough   = "BROOKLYN";
    int zipCode   = 11201;
    int minInjuries       = 5;
    double minLat         = 40.5, maxLat = 40.9;
    double minLong        = -74.0, maxLong = -73.7;

    Benchmark::compareSearchByDateBenchmarks(seqDataset, parDataset, startDate, endDate, RUN_TIMES);
    Benchmark::compareSearchByBoroughBenchmarks(seqDataset, parDataset, borough, RUN_TIMES);
    Benchmark::compareSearchByZipCodeBenchmarks(seqDataset, parDataset, zipCode, RUN_TIMES);
    Benchmark::compareSearchByInjuryThresholdBenchmarks(seqDataset, parDataset, minInjuries, RUN_TIMES);
    Benchmark::compareSearchByLocationBoundsBenchmarks(seqDataset, parDataset, minLat, maxLat, minLong, maxLong, RUN_TIMES);

    Benchmark::compareLoadBenchmarksPhase3(filename, RUN_TIMES);

    CollisionDatasetParallelArrays phase3Dataset;
    if (!phase3Dataset.loadFromCSV(filename)) {
        std::cerr << "Failed to load Phase3 dataset.\n";
        return 1;
    }

    Benchmark::compareSearchByDateBenchmarksPhase3(phase3Dataset, startDate, endDate, RUN_TIMES);
    Benchmark::compareSearchByBoroughBenchmarksPhase3(phase3Dataset, borough, RUN_TIMES);
    Benchmark::compareSearchByZipCodeBenchmarksPhase3(phase3Dataset, zipCode, RUN_TIMES);
    Benchmark::compareSearchByInjuryThresholdBenchmarksPhase3(phase3Dataset, minInjuries, RUN_TIMES);
    Benchmark::compareSearchByLocationBoundsBenchmarksPhase3(phase3Dataset, minLat, maxLat, minLong, maxLong, RUN_TIMES);

    return 0;
}
