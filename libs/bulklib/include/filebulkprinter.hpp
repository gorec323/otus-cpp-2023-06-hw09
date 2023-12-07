#pragma once

#include <memory>
#include <fstream>
#include <thread>
#include <sstream>
#include "bulkprinter.hpp"

namespace bulk_defs {

/// @brief Класс файловый принтер блока команд. 
/// Выводит каждый блок команд в отдельный файл.
/// Имя файла - количество миллисекунд с начала эпохи
class FileBulkPrinter: public BulkPrinter
{
public:
    using BulkPrinter::BulkPrinter;

    /// @brief Перекрытая абстрактная функция печати блока команд
    /// @param bulk shared_ptr на блок команд
    void printBulk(std::shared_ptr<const Bulk> bulk) override final
    {
        if (!m_ofs) {
            std::ostringstream ss;
            ss << std::this_thread::get_id();
            const auto threadIdStr = ss.str();
            m_ofs = std::make_unique<std::ofstream>("bulk" 
                + std::to_string(bulk->startPoint().time_since_epoch().count())
                + "_" + threadIdStr + ".log");
        }

        print(BulkPrinter::bulkToString(*bulk));
    }

protected:

    /// @brief Функция строкового представления блока команд в файл
    /// @param data 
    void print(const std::string &data) override final
    {
        if (m_ofs->is_open())
            (*m_ofs) << data;
        
        m_ofs.reset();
    }

private:
    std::unique_ptr<std::ofstream> m_ofs;
};

}