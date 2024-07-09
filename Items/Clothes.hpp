#if !defined(CLOTHES_HPP)
#define CLOTHES_HPP

#include <BaseItems.hpp>
#include <memory>
#include <iostream>

class Clothes : public BaseItem
{
public:
    Clothes():
        m_id(1),
        m_type(0)
    {};

    short getType() const {return m_type;};
    unsigned long getItemId() const {return m_id;};

private:
    short m_type;
    unsigned long m_id;

};

using pClothes = std::shared_ptr<Clothes>;

std::ostream& operator<<(std::ostream& os, const Clothes& dt)
{
    os << "Type: " << dt.getType() << " / Id: " << dt.getItemId() << "\n";
    return os;
}

#endif