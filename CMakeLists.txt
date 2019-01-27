cmake_minimum_required(VERSION 3.12.1)

project( WalletViewer
    VERSION 1.1.0.0
    DESCRIPTION "Project to show many flow in your pocket"
    HOMEPAGE_URL "https://github.com/zerg13new/WalletViewer"
    LANGUAGES CXX
    )

#Define build type
if(NOT CMAKE_BUILD_TYPE)
  message(FATAL_ERROR "No configuration information")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  #
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
  #
else()
  message(FATAL_ERROR "Unknown configuration")
endif()
message(STATUS "Current config is ${CMAKE_BUILD_TYPE}")

# Set platform
set(PLATFORM "UNIX")
if(UNIX)
  set(PLATFORM "UNIX")
elseif(WIN32)
  set(PLATFORM "WINDOWS")
else()
  message(FATAL_ERROR "Unknown platform for building.")
endif()

# Set architecture
set(ARCHITECTURE "x64")

set(CMAKE_BINARY_DIR "${CMAKE_BINARY_DIR}/bin/${PLATFORM}/${ARCHITECTURE}")

if(NOT EXISTS "${CMAKE_BINARY_DIR}")
  file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}")
  message(STATUS "Created ${CMAKE_BINARY_DIR}")
endif()

# Include auxilary tools
include(CMakeTools/add_library.cmake)

# Include libraryies
add_library_interface(zip SHARED)

# Main build
add_executable(walletviewer)
target_include_directories(walletviewer
    PUBLIC include ${zip_include})
target_link_libraries(walletviewer -lzip)
add_dependencies(walletviewer zip)

set( SRC
    src/algorithms.cpp
    src/content_reader.cpp
    src/ods_reader.cpp
    src/main.cpp
    )

target_sources( walletviewer 
    PRIVATE ${SRC}
    )

install( TARGETS walletviewer
    CONFIGURATIONS Release
    RUNTIME DESTINATION ${CMAKE_BINARY_DIR}
    )

install( TARGETS walletviewer
    CONFIGURATIONS Debug
    RUNTIME DESTINATION ${CMAKE_BINARY_DIR}
    )
