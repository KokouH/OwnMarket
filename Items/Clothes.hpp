#if !defined(CLOTHES_HPP)
#define CLOTHES_HPP

#include <BaseItems.hpp>
#include <memory>
#include <iostream>

class Clothes : public BaseItem
{
public:
    Clothes();

    Clothes(short type, char* name);

    short getType() const {return m_type;};
    unsigned long getItemId() const {return m_id;};
    char* getName() const {return m_name;};

private:
    short m_type;
    unsigned long m_id;
    char* m_name;

};

using pClothes = std::shared_ptr<Clothes>;

#endif