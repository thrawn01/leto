# ----------------------------------------------------------------
# Derrick Wippler 2011 (thrawn01@gmail.com) 
# ----------------------------------------------------------------
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(LETO)

# Add Option to compile with shared/static libraries 
OPTION(BUILD_SHARED "Build projects with shared libs" ON)
IF(BUILD_SHARED)
    SET(BUILD_SHARED_LIBS 1)
ENDIF(BUILD_SHARED)

# Add Option to compile with Optimize flags
OPTION(WITH_OPTIMIZE "Build projects with Optimize flags" OFF)
IF(WITH_OPTIMIZE)
    SET(CMAKE_CXX_FLAGS "-O3")
ENDIF(WITH_OPTIMIZE)

# Add Option to compile with debug flags
OPTION(WITH_DEBUG "Build projects with debug flags" ON)
IF(WITH_DEBUG)
    SET(CMAKE_BUILD_TYPE Debug)
    SET(CMAKE_CXX_FLAGS_DEBUG "-g3")
ENDIF(WITH_DEBUG)

# CMake Modules for BSG build system
SET(CMAKE_MODULE_PATH ${LETO_SOURCE_DIR}/cmake)

# All executables go into /bin
SET(EXECUTABLE_OUTPUT_PATH ${LETO_SOURCE_DIR}/bin)

# All Libraries go into /lib
SET(LIBRARY_OUTPUT_PATH ${LETO_SOURCE_DIR}/lib)

# Find Packages Needed for Testing
FIND_PACKAGE(PythonInterp)
FIND_PACKAGE(Perl)
FIND_PACKAGE(Boost COMPONENTS serialization )

# Set to svn so Ctest doesn't 
# complain and confuse users
SET(UPDATE_TYPE "svn")
SET(CXXTEST_BUILD_DIR ${LETO_SOURCE_DIR}/Testing)

# Include CTest framework in the makefiles
INCLUDE (CTest)

# Include Macros for adding CxxTests
INCLUDE (CxxTestMacros)

# So the cxxtest headers can find the .h files
INCLUDE_DIRECTORIES(src)

# Add projects to the build system here.
ADD_SUBDIRECTORY(src)
