#include <ItemsGenerator.hpp>

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