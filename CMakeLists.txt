cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME cmake-test)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic-errors")
set(CMAKE_VERBOSE_MAKEFILE on)

project(${PROJECT_NAME})

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

include(FindPkgConfig)
pkg_search_module(SDL2 required sdl2)
pkg_search_module(SDL2IMAGE required SDL2_image>=2.0.0)
pkg_search_module(SDL2TTF required SDL2_ttf)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${PROJECT_SOURCE_DIR}/includes
    ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})
file(COPY assets DESTINATION "${CMAKE_BINARY_DIR}")

