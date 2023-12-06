#pragma once

#include <memory>
#include <consoleprinter.hpp>
#include "bulk.hpp"

namespace bulk_defs {

/// @brief Абстрактный класс печати блока команд
class BulkPrinter: public virtual hw_io::IPrinter
{
public:
    /// @brief Чисто виртуальная функция вывода блока команд на печать
    /// Основная функция печати print перенесена в секцию protected,
    /// чтобы не было достыпна для пользователей класса
    /// @param bulk shared_ptr указатель на блок команд
    virtual void printBulk(std::shared_ptr<const Bulk> bulk) = 0;

    /// @brief Ститическая функция преобразования блока команд в строку
    /// @param bulk Константная ссылка на блок команд
    /// @return выдаёт строку в форма bulk: <cmd1>, ..., <cmdN>
    static std::string bulkToString(const Bulk &bulk);

protected:
    using hw_io::IPrinter::print;
};



}