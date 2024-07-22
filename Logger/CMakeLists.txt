cmake_minimum_required(VERSION 3.29)

set(CUR_DIR ${CMAKE_CURRENT_LIST_DIR})
file(GLOB MarketLogger_src
    "${CUR_DIR}/*.cpp"
)
include_directories(
    ${CUR_DIR}
)

message("MARKET_LOGGER")
message(${MarketLogger_src})
add_library(MarketLogger ${MarketLogger_src})