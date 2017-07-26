#include "..\Include\CommandQueue.hpp"

void CommandQueue::push(Command command)
{
    m_commands.push(command);
}

Command CommandQueue::pop()
{
    auto command = m_commands.front();
    m_commands.pop();
    return command;
}

bool CommandQueue::isEmpty() const
{
    return m_commands.empty();
}
