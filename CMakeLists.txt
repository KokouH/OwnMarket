cmake_minimum_required(VERSION 3.29)
project(Market)

set(CURRENT_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(Inventory)
include_directories(Inventory Items)
add_executable(Market main.cpp)
target_link_libraries(Market InventoryProject)
