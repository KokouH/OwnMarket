#if !defined(INVENTORY_COLLECTOR_HPP)
#define INVENTORY_COLLECTOR_HPP

#include <Inventory.hpp>
#include <Generators.hpp>
#include <Clothes.hpp>
#include <ItemNames.hpp>
#include <vector>
#include <unordered_map>
#include <memory>

/*
InventoryCollector
хранит все предметы и инвентари
гарантирует что предметы не будут повторятся
*/

class InventoryCollector
{
public:
    InventoryCollector(ItemsGenerator&, InventoryGenerator&);
    ~InventoryCollector() = default;

    unsigned long createInventory();
    unsigned long createItem(short); // return new item id
    void removeItem(unsigned long);

    pBaseItem getItemById(unsigned long);
    pInventory getInventoryById(unsigned long);

private:
    InventoryCollector();
    std::unordered_map<unsigned long, pInventory> m_inventories;
    std::unordered_map<unsigned long, pBaseItem> m_items;

    ItemsGenerator &m_item_generator;
    InventoryGenerator &m_inventory_generator;

};

#endif