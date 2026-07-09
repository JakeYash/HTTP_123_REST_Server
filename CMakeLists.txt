cmake_minimum_required(VERSION 3.16)
project(RestClient VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QUIC_BUILD_SHARED ON CACHE BOOL "" FORCE)
set(QUIC_TLS "openssl" CACHE STRING "" FORCE)
add_subdirectory(third_party/msquic)

add_executable(rest_server
    src/main.cpp
)
target_link_libraries(rest_client PRIVATE msquic)
target_include_directories(rest_client PRIVATE third_party/msquic/src/inc)
