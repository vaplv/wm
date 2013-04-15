cmake_minimum_required(VERSION 2.6)
project(wm-glfw C)

if(NOT CMAKE_COMPILER_IS_GNUCC)
  message(FATAL_ERROR "Unsupported compiler.")
endif(NOT CMAKE_COMPILER_IS_GNUCC)

set(CMAKE_DEBUG_POSTFIX "-dbg")

set(CMAKE_C_FLAGS "-pedantic -std=c99 -Wall -Wextra -Wcast-align -Wmissing-declarations -Wmissing-prototypes -fvisibility=hidden -fstrict-aliasing -Wl,-z,defs -Wconversion")
set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

################################################################################
# Check dependencies
################################################################################
macro(check_dependency lib header)
  find_path(${lib}_INCLUDE_DIR ${header})
  find_library(${lib}_LIBRARY ${lib})

  if(NOT ${lib}_INCLUDE_DIR OR NOT ${lib}_LIBRARY)
    message(FATAL_ERROR "Can't find ${lib} header/library")
  else()
    message(STATUS "${lib} found: ${${lib}_LIBRARY}")
  endif()

  include_directories(${${lib}_INCLUDE_DIR})
endmacro()

check_dependency(glfw GL/glfw.h)
check_dependency(sl sl/sl.h)
check_dependency(snlsys snlsys/snlsys.h)

################################################################################
# Define targets
################################################################################
add_definitions(-DWM_BUILD_SHARED_LIBRARY)

file(GLOB WM_GLFW_FILES *.c)

add_library(wm-glfw SHARED ${WM_GLFW_FILES})
target_link_libraries(wm-glfw ${glfw_LIBRARY} ${sl_LIBRARY} ${snlsys_LIBRARY})
set_target_properties(wm-glfw PROPERTIES DEFINE_SYMBOL WM_SHARED_BUILD)

################################################################################
# Define output & install directories 
################################################################################
install(TARGETS wm-glfw LIBRARY DESTINATION lib)
