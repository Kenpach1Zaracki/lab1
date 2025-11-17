cmake_minimum_required(VERSION 3.14)
project(LabDataStructures)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опции для покрытия кода
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage -g -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Исходные файлы
set(SOURCES
    array.cpp
    slist.cpp
    dlist.cpp
    queue.cpp
    stack.cpp
    storage.cpp
    full_binary_tree.cpp
    hash_simple.cpp
)

# Тестовые файлы
set(TEST_SOURCES
  tests/test_full_binary_tree.cpp
  tests/test_array.cpp
  tests/test_slist.cpp
  tests/test_dlist.cpp
  tests/test_stack.cpp
  tests/test_queue.cpp
  tests/test_hash_simple.cpp
  tests/test_storage.cpp  # ДОБАВЛЕНО
)

# Создание исполняемого файла тестов
add_executable(run_tests ${SOURCES} ${TEST_SOURCES})

target_link_libraries(run_tests gtest_main)

include(GoogleTest)
gtest_discover_tests(run_tests)

# Цель для генерации отчета о покрытии
add_custom_target(coverage
    COMMAND ./run_tests
    COMMAND lcov --capture --directory . --output-file coverage.info
    COMMAND lcov --remove coverage.info "/usr/*" "*/build/*" "*/tests/*" "*/googletest/*" -o coverage_filtered.info
    COMMAND genhtml coverage_filtered.info --output-directory coverage_report
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Generating coverage report"
)