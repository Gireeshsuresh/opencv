cmake_minimum_required(VERSION 2.80)
project( Smoothing_basic )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( Smoothing_basic basic_smooth.cpp )
target_link_libraries( Smoothing_basic ${OpenCV_LIBS} )
