cmake_minimum_required(VERSION 3.16)

project(UrbanPulse VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(UrbanPulse
    src/main.cpp
    src/MetroController.cpp
    src/MetroGraph.cpp
    src/Routing.cpp
    src/Infrastructure.cpp
    src/ExpressNetwork.cpp
    src/BellmanFord.cpp
    src/MetroOperations.cpp
    src/NetworkAnalysis.cpp
    src/Data.cpp
)

target_include_directories(UrbanPulse PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

set_target_properties(UrbanPulse PROPERTIES
    OUTPUT_NAME "metro"
)

if(MSVC)
    target_compile_options(UrbanPulse PRIVATE /W4)
else()
    target_compile_options(UrbanPulse PRIVATE -Wall -Wextra -Wpedantic)
endif()