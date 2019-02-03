cmake_minimum_required(VERSION 3.9)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_PRIVATE_HEADERS "can we use QtQuickTemplates2 private headers" FALSE)

add_subdirectory(backbone)
add_subdirectory(app)
