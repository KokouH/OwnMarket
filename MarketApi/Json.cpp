#include <Json.hpp>

JsonConverter::JsonConverter()
{}

JsonConverter::~JsonConverter()
{}

std::string JsonConverter::getJson(pBaseItem item)
{
    std::stringstream strItemJson;
    char* name = item->getName();

    strItemJson << "{\"itemType\":"
        << item->getType() << ",\"itemId\":" 
        << item->getItemId() << ",\"itemName\":\"";
    if (name)
        strItemJson << name << "\"}";
    else
        strItemJson << "\"}";

    return strItemJson.str();
}

std::string JsonConverter::getJson(pInventory)
{
    std::string strItemJson("{}");

    return strItemJson;
}