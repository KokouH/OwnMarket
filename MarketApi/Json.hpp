#if !defined(JSON_HPP_)
#define JSON_HPP_

#include <Inventory.hpp>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <map>
#include <string>
#include <sstream>

struct tempString
{
    char* str;
    unsigned long index;
};

class JsonConverter
{
public:
    JsonConverter();
    ~JsonConverter();

    /* TODO
    Убрать std::string
    Идея в том что стриг будет постоянно копироваться, а это плохо
    Поэтому нужен собственый тип данных, который будет хранить json 
    строки какое=то время и не будет отчищать память это время
    и не будет копировать строку
    */
    std::string getJson(pBaseItem);
    std::string getJson(pInventory);

private:
    // std::map<>

};

#endif