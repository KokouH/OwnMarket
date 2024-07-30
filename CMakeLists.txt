cmake_minimum_required(VERSION 3.29)
project(Market)

set(CMAKE_CXX_STANDARD 20)
set(HTTP_PARSER_HEADER "/home/almaz/projects/cppLibs/httpparser-master/src")
set(NLOHMANN_HEADERS "/home/almaz/projects/cppLibs/json/include")

# find_package( Boost )
link_libraries( pthread )

set(CURRENT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(USE_MARKET_API ON)

add_executable(Market main.cpp)

add_subdirectory(Collector)
add_subdirectory(Inventory)
add_subdirectory(Items)
add_subdirectory(Logger)
if (USE_MARKET_API)
    include_directories(MarketApi)
    add_subdirectory(MarketApi)
    target_include_directories(MarketAPI 
        PUBLIC Inventory
        PUBLIC Logger
        PUBLIC Collector
        PUBLIC Items
        PUBLIC ${HTTP_PARSER_HEADER}
        
    )
    target_link_libraries(Market MarketAPI)
endif()

include_directories(
    Inventory
    Items
    Collector
    ${NLOHMANN_HEADERS}
)

target_include_directories(ItemsPacket PUBLIC Inventory)
target_include_directories(Collector PUBLIC Inventory)
target_include_directories(Collector PUBLIC Items)

target_link_libraries(Market Collector)
target_link_libraries(Market InventoryProject)
target_link_libraries(Market ItemsPacket)
target_link_libraries(Market MarketLogger)
