cmake_minimum_required(VERSION 3.14)
project(algebraic-curves)

set(CMAKE_CXX_STANDARD 17)

# основная программа
add_executable(app
    cpp/main.cpp
    cpp/Monom.cpp
    cpp/Polynomial.cpp
    cpp/Multiplicity.cpp
)
# !!!!! указываем, где искать заголовочные файлы для основной программы
target_include_directories(app PRIVATE cpp)

# подкл GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# предотвращаем переопределение настроек компилятора
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# тесты
enable_testing()
add_executable(test_app
    tests/MultiplicityTest.cpp
    cpp/Monom.cpp
    cpp/Polynomial.cpp
    cpp/Multiplicity.cpp
)
# !!!!! указываем, где искать заголовочные файлы для тестов
target_include_directories(test_app PRIVATE cpp) 

target_link_libraries(test_app gtest_main)
include(GoogleTest)
gtest_discover_tests(test_app)