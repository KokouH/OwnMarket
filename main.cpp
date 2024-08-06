#include <InventoryCollector.hpp>
#include <Server.hpp>
#include <Json.hpp>
#include <algorithm>
#include <iostream>
#include <Logger.hpp>
#include <URI.hpp>

void EP_api_get_inventory(std::string& uri, EndPointArgs& args, std::string& response)
{
    URI _uri;
    std::stringstream ss;
    unsigned long id = -1;

    ss << OK_HTTP_STRING;
    ss << "\r\n";

    _uri.Parse(uri);
    if (_uri.params.find("id") != _uri.params.end())
    {
        try
        {
            id = std::stoul(_uri.params["id"]);
            ss << args.m_converter.getJson(args.m_collector.getInventoryById(id));
        }
        catch(const std::exception& e)
        {
            ss << _uri.params["id"];
            return;
        }
    }

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
    
    for (int iq; iq < 100; iq++)
    {
        inv = collector.createInventory();
        invent = collector.getInventoryById(inv);
        ItemType it = ItemType::CLOTHES;
        for (int i = 0; i < 10000; i++)
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
    }

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