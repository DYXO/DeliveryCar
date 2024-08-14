cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 11)

project(DeliveryRobot)

include_directories(${CMAKE_SOURCE_DIR}/inc)

set(SOURCE_FILES
	#../test/test_track.cpp
	#../test/gpiofix.cpp
	#../test/test_ultrasonic.cpp
	../test/test_serial.cpp
	#../test/test_playsound.cpp
	#../src/main.cpp
	../src/motor.cpp
	../src/ultrasonic.cpp
	../src/linetrack.cpp
	../src/playsound.cpp
	../src/serial.cpp
	../inc/motor.h
	../inc/ultrasonic.h
	../inc/linetrack.h
	../inc/playsound.h
	../inc/serial.h
)

find_library(pigpio_LIBRARY 
	NAMES libpigpio.so
	HINTS /usr/local/lib)

find_package(ALSA REQUIRED)
	
add_executable(DeliveryRobot ${SOURCE_FILES})
target_link_libraries(DeliveryRobot ${pigpio_LIBRARY})
target_link_libraries(DeliveryRobot ${ALSA_LIBRARIES})
target_include_directories(DeliveryRobot PRIVATE ${ALSA_INCLUDE_DIRS})