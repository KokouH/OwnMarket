#include <InventoryCollector.hpp>

InventoryCollector::InventoryCollector(ItemsGenerator& items_gen, InventoryGenerator &inventory_gen)
    : m_item_generator(items_gen),
    m_inventory_generator(inventory_gen)
{
}

unsigned long InventoryCollector::createInventory()
{
    pInventory pinventory;
    unsigned long id;

    id = m_inventory_generator.get_current_id();
    pinventory = std::make_shared<Inventory>(id);
    m_inventories[id] = pinventory;

    return id;
}

unsigned long InventoryCollector::createItem(short type)
{
    pBaseItem pItem;
    unsigned long id;

    id = m_item_generator.get_current_id();
    if (type == ItemType::CLOTHES)
        pItem = std::make_shared<Clothes>(Clothes(
            (char *)ItemNames::ClothesDragonLore, id
        ));

    if (type == ItemType::HATS)
        pItem = std::make_shared<Hats>(Hats(
            (char *)ItemNames::HatDragonLore, id
        ));

    if (pItem.get() == nullptr)
        return 0;
    m_items[id] = pItem;

    return id;
}

void InventoryCollector::removeItem(unsigned long id)
{
    if (auto it = m_items.find(id); it != m_items.end())
        m_items.erase( it );
}

pBaseItem InventoryCollector::getItemById(unsigned long id)
{
    return m_items[id];
}

pInventory InventoryCollector::getInventoryById(unsigned long id)
{
    return m_inventories[id];
}
