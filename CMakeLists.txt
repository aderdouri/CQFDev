cmake_minimum_required(VERSION 3.10)

# Project name
project(CQFDev)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define source files for CppUnitTest
set(SOURCE_FILES_CPPUNITTEST
    CppUnitTest/Failure.cpp
    CppUnitTest/Main.cpp
    CppUnitTest/Test.h
    CppUnitTest/TestRegistry.cpp
    CppUnitTest/TestResult.cpp
    CppUnitTest/Failure.h
    CppUnitTest/Test.cpp
    CppUnitTest/TestHarness.h
    CppUnitTest/TestRegistry.h
    CppUnitTest/TestResult.h
)

set(SOURCE_FILES_MODULE_03
    Module_03/Matrix.h
    Module_03/Matrix.cpp
    Module_03/BlackScholes.h
    Module_03/MonteCarlo.cpp
    Module_03/BlackScholes.cpp
    Module_03/MonteCarlo.h
    Module_03/ExplicitFiniteDifference.h
    Module_03/ExplicitFiniteDifference.cpp
    Module_03/ExplicitFiniteDifferenceTest.cpp
    Module_03/MonteCarloTest.cpp
)

# ExplicitFiniteDifference executable
add_executable (explicitFiniteDifference ${SOURCE_FILES_CPPUNITTEST} ${SOURCE_FILES_MODULE_03})