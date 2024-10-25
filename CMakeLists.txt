cmake_minimum_required(VERSION 3.10)

# Project name
project(Assignment)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the path where curl.h is located (only necessary if not found automatically)
include_directories(C:\Program Files\curl-8.10.1_7-win64-mingw\include\curl)

# Add executable
add_executable(Assignment main.cpp deribit_api.cpp http_client.cpp)

# Link cURL
find_package(CURL REQUIRED)
target_link_libraries(Assignment CURL::libcurl)
