cmake_minimum_required(VERSION 3.29)

set(CUR_DIR ${CMAKE_CURRENT_LIST_DIR})
file(GLOB Collector_src
    "${CUR_DIR}/*.cpp"
)
include_directories(
    ${CUR_DIR}
)

message("MARKET_API")
message(${Collector_src})
add_library(Collector ${Collector_src})