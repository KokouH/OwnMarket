#include <Clothes.hpp>

Clothes::Clothes()
    : m_type(0)
{
    m_name = nullptr;
    m_id = 0;
}

Clothes::Clothes(short type, char* name)
    : m_type(type),
    m_name(name)
{
    /* TODO
    Добавить класс генератора id,
    который гарантирует их неповторяемость
    */
    m_id = 0;
}
