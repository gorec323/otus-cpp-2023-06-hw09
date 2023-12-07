#pragma once

#include <cinttypes>

namespace async {

    using print_handler_t = void *;

    print_handler_t connect(std::size_t bulkLimit);

    void receive(print_handler_t const handler, const char * const data, std::size_t dataSize);

    void disconnect(print_handler_t handler);
}