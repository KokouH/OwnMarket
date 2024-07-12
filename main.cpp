#include <Inventory.hpp>
#include <Clothes.hpp>
#include <Json.hpp>
#include <algorithm>
#include <iostream>
#include <ItemNames.hpp>

int main()
{
    pClothes pitem = std::make_shared<Clothes>(
        Clothes(10, (char *)ItemNames::HatDragonLore)
    );
    
    std::cout << JsonConverter().getJson(pitem) << std::endl;

    return (0);
}