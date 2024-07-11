#include <Clothes.hpp>

Clothes::Clothes()
    :m_id(1),
    m_type(0)
{
    m_name = EmptyItemName;
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
