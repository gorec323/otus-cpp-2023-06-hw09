#pragma once

#include <memory>
#include <deque>
#include <bulkprinter.hpp>

namespace bulk_defs {

/// @brief Контроллер обработки команд
class CommandsController
{
public:
    /// @brief Конструктор
    /// @param blockCommandsLimit количество команд в блоке
    CommandsController(std::size_t blockCommandsLimit);

    /// @brief Деструктор
    ~CommandsController() = default;

    /// @brief Добавление новой команды
    /// @param strCommand строковая команда в виде r-value ссылки
    void addCommand(std::string &&strCommand);

    /// @brief Признак завершения обработки команд
    /// @return возвращает true, если обработка команд завершена, например,
    /// была получена команда EOF, иначе false
    bool isFinished() const noexcept;

private:
    /// @brief Печать блока команд с помощью зарегистрированных принтеров
    void printBuket();

    const std::size_t m_blockCommandsLimit; // количество команд в блоке
    bool m_finished {false}; // признак завершения обработки команд
    int m_blockDept{0}; // текущая глубина блока команд
    std::shared_ptr<Bulk> m_currentBulk; // текущий блок команд
    std::vector<std::unique_ptr<BulkPrinter>> m_printers; // принтеры
};

}
