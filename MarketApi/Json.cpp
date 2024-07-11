#include <Json.hpp>

JsonConverter::JsonConverter()
{}

JsonConverter::~JsonConverter()
{}

std::string JsonConverter::getJson(pBaseItem item)
{
    std::stringstream strItemJson;

    strItemJson << "{\"itemType\":"
        << item->getType() << ",\"itemId\":" 
        << item->getItemId() << ",\"itemName\":\""
        << item->getName() << "\"}";

    return strItemJson.str();
}

std::string JsonConverter::getJson(pInventory)
{
    std::string strItemJson("{}");

    return strItemJson;
}