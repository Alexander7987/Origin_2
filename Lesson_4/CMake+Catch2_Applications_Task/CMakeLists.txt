cmake_minimum_required(VERSION 3.22.0)
project(my_project)
add_executable(MyProject main.cpp factorial.cpp factorial.h)

add_subdirectory(../Catch2 Catch2-build)
add_executable(My_project_test test_main.cpp factorial.cpp factorial.h)
target_link_libraries(My_project_test PRIVATE Catch2::Catch2)