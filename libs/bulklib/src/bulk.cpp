#include "bulk.hpp"

namespace bulk_defs {
    Bulk::Bulk(std::string &&firstCommand, std::chrono::time_point<std::chrono::system_clock> &&startPoint): 
        m_startPoint {std::move(startPoint)},
        m_commands { {std::string{std::move(firstCommand)}}}
    {
    }

    const std::vector<std::string> &Bulk::commands() const
    {
        return m_commands;
    }

    void Bulk::push(std::string &&command)
    {
        m_commands.push_back(std::move(command));
    }

    const std::chrono::time_point<std::chrono::system_clock> &Bulk::startPoint() const
    {
        return m_startPoint;
    }
}
