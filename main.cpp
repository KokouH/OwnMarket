#include <InventoryCollector.hpp>
#include <Server.hpp>
#include <Json.hpp>
#include <algorithm>
#include <iostream>
#include <Logger.hpp>

void api_endpoind_handler(std::string &content, EndPointArgs& args, std::string& response)
{
    std::stringstream ss;

    content.replace()
    // nlohmann::json obj = getObj(content);

    std::cout << content << std::endl;
    // std::cout << obj;
    ss << "HTTP/1.0 200 OK\r\n\r\n";
    // ss << args.m_converter.getJson(
    //     args.m_collector.getInventoryById(obj["id"])
    // );

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

    server.add_end_point(std::string("/api"), &api_endpoind_handler);
    
    unsigned long inv;
    unsigned long item;
    pInventory invent;

    inv = collector.createInventory();
    invent = collector.getInventoryById(inv);
    for (int i = 0; i < 100000; i++)
    {
        item = collector.createItem(ItemType::CLOTHES);

        invent->addItem(
            collector.getItemById(item)
        );
    }

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