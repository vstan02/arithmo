cmake_minimum_required(VERSION 3.17)
project(arithmo C)

set(CMAKE_C_STANDARD 11)
set(ARITHMO_PUBLIC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(ARITHMO_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB ARITHMO_PUBLIC "${ARITHMO_PUBLIC_DIR}/*.h")
file(GLOB ARITHMO_SOURCES "${ARITHMO_SOURCE_DIR}/*.c")

include_directories(${ARITHMO_PUBLIC_DIR})

find_package(PkgConfig)
pkg_check_modules(GLIB REQUIRED glib-2.0)
include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})
add_definitions(${GLIB_CFLAGS_OTHER})

add_library(arithmo ${ARITHMO_SOURCES})

install(FILES ${ARITHMO_PUBLIC} DESTINATION include)
install(TARGETS arithmo ARCHIVE DESTINATION lib)
