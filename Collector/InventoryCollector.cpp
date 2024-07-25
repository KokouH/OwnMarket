#include <InventoryCollector.hpp>

InventoryCollector::InventoryCollector(ItemsGenerator& items_gen)
    : m_item_generator(items_gen)
{
}

void InventoryCollector::addItem(short type)
{
    pBaseItem pItem;
    unsigned long newItemId = 
        m_item_generator.get_current_id();

    if (type == ItemType::CLOTHES)
        pItem = std::make_shared<BaseItem>(Clothes(
            (char *)ItemNames::HatDragonLore,
            newItemId
        ));

    m_items[newItemId] = pItem;
}

void InventoryCollector::removeItem(unsigned long id)
{
    if (auto it = m_items.find(id); it != m_items.end())
        m_items.erase( it );
}