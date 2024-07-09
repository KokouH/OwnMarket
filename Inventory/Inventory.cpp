#include <Inventory.hpp>

Inventory::Inventory()
{}

Inventory::~Inventory()
{}

void Inventory::addItem(pBaseItem item)
{
    m_items.insert(item);
}

void Inventory::removeItem(pBaseItem item)
{
    m_items.erase(item);
}

void Inventory::moveItem(pBaseItem item, pInventory other_inventory)
{
    this->removeItem(item);
    other_inventory->addItem(item);
}

pItemsList Inventory::getItems()
{
    return std::make_shared<ItemsList>(m_items);
}