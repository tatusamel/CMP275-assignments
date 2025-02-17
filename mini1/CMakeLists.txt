cmake_minimum_required(VERSION 3.10)

project(mini)
set(CMAKE_CXX_STANDARD 14)

# Provide hints for OpenMP
set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp")
set(OpenMP_C_LIB_NAMES "omp")
set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp")
set(OpenMP_CXX_LIB_NAMES "omp")
# Explicitly set the OpenMP library path (adjust the version/path as needed)
set(OpenMP_omp_LIBRARY "/opt/homebrew/opt/libomp/lib/libomp.dylib")

# Add Homebrew's libomp include and lib directories
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I/opt/homebrew/opt/libomp/include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/opt/homebrew/opt/libomp/include")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/opt/homebrew/opt/libomp/lib -lomp")



# Find OpenMP package
find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# source files
set(SOURCES
    src/main.cpp
    src/CSVParser.cpp
    src/CollisionRecord.cpp
    src/CollisionDataset.cpp
)

# Create the executable
add_executable(mini ${SOURCES})
