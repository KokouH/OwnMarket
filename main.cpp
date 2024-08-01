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
    pInventory invent;
    
    inv = collector.createInventory();
    invent = collector.getInventoryById(inv);
    ItemType it = ItemType::CLOTHES;
    for (int i = 0; i < 100000; i++)
    {
        if (it == ItemType::HATS)
        {
            item = collector.createItem(ItemType::HATS);
            it = ItemType::CLOTHES;
        } else {
            item = collector.createItem(ItemType::CLOTHES);
            it = ItemType::HATS;
        }

        invent->addItem(
            collector.getItemById(item)
        );
    }

    logger.putMessage(
        LogMessage{
            MessageTypes::INFO,
            converter.getJson(collector.getInventoryById(inv))
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