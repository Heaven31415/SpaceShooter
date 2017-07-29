#pragma once

#include "Object.hpp"
#include <unordered_map>

struct GUIDHasher
{
    std::size_t operator()(const GUID& guid) const
    {
        return guid.getMagic();
    }
};

class ObjectContainer
{
public:
    ObjectContainer();

private:
    std::unordered_map<GUID, Object::Ptr, GUIDHasher> m_objects;
};
