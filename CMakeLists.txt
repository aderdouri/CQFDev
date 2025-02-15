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

set(SOURCE_FILES_MATRIX
    Matrix/Matrix.h
    Matrix/Matrix.cpp
)

set(SOURCE_FILES_MODULE_03
    Module_03/BlackScholes.h
    Module_03/MonteCarlo.cpp
    Module_03/BlackScholes.cpp
    Module_03/ExplicitFiniteDifference.h
    Module_03/ExplicitFiniteDifference.cpp
    Module_03/ExplicitFiniteDifferenceTest.cpp
    Module_03/MonteCarlo.h
    Module_03/MonteCarloTest.cpp
)
set(SOURCE_FILES_MODULE_04
    Module_04/BondTest.cpp
    Module_04/HJM.cpp
    Module_04/HJM.h
    Module_04/HJMTest.cpp
)

set(SOURCE_FILES_MODULE_05
    Module_05/curve.h
    Module_05/curve.cpp
    Module_05/cdsBootstrappingTest.cpp
)
# ExplicitFiniteDifference executable
add_executable (explicitFiniteDifference ${SOURCE_FILES_CPPUNITTEST} ${SOURCE_FILES_MATRIX} ${SOURCE_FILES_MODULE_03})

# HJM model executable
add_executable (hjm ${SOURCE_FILES_CPPUNITTEST} ${SOURCE_FILES_MATRIX} ${SOURCE_FILES_MODULE_04})

# CDS Bootstrapping executable
add_executable (cdsBootstrapping ${SOURCE_FILES_CPPUNITTEST} ${SOURCE_FILES_MODULE_05})
