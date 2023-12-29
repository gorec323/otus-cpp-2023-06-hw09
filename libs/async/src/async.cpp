#include <memory>
#include <commandscontroller.hpp>
#include "async.h"

namespace async {

print_handler_t connect(std::size_t bulkLimit)
{
    return new bulk_defs::CommandsController(bulkLimit);
}

void receive(print_handler_t const handler, const char *const data, std::size_t dataSize)
{
    auto controller = static_cast<bulk_defs::CommandsController *>(handler);
    if (handler == nullptr)
        return;

    controller->addCommand(std::string{data, dataSize});    
}

void disconnect(print_handler_t handler)
{
    const std::string endCommand = "EOF";
    receive(handler, endCommand.c_str(), endCommand.size());

    auto controller = static_cast<bulk_defs::CommandsController *>(handler);
    delete controller;
}

}
