cmake_minimum_required(VERSION 3.18)
project(facepga LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Torch first-class import
find_package(Torch REQUIRED)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES
    "${SRC_DIR}/*.c"
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/*.cc"
    "${SRC_DIR}/*.cxx"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${SRC_DIR}
    ${TORCH_INCLUDE_DIRS}
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra -O3
    ${TORCH_CXX_FLAGS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${TORCH_LIBRARIES}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)