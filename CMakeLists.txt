cmake_minimum_required(VERSION 2.8.12)
project(TOR CXX)
add_executable(TOR
main.cpp
)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "-Wall -std=c++1z -stdlib=libc++")
SET_TARGET_PROPERTIES(TOR PROPERTIES OUTPUT_NAME "a.out")
target_link_libraries(TOR GL)
target_link_libraries(TOR GLU)
target_link_libraries(TOR GLEW)
target_link_libraries(TOR glfw)
target_link_libraries(TOR boost_system)
target_link_libraries(TOR boost_coroutine)
target_link_libraries(TOR pthread)
target_link_libraries(TOR cxxrt)

