cmake_minimum_required(VERSION 3.29)

set(CUR_DIR ${CMAKE_CURRENT_LIST_DIR})
file(GLOB MarketAPI_src
    "${CUR_DIR}/*.cpp")
include_directories(${CUR_DIR})
add_library(MarketAPI ${MarketAPI_src})