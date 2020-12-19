cmake_minimum_required(VERSION 3.17)
project(AssemblyLineSimulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(AssemblyLineSimulator
        tests/test.cpp
        Utilities.cpp Utilities.h
        Station.cpp Station.h
        CustomerOrder.cpp CustomerOrder.h
        Workstation.cpp Workstation.h
        LineManager.cpp LineManager.h
        )
