cmake_minimum_required(VERSION 3.10)
project(draw CXX)
include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

Set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG master
    GIT_SHALLOW ON
    GIT_PROGRESS
)
FetchContent_MakeAvailable(raylib)

file(GLOB SRC_FILES CONFIGURE_DEPENDS 
    source/*.cpp
    source/*.h
    source/*.hpp
    
)
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/source")
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/source")
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="../assets/")