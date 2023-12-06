#pragma once

#include "iprinter.hpp"

namespace hw_io {

/// @brief Базовый класс вывода строки в стандартный поток вывода
class ConsolePrinter : public virtual IPrinter
{
public:
    /// @brief Функция печати строки на стандартный поток вывода
    /// @param data 
    void print(const std::string &data) override final;
};

}