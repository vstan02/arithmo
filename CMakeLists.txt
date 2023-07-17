cmake_minimum_required(VERSION 3.17)
project(
	arithmo
	VERSION 1.0.0
	DESCRIPTION "A fast and simple-to-use library for math expressions processing"
	LANGUAGES C
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	set(CMAKE_C_STANDARD 11 CACHE STRING "The C standard to use")
	set(CMAKE_C_STANDARD_REQUIRED ON)
	set(CMAKE_C_EXTENSIONS ON)

	file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
	if(EXISTS "${LOC_PATH}")
		message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
	endif()

	include(CheckIPOSupported)
	check_ipo_supported(RESULT IPO_SUPPORTED)
	if(IPO_SUPPORTED)
		message(STATUS "Interprocedural optimization supported")
	else()
		message(STATUS "Interprocedural optimization not supported")
	endif()

	if(MSVC)
		add_compile_options(/W4 /WX)
	else()
		add_compile_options(-Wall -Wextra -pedantic -Werror)
	endif()
endif()

set(ARITHMO_PUBLIC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(ARITHMO_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(ARITHMO_EXAMPLE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/example)

file(GLOB ARITHMO_PUBLIC "${ARITHMO_PUBLIC_DIR}/*.h")
file(GLOB ARITHMO_SOURCES "${ARITHMO_SOURCE_DIR}/*.c")

add_library(arithmo ${ARITHMO_SOURCES})
target_include_directories(arithmo PUBLIC "${ARITHMO_PUBLIC_DIR}")
target_include_directories(arithmo PRIVATE "${ARITHMO_SOURCE_DIR}")
if(IPO_SUPPORTED)
  set_target_properties(conixpp PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

add_executable(example "${ARITHMO_EXAMPLE_DIR}/main.c")
target_include_directories(arithmo PUBLIC "${ARITHMO_PUBLIC_DIR}")
target_include_directories(arithmo PRIVATE "${ARITHMO_EXAMPLE_DIR}")
target_link_libraries(example arithmo)

install(FILES ${ARITHMO_PUBLIC} DESTINATION include)
install(TARGETS arithmo ARCHIVE DESTINATION lib)
