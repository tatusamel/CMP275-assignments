cmake_minimum_required(VERSION 3.10)

project(mini)
set(CMAKE_CXX_STANDARD 14)

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
