cmake_minimum_required(VERSION 3.0)

project(photo_rename)

include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(easyexif
    GIT_REPOSITORY https://github.com/mayanklahiri/easyexif.git
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(easyexif source_dir)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -ansi -std=c++11 -std=gnu++11 ")
add_library(exif STATIC ${source_dir}/exif.cpp)
include_directories(${source_dir})
add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} exif)
