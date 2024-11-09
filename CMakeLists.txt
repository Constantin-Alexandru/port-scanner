cmake_minimum_required(VERSION 3.30)
project(ac_scanner VERSION 0.1.5)

# Enable only when in development mode
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES src/*.cpp src/*/*.cpp src/*/*/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/external
    ${CMAKE_CURRENT_SOURCE_DIR}/include/port-scanner
)

target_compile_options(${PROJECT_NAME}
  PRIVATE
  -Wall -Wextra -Werror -Wpedantic -O3 -pthread
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
