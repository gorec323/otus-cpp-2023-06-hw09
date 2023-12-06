#pragma once

#include <string>
#include <vector>
#include <chrono>

namespace bulk_defs {

/// @brief Класс предназначен для хранения блока комманд и времени поступления первой команды
class Bulk
{
public:
    /// @brief Конструктор
    /// @param firstCommand Первая команда блока
    /// @param startPoint Время поступления первой команды, по умолчанию now
    Bulk(std::string &&firstCommand, std::chrono::time_point<std::chrono::system_clock> &&startPoint =
    std::chrono::system_clock::now());

    /// @brief Конструктор перемещения
    /// @param  
    Bulk(Bulk &&) noexcept = default;

    /// @brief Деструктор
    ~Bulk() = default;

    const std::vector<std::string> &commands() const;

    /// @brief Добавление новой команды в блок
    /// @param command Строковая команда
    void push(std::string &&command);

    const std::chrono::time_point<std::chrono::system_clock> &startPoint() const;
    
private:
    const std::chrono::time_point<std::chrono::system_clock> m_startPoint;
    std::vector<std::string> m_commands;
};

}
