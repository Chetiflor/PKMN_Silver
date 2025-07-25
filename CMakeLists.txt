#CMakeLists.txt to build project using cmake
#run $cmake CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

project(pgm)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories("projet/src/" "projet/src/states/")

file(
GLOB_RECURSE
source_files
projet/src/*.[cht]pp
projet/src/states/*.[cht]pp
)

set(CMAKE_BUILD_TYPE Debug)

if (WIN32)
  set(LINK_FLAGS )
elseif (APPLE)
  set(LINK_FLAGS )
elseif (UNIX)
  set(LINK_FLAGS -lm -ldl -fopenmp)
  add_definitions(-O2 -Wno-comment -Wno-unused-parameter -Wno-unused-function -Wno-unused-variable -DCORRECTION -DWITH_BACKTRACE)
endif ()




find_package(SDL2 REQUIRED)
include_directories(pgm ${SDL2_INCLUDE_DIRS})

add_executable(pgm ${source_files})
target_link_libraries(pgm ${SDL2_LIBRARIES})