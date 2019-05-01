#pragma once

#include <queue>
#include <functional>
#include <SFML/System/Time.hpp>

class Object;

typedef std::function<void(Object*, sf::Time)> Action;

struct Command
{
    Command() : who(0), action() {}
    Command(unsigned int who, Action action) : who(who), action(action) {}

    unsigned int                            who;
    Action                                  action;
};

class CommandQueue
{
public:
    void                                    push(Command command);
    Command                                 pop();
    bool                                    isEmpty() const;

private:
    std::queue<Command>                     m_commands;
};