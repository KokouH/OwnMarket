#if !defined(INVENTORY_HPP)
#define INVENTORY_HPP

#include <BaseItems.hpp>
#include <set>
#include <memory>

class Inventory;
using pInventory = std::shared_ptr<Inventory>;
using ItemsList = std::set<pBaseItem>;
using pItemsList = std::shared_ptr<ItemsList>;

class Inventory
{
public:
    Inventory();
    ~Inventory();
    
    void addItem(pBaseItem);
    void removeItem(pBaseItem);
    void moveItem(pBaseItem, pInventory);
    unsigned long getId(){return m_id;};
    pItemsList getItems();

private:
    ItemsList m_items;
    unsigned long m_id;

};

#endif