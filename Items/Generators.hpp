#if !defined(ITEMS_GENERATOR_HPP)
#define ITEMS_GENERATOR_HPP

#include <atomic>

class ItemsGenerator
{
public:
    ItemsGenerator();
    ItemsGenerator(unsigned long);
    ~ItemsGenerator() = default;

    unsigned long get_current_id();
    unsigned long get_current_id_non_inc();

private:
    std::atomic<unsigned long> m_cur_id;

};

class InventoryGenerator
{
public:
    InventoryGenerator();
    InventoryGenerator(unsigned long);
    ~InventoryGenerator() = default;

    unsigned long get_current_id();
    unsigned long get_current_id_non_inc();

private:
    std::atomic<unsigned long> m_cur_id;

};

#endif