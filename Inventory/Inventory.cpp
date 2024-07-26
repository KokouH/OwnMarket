#include <Inventory.hpp>

Inventory::Inventory()
    : m_id(0)
{}

Inventory::Inventory(unsigned long id)
    : m_id(id)
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
    pItemsList pIL = this->getItems();
    if (pIL->find(item) == pIL->end())
        return;
    this->removeItem(item);
    other_inventory->addItem(item);
}

pItemsList Inventory::getItems()
{
    return std::make_shared<ItemsList>(m_items);
}