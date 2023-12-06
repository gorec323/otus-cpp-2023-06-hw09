#pragma once

#include <string>

namespace hw_io {

/// @brief Интерфейс вывода данных
struct IPrinter
{
    // Виртуальный деструктор
    virtual ~IPrinter() = default;

    /// @brief ФУнкция вывода на печать строки
    /// @param  
    virtual void print(const std::string &) = 0;
};

}
