cmake_minimum_required(VERSION 3.29)

project(mytree1 VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} mytree1.cpp)

add_library(treeh mytree1.h)
set_target_properties(treeh PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(Tree_Test)


#add_subdirectory(TreeLib)
#target_link_libraries(${PROJECT_NAME} TreeLib)