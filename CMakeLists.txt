cmake_minimum_required(VERSION 3.9)
project(AppIO_RPi_GPIO VERSION 0.1 DESCRIPTION "Raspberry pi IO over ZMQ")
include(GNUInstallDirs)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_REQUIRED_FLAGS -std=c++17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17 -pthread -lstdc++fs -static-libgcc -static-libstdc++")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/config")

#set(BOOST_INCLUDEDIR /usr/lib/arm-linux-gnueabihf/include)
#set(BOOST_LIBRARYDIR /usr/lib/arm-linux-gnueabihf/lib)
find_package(Boost 1.65 COMPONENTS system date_time thread chrono regex random program_options REQUIRED)
find_package(ZeroMQ 4.0 REQUIRED)
find_package(Azmq 1.0 REQUIRED)
find_package(pigpio REQUIRED)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)

include_directories(${Boost_INCLUDE_DIRS}
        ${ZeroMQ_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}
        ${Azmq_INCLUDE_DIRS}
        ${pigpio_INCLUDE_DIR})

add_executable(AppIO_RPi_GPIO main.cpp GPIO.cpp GPIO.hpp IO.cpp IO.hpp)

target_link_libraries(AppIO_RPi_GPIO ${Boost_LIBRARIES}
        ${ZeroMQ_LIBRARY}
        ${Azmq_LIBRARIES}
        ${pigpio_LIBRARY})