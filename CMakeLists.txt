# CMake for Wing-of-War
cmake_minimum_required(VERSION 2.8)

# Project Information
project(wingsofwar)
set(wingsofwar_VERSION_MAJOR 0)
set(wingsofwar_VERSION_MINOR 5)

# Fetch Wing of War Source Files
file(GLOB_RECURSE WOWSOURCES src/*.cpp)

# Fetch Wing of War Test Files
file(GLOB_RECURSE WOWTEST_FILE test/*.cpp)

# Add local cmake_modules folder in CMake serach path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Search for required libraries 
find_package(SFML 1.6 COMPONENTS system window graphics network audio REQUIRED)
find_package(TinyXML REQUIRED)
find_package(LibConfig++ REQUIRED)

# Include all include directories
include_directories(${SFML_INCLUDE_DIR})
include_directories(${LIBCONFIG_INCLUDE_DIR})
include_directories(${TCLAP_INCLUDE_DIR})
include_directories(${TINYXML_INCLUDE_DIR})
include_directories("${CMAKE_SOURCE_DIR}/include")

# Build Executable
add_executable(wingsofwar ${WOWSOURCES})

# Link all the libraries!
target_link_libraries(wingsofwar ${SFML_LIBRARIES} ${TINYXML_LIBRARIES} ${LIBCONFIGPP_LIBRARIES})

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

execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/src/conf
    ${CMAKE_BINARY_DIR}/conf
)

# TODO: Experimental: CPack Support!
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${wingsofwar_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${wingsofwar_VERSION_MINOR}")
include(CPack)
