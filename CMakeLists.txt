cmake_minimum_required(VERSION 2.8)

project(wingsofwar)

file(GLOB WOWSOURCES *.cpp)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 1.6 COMPONENTS system window graphics network audio REQUIRED)
find_package(TinyXML REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
include_directories(${TINYXML_INCLUDE_DIR})

set(CMAKE_CXX_FLAG "-g -Wall")

add_executable(wingsofwar ${WOWSOURCES})
target_link_libraries(wingsofwar ${SFML_LIBRARIES} ${TINYXML_LIBRARIES})

execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/assets
)
