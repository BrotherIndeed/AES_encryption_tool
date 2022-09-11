cmake_minimum_required(VERSION 3.0)

project(copy)

message(${FILE})

add_executable(${PROJECT_NAME} ${FILE})

find_package(OpenSSL REQUIRED)

target_link_libraries(${PROJECT_NAME} OpenSSL::Crypto)