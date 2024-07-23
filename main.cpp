#include <Inventory.hpp>
#include <Clothes.hpp>
#include <Server.hpp>
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
    pInventory inv = std::make_shared<Inventory>();
    
    logger.putMessage( LogMessage{
        MessageTypes::INFO,
        JsonConverter().getJson(pitem) 
    });
    inv->addItem(pitem);
    logger.putMessage( LogMessage{
        MessageTypes::INFO,
        JsonConverter().getJson(inv)
    });

    logger.popAllMessages();

    std::cout << "===============" << std::endl;

    Server server(logger);

    server.start_acceptor();
    server.start_session_handler();

    server.join();
    // std::cout << JsonConverter().getJson(pitem) << std::endl;

    return (0);
}