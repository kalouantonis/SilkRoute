#ifndef ITEMREFERENCEDEXCEPTION_H
#define ITEMREFERENCEDEXCEPTION_H

#include <stdexcept>
#include <sstream>

/// Custom exception for use when removing records
class ItemReferencedException: public std::runtime_error
{
public:
    /// Constructor, takes message as argument
    ItemReferencedException(const char* m="Item already referenced once!")
        : std::runtime_error(m) // Parent constructor
    {

    }
};


#endif // ITEMREFERENCEDEXCEPTION_H
