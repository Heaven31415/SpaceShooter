#pragma once

#include "Object.hpp"
#include <vector>

class Observer
{
public:
    virtual void onNotify(Object* obj, unsigned int code) = 0;
};

class Subject
{
public:
    void add(Observer* observer)
    {
        for (std::size_t i = 0; i < m_observers.size(); i++)
            // don't add the same observer more than once
            if (m_observers[i] == observer) return;
        m_observers.push_back(observer);
    }

    void remove(Observer* observer)
    {
        for (std::size_t i = 0; i < m_observers.size(); i++)
        {
            if (m_observers[i] == observer)
            {
                // find pointer with the same address and erase it
                m_observers.erase(m_observers.begin() + i);
                break;
            }
        }
    }

    void notify(Object* obj, unsigned int code)
    {
        for (auto& observer : m_observers)
            // inform observer that object 'obj' did action labeled with 'code'
            observer->onNotify(obj, code);
    }

private:
    std::vector<Observer*> m_observers;
};

