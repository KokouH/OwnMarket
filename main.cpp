#include <InventoryCollector.hpp>
#include <Server.hpp>
#include <Json.hpp>
#include <algorithm>
#include <iostream>
#include <Logger.hpp>

int main()
{
    JsonConverter converter;
    ConsoleLogger logger;
    InventoryGenerator inv_gen;
    ItemsGenerator item_gen;
    InventoryCollector collector(item_gen, inv_gen);
    Server server(logger, collector);
    
    unsigned long inv;
    unsigned long item;

    inv = collector.createInventory();
    item = collector.createItem(ItemType::CLOTHES);

    collector.getInventoryById(inv)->addItem(
        collector.getItemById(item)
    );

    logger.putMessage(
        LogMessage{
            MessageTypes::INFO,
            converter.getJson(
                collector.getInventoryById(inv)
            )
        }
    );

    logger.putMessage(
        LogMessage{
            MessageTypes::INFO,
            "Try start server."
        }
    );
    logger.popAllMessages();

    server.start_acceptor();
    server.start_session_handler();

    logger.popAllMessages();
    server.join();

    return (0);
}