cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 11)

project(DeliveryRobot)

include_directories(${CMAKE_SOURCE_DIR}/inc)

set(SOURCE_FILES
	../test/test_ultrasonic.cpp
	../src/main.cpp
	../src/motor.cpp
  ../src/linetrack.cpp
	../src/ultrasonic.cpp
	../inc/motor.h
  ../inc/linetrack.h
	../inc/ultrasonic.h
)

find_library(pigpio_LIBRARY 
	NAMES libpigpio.so
	HINTS /usr/local/lib)
	
add_executable(DeliveryRobot ${SOURCE_FILES})
target_link_libraries(DeliveryRobot ${pigpio_LIBRARY})
