#include "GUID.hpp"

long unsigned GUID::counter = 1;

GUID::GUID(Type type)
: magic(0)
{
    if (type == Type::NonEmpty) magic = counter++;
}

bool GUID::operator==(const GUID& other) const
{
    return this->magic == other.magic;
}

bool GUID::operator!=(const GUID& other) const
{
    return !(*this == other);
}

bool GUID::operator<(const GUID& other) const
{
    return this->magic < other.magic;
}

bool GUID::operator>(const GUID& other) const
{
    return other < *this;
}

bool GUID::operator>=(const GUID& other) const
{
    return !(*this < other);
}

bool GUID::operator<=(const GUID& other) const
{
    return !(other < *this);
}

long unsigned GUID::getMagic() const
{
    return magic;
}

std::ostream & operator<<(std::ostream & stream, const GUID & guid)
{
    stream << "GUID 0x" << std::hex << std::uppercase << guid.magic;
    return stream;
}
