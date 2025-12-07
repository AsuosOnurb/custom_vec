cmake_minimum_required(VERSION 3.20)

project(MyVectorProject LANGUAGES CXX)


if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring for Debug build")
    
    add_compile_definitions(MYVECTOR_DEBUG_BOUNDS)
    message(STATUS "Bounds checking enabled")
endif()


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror=return-type)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(MYVECTOR_DEBUG_BOUNDS)
endif()


# Header-only library: use INTERFACE
add_library(myvector INTERFACE)
target_include_directories(myvector INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(myvector_demo src/main.cpp)
target_link_libraries(myvector_demo PRIVATE myvector)

# GoogleTest setup
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test target
add_executable(vector_tests tests/test_vector.cpp)
target_link_libraries(vector_tests PRIVATE myvector gtest_main)
target_include_directories(vector_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_test(NAME VectorTests COMMAND vector_tests)