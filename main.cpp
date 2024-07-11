#include <Inventory.hpp>
#include <Clothes.hpp>
#include <Json.hpp>
#include <algorithm>
#include <iostream>

int main()
{
    pClothes pitem = std::make_shared<Clothes>(Clothes());
    
    std::cout << JsonConverter().getJson(pitem) << std::endl;

    return (0);
}