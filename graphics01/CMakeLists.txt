cmake_minimum_required(VERSION 3.13)
project(graphics01)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_INCLUDE ./include)

include_directories(${PROJECT_INCLUDE})

add_executable(graphics01 src/main.cpp)

target_link_libraries(graphics01 GLEW)
target_link_libraries(graphics01 glfw3)
target_link_libraries(graphics01 GL)
target_link_libraries(graphics01 X11)
target_link_libraries(graphics01 pthread)
target_link_libraries(graphics01 Xrandr)
target_link_libraries(graphics01 Xi)
target_link_libraries(graphics01 Xxf86vm)
target_link_libraries(graphics01 Xinerama)
target_link_libraries(graphics01 Xcursor)
target_link_libraries(graphics01 rt)
target_link_libraries(graphics01 m)
target_link_libraries(graphics01 dl)