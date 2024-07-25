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
        Clothes((char *)ItemNames::HatDragonLore, 0)
    );
    pInventory inv = std::make_shared<Inventory>();
    
    logger.putMessage( LogMessage{
        MessageTypes::INFO,
        JsonConverter().getJson(pitem) 
    });
    inv->addItem(pitem);
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

    return (0);
}