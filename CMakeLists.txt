cmake_minimum_required(VERSION 3.17)
project(firework)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/data)
SET(CMAKE_CXX_FLAGS "-pthread")
set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(usbrelay)
add_subdirectory(usbrelay)

add_executable(firework main.cpp ShootFlower.cpp FireworksFactory.cpp RelayUtils.cpp)
target_link_libraries(firework ${OpenCV_LIBS})
target_link_libraries(firework usbrelay)
