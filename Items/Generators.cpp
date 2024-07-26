#include <Generators.hpp>

ItemsGenerator::ItemsGenerator()
{
    m_cur_id = 0;
}

ItemsGenerator::ItemsGenerator(unsigned long startId)
{
    m_cur_id = startId;
}

unsigned long ItemsGenerator::get_current_id_non_inc()
{
    return m_cur_id;
}

unsigned long ItemsGenerator::get_current_id()
{
    return m_cur_id++;
}

// Пока скопировал, думаю логика у этих генераторов должна быть разной и потом поменяется, но пока так будет быстрее  
InventoryGenerator::InventoryGenerator()
{
    m_cur_id = 0;
}

InventoryGenerator::InventoryGenerator(unsigned long startId)
{
    m_cur_id = startId;
}

unsigned long InventoryGenerator::get_current_id_non_inc()
{
    return m_cur_id;
}

unsigned long InventoryGenerator::get_current_id()
{
    return m_cur_id++;
}