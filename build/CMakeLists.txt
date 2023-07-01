cmake_minimum_required(VERSION 3.7)

project(exec)

find_package(SDL2 REQUIRED)

set(CMAKE_C_FLAGS "-Wall -Werror -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-ggdb3 -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/../src/")
set(HEADER_DIR "${PROJECT_SOURCE_DIR}/../include/")
set(LIB_DIR "${PROJECT_SOURCE_DIR}/../lib/")
set(EXEC_DIR "${PROJECT_SOURCE_DIR}/../bin/apps/")
set(INCLUDE_LIB "${SDL2_INCLUDE_DIRS}")
set(LINK_LIB "${SDL2_LIBRARIES} -L${LIB_DIR}SDL_image/ -lSDL2_image")

file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.c")
file(GLOB_RECURSE HEADER_FILES "${HEADER_DIR}/*.h" "${LIB_DIR}/*.h")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADER_DIR} ${LIB_DIR})
include_directories(${INCLUDE_LIB})
target_link_libraries(${PROJECT_NAME} ${LINK_LIB})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${EXEC_DIR})
