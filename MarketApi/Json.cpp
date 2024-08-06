#include <Json.hpp>

JsonConverter::JsonConverter()
{}

JsonConverter::~JsonConverter()
{}

static inline nlohmann::json _jsonItem(pBaseItem item)
{
    nlohmann::json j_item;

    j_item["type"] = item->getType();
    j_item["itemId"] = item->getItemId();
    j_item["name"] = item->getName();

    return j_item;
}

std::string JsonConverter::getJson(pBaseItem item)
{
    if (item.get() == nullptr)
        return std::string();

    nlohmann::json j_item = _jsonItem(item);

    return j_item.dump();
}

std::string JsonConverter::getJson(pInventory inventory)
{
    if (!inventory)
        return std::string("Error: Inventory not found");

    nlohmann::json j_inventory;
    pItemsList itemsList = inventory->getItems();
    
    std::for_each(itemsList->begin(), itemsList->end(), [&](pBaseItem item)
    {
        j_inventory.push_back( _jsonItem(item) );
    });

    return j_inventory.dump();
}