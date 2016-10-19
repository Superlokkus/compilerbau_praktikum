cmake_minimum_required (VERSION 3.0)
project (Compilerbau_Praktikum)

set (PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})


include_directories("${PROJECT_BINARY_DIR}")

set (CORE_SOURCE_FILES
${PROJECT_SOURCE_DIR}/compiler.cpp
${PROJECT_SOURCE_DIR}/compiler.hpp
)

add_executable(praktikum_cli ${PROJECT_SOURCE_DIR}/cli.cpp ${CORE_SOURCE_FILES})

set_property(TARGET praktikum_cli PROPERTY LINKER_LANGUAGE CXX)
set_property(TARGET praktikum_cli PROPERTY CXX_STANDARD 11)


#enable_testing()
#add_subdirectory(test)