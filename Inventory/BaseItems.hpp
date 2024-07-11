#if !defined(BASE_ITEMS_HPP)
#define BASE_ITEMS_HPP

#include <memory>

class BaseItem
{
public:
    virtual short getType() const =0;
    virtual unsigned long getItemId() const =0;
    virtual char* getName() const =0;
};

using pBaseItem = std::shared_ptr<BaseItem>;

#endif