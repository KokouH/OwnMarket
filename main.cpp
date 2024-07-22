#include <Inventory.hpp>
#include <Clothes.hpp>
#include <Json.hpp>
#include <algorithm>
#include <iostream>
#include <ItemNames.hpp>
#include <Logger.hpp>

int main()
{
    ConsoleLogger logger;
    pClothes pitem = std::make_shared<Clothes>(
        Clothes(10, (char *)ItemNames::HatDragonLore)
    );
    
    logger.putMessage( LogMessage{
        MessageTypes::INFO,
        JsonConverter().getJson(pitem) 
    });

    logger.popAllMessages();
    // std::cout << JsonConverter().getJson(pitem) << std::endl;

    return (0);
}