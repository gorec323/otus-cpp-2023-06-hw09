#include <iostream>
#include <algorithm>
#include <utility>
#include <consolebulkprinter.hpp>
#include "filebulkprinter.hpp"
#include "commandscontroller.hpp"
#include "asyncbulkprinter.hpp"

namespace bulk_defs {

namespace {
    static const std::string FINISH_COMMAND {"EOF"};
    static const std::string START_BLOCK_COMMAND {"{"};
    static const std::string END_BLOCK_COMMAND {"}"};
}

CommandsController::CommandsController(std::size_t blockCommandsLimit):
    m_blockCommandsLimit {blockCommandsLimit}
{
    m_printers.push_back(std::make_unique<AsyncBulkPrinter<ConsoleBulkPrinter>>());
    m_printers.push_back(std::make_unique<AsyncBulkPrinter<FileBulkPrinter>>(2));
}

void CommandsController::addCommand(std::string &&strCommand)
{
    // std::cout << ">" << strCommand << std::endl;
    if (m_finished)
        return;

    if ((strCommand != START_BLOCK_COMMAND) && (strCommand != END_BLOCK_COMMAND)) {
        if (strCommand == FINISH_COMMAND) {
            m_finished = true;
            if (m_blockDept == 0)
                printBuket();
            return;
        }

        if (m_currentBulk)
            m_currentBulk->push(std::move(strCommand));
        else
            m_currentBulk = std::make_unique<Bulk>(std::move(strCommand));

        if (m_blockDept > 0)
            return;

        if (m_currentBulk->commands().size() == m_blockCommandsLimit)
            printBuket();

        return;
    }

    if (strCommand == START_BLOCK_COMMAND) {
        if (std::exchange(m_blockDept, m_blockDept + 1) == 0)
            printBuket();
    } else {
        m_finished = (std::exchange(m_blockDept, m_blockDept - 1) == 0);
        if (m_finished)
            return;

        if (m_blockDept == 0)
            printBuket();
    }
}

bool CommandsController::isFinished() const noexcept
{
    return m_finished;
}

void CommandsController::printBuket()
{
    if (m_currentBulk) {
        // const std::string str {bulkToString(std::exchange(m_currentBulk, {}))};
        for (auto &&printer : m_printers)
            printer->printBulk(m_currentBulk);
    
        m_currentBulk = {};
    }
}

}
