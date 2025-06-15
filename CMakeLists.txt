cmake_minimum_required(VERSION 3.14)

project(MyProject VERSION 1.0 LANGUAGES C CXX)

# Set default build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# C/C++ standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Platform selection (e.g., -DPLATFORM=stm32f4)
set(PLATFORM "" CACHE STRING "Target platform (e.g. stm32f4, rp2040, etc.)")

# Toolchain selection hint (optional)
set(TOOLCHAIN "" CACHE STRING "Toolchain file path relative to tools/ (optional)")

# Platform-specific source dir
if(PLATFORM)
  message(STATUS "Target platform: ${PLATFORM}")
  add_definitions(-DPLATFORM_${PLATFORM})
  set(PLATFORM_SRC "src/platform/${PLATFORM}")
else()
  message(WARNING "No platform specified; building default/native only")
endif()

# Source files
file(GLOB_RECURSE SOURCES
  src/*.c
  src/*.cpp
)

# Add platform-specific files
if(EXISTS "${CMAKE_SOURCE_DIR}/${PLATFORM_SRC}")
  file(GLOB_RECURSE PLATFORM_SOURCES
    ${PLATFORM_SRC}/*.c
    ${PLATFORM_SRC}/*.cpp
  )
  list(APPEND SOURCES ${PLATFORM_SOURCES})
else()
  if(PLATFORM)
    message(FATAL_ERROR "Platform source directory not found: ${PLATFORM_SRC}")
  endif()
endif()

# Include directories
include_directories(
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}${PLATFORM_SRC}       # platform headers
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Output location
set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Install rule
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
