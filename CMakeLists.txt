# CMake for Wing-of-War
cmake_minimum_required(VERSION 2.8)

# Project Information
project(wingsofwar)
set(wingsofwar_VERSION_MAJOR 0)
set(wingsofwar_VERSION_MINOR 5)

# Fetch Wing of War Source Files
file(GLOB WOWSOURCES src/*.cpp)

# Fetch Wing of War Test Files
file(GLOB WOWTEST_FILE test/*.cpp)

# Add local cmake_modules folder in CMake serach path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Search for required libraries 
find_package(SFML 1.6 COMPONENTS system window graphics network audio REQUIRED)
find_package(TinyXML REQUIRED)

# Include all include directories
include_directories(${SFML_INCLUDE_DIR})
include_directories(${TINYXML_INCLUDE_DIR})
include_directories("${CMAKE_SOURCE_DIR}/include")

# TODO: Build in Debug-Mode. Should be improved in the final release.
set(CMAKE_CXX_FLAG "-g -Wall")

# TODO: Added for allowing profiling
# set(CMAKE_EXE_LINKER_FLAGS "-g -pg")

# Build Executable
add_executable(wingsofwar ${WOWSOURCES})

# Link all the libraries!
target_link_libraries(wingsofwar ${SFML_LIBRARIES} ${TINYXML_LIBRARIES})

# Post build operation.
# Copy required assets and shader from source to build.
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/assets
)

execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders
    ${CMAKE_BINARY_DIR}/shaders
)

# TODO: Experimental: CPack Support!
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${wingsofwar_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${wingsofwar_VERSION_MINOR}")
include(CPack)
