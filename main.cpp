#include <Inventory.hpp>
#include <Clothes.hpp>
#include <algorithm>
#include <iostream>

int main()
{
    Inventory i1;
    Inventory i2;

    Clothes item1;

    pClothes pitem = std::make_shared<Clothes>(item1);

    i1.addItem(pitem);
    pItemsList pl = i1.getItems();

    std::for_each(pl->begin(), pl->end(), [](pBaseItem item)
    {
        std::cout << *(Clothes *)item.get() << std::endl;
    });

    return (0);
}