#if !defined(HATS_HPP)
#define HATS_HPP

#include <BaseItems.hpp>
#include <memory>
#include <iostream>

class Hats : public BaseItem
{
public:
    Hats(char*, unsigned long);

    short getType() const {return m_type;};
    unsigned long getItemId() const {return m_id;};
    char* getName() const {return m_name;};

private:
    Hats();
    short m_type = ItemType::HATS;
    unsigned long m_id;
    char* m_name;

};

using pHats = std::shared_ptr<Hats>;

#endif