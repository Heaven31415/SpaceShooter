#pragma once

#include <iostream>

class GUID
{
public:
    enum class Type
    {
        Empty,
        NonEmpty
    };
    GUID(Type type = Type::NonEmpty);
    bool operator==(const GUID& other) const;
    bool operator!=(const GUID& other) const;
    bool operator<(const GUID& other) const;
    bool operator>(const GUID& other) const;
    bool operator>=(const GUID& other) const;
    bool operator<=(const GUID& other) const;

    friend std::ostream& operator<< (std::ostream& stream, const GUID& guid);
    long unsigned getMagic() const;

private:
    static long unsigned counter;
    long unsigned magic;
};