cmake_minimum_required(VERSION 3.0.2)

project(opengl_core)

find_package(OpenGL)

add_subdirectory(${CMAKE_SOURCE_DIR}/../tests/build ${CMAKE_CURRENT_BINARY_DIR}/tests)

include_directories(${CMAKE_SOURCE_DIR}/../includes)
include_directories(${CMAKE_SOURCE_DIR}/../)

set(src ${CMAKE_SOURCE_DIR}/../declspec.h
  ${CMAKE_SOURCE_DIR}/../src/extension_checker.cpp
  ${CMAKE_SOURCE_DIR}/../src/win32_error_handler.cpp
  ${CMAKE_SOURCE_DIR}/../src/win32_fb_config.cpp
  ${CMAKE_SOURCE_DIR}/../src/win32_gl_functions.cpp
  ${CMAKE_SOURCE_DIR}/../src/win32_hinstance.cpp
  ${CMAKE_SOURCE_DIR}/../src/win32_render_context.cpp
  ${CMAKE_SOURCE_DIR}/../src/win32_render_system.cpp
  ${CMAKE_SOURCE_DIR}/../src/win32_render_window.cpp
  ${CMAKE_SOURCE_DIR}/../src/win32_symbol_loader.cpp
  ${CMAKE_SOURCE_DIR}/../src/win32_wndproc.cpp
  ${CMAKE_SOURCE_DIR}/../includes/core/concurrent_queue.h
  ${CMAKE_SOURCE_DIR}/../includes/core/extension_checker.h
  ${CMAKE_SOURCE_DIR}/../includes/core/fb_config.h
  ${CMAKE_SOURCE_DIR}/../includes/core/gl_functions.h
  ${CMAKE_SOURCE_DIR}/../includes/core/memory_leaks.h
  ${CMAKE_SOURCE_DIR}/../includes/core/non_copyable.h
  ${CMAKE_SOURCE_DIR}/../includes/core/platform.h
  ${CMAKE_SOURCE_DIR}/../includes/core/render_context.h
  ${CMAKE_SOURCE_DIR}/../includes/core/render_system.h
  ${CMAKE_SOURCE_DIR}/../includes/core/render_window.h
  ${CMAKE_SOURCE_DIR}/../includes/core/symbol_loader.h
  ${CMAKE_SOURCE_DIR}/../includes/core/win32_error_handler.h
  ${CMAKE_SOURCE_DIR}/../includes/core/win32_hinstance.h
  ${CMAKE_SOURCE_DIR}/../includes/core/win32_wndproc.h)

include(CheckCXXCompilerFlag)

check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

add_library(opengl_core SHARED ${src})
add_library(opengl_core_static STATIC ${src})

target_link_libraries(opengl_core ${OPENGL_gl_LIBRARY})
target_link_libraries(opengl_core_static ${OPENGL_gl_LIBRARY})

add_definitions(-DUNICODE -D_UNICODE)
  
enable_testing()
add_test(NAME tests COMMAND core_tests)
