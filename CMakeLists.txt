cmake_minimum_required(VERSION 3.0.0)
project(WebcamToText VERSION 0.1.0)

include(CTest)
enable_testing()

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )


add_executable(WebcamToText main.cpp)
find_package(raylib CONFIG REQUIRED)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(WebcamToText PRIVATE raylib)
include_directories(${OpenCV_INCLUDE_DIRS})