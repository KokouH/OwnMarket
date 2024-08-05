#include <InventoryCollector.hpp>
#include <Server.hpp>
#include <Json.hpp>
#include <algorithm>
#include <iostream>
#include <Logger.hpp>
#include <URI.hpp>

void EP_api_get_inventory(std::string& uri, EndPointArgs& args, std::string& response)
{
    std::stringstream ss;

    ss << OK_HTTP_STRING;
    ss << "\r\n";

    ss << args.m_converter.getJson(
        args.m_collector.getInventoryById(0)
    );

    response = ss.str();
}

int main()
{
    JsonConverter converter;
    ConsoleLogger logger;
    InventoryGenerator inv_gen;
    ItemsGenerator item_gen;
    InventoryCollector collector(item_gen, inv_gen);
    Server server(logger, collector);

    server.add_end_point("/api/get_inventory", &EP_api_get_inventory);
    
    unsigned long inv;
    unsigned long item;
    pInventory invent;
    
    inv = collector.createInventory();
    invent = collector.getInventoryById(inv);
    ItemType it = ItemType::CLOTHES;
    for (int i = 0; i < 1000; i++)
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