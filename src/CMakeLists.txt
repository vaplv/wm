cmake_minimum_required(VERSION 2.6)
project(wm C)

file(GLOB WM_FILES_INC *.h)
install(FILES ${WM_FILES_INC} DESTINATION include/wm)

add_subdirectory(glfw)

