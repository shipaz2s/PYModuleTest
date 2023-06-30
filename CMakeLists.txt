cmake_minimum_required(VERSION 3.24)
project(PYModule VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR)

add_library(PYModule SHARED module.c class.c class_py.c)
target_include_directories(PYModule PUBLIC ${PYTHON_DIR}/include)
target_link_directories(PYModule PUBLIC ${PYTHON_DIR}/libs)
target_link_libraries(PYModule PUBLIC python${PY_VERSION})
target_compile_definitions(PYModule PUBLIC MS_WIN64)

add_executable(test test.c)

target_link_directories(test PUBLIC ${PYTHON_DIR}/libs)
target_link_libraries(test PUBLIC PYModule python${PY_VERSION})
target_include_directories(test PUBLIC ${PYTHON_DIR}/include)
add_custom_command(
	TARGET PYModule POST_BUILD
	COMMAND ${PYTHON_DIR}/python.exe ARGS "setup.py" "install"
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)