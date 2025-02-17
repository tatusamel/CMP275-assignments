cmake_minimum_required(VERSION 3.10)

project(mini)
set(CMAKE_CXX_STANDARD 14)

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
