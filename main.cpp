#include <Inventory.hpp>
#include <Clothes.hpp>
#include <algorithm>
#include <iostream>

void showInventory(pItemsList pl)
{
    std::for_each(pl->begin(), pl->end(), [](pBaseItem item)
    {
        std::cout << *(Clothes *)item.get() << '\n';
    });
}

int main()
{
    pInventory pi1 = std::make_shared<Inventory>(Inventory());
    pInventory pi2 = std::make_shared<Inventory>(Inventory());

    Clothes item1;

    pClothes pitem = std::make_shared<Clothes>(item1);
    pi1->addItem(pitem);

    std::cout << "Inventory 1:\n";
    showInventory(pi1->getItems());
    
    pi1->moveItem((pBaseItem)pitem, pi2);

    std::cout << "Inventory 2:\n";
    showInventory(pi2->getItems());

    std::cout << "Inventory 1:\n";
    showInventory(pi1->getItems());

    return (0);
}