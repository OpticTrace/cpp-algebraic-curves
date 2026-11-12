cmake_minimum_required(VERSION 3.14)
project(algebraic-curves LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
    add_compile_options(/W4) # Для Windows (Visual Studio)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # oтключаем gnu-расширения для кроссплатформенности


add_library(math_lib STATIC
    src/Monom.cpp
    src/Polynomial.cpp
    src/Multiplicity.cpp
)

# public означает, что заголовки из include/ будут видны всем, кто линкует эту библиотеку
target_include_directories(math_lib PUBLIC include)


add_executable(app app/main.cpp)
target_link_libraries(app PRIVATE math_lib)


include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(test_app tests/MultiplicityTest.cpp)

target_link_libraries(test_app PRIVATE math_lib gtest_main)

include(GoogleTest)
gtest_discover_tests(test_app)