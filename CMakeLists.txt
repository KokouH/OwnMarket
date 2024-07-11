cmake_minimum_required(VERSION 3.29)
project(Market)

find_package( Boost )

set(CURRENT_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(Inventory)
add_subdirectory(MarketApi)
add_subdirectory(Items)

include_directories(Inventory Items MarketApi)
add_executable(Market main.cpp)

target_include_directories(MarketAPI PUBLIC Inventory)
target_include_directories(ItemsPacket PUBLIC Inventory)

target_link_libraries(Market InventoryProject)
target_link_libraries(Market MarketAPI)
target_link_libraries(Market ItemsPacket)
