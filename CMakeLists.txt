cmake_minimum_required(VERSION 3.10)
project(MatrixCalculator)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)


add_executable(matrix_tests 
    tests/test_matrix.cpp
    src/matrix.cpp
    src/decompositions.cpp
    src/solvers.cpp
)

add_executable(matrix_app 
    app/main.cpp
    src/matrix.cpp
    src/decompositions.cpp
    src/solvers.cpp
)

enable_testing()
add_test(NAME MatrixTests COMMAND matrix_tests)
target_link_libraries(matrix_tests matrix_lib)
