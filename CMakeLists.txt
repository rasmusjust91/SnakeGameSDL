cmake_minimum_required(VERSION 3.0.0)
project(MOBA VERSION 0.1.0)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(COPY resources/ DESTINATION ${PROJECT_BINARY_DIR}/resources)

add_executable(${PROJECT_NAME} main.cpp game.cpp objects.cpp)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
