#include <algorithm>
#include "bulkprinter.hpp"

namespace bulk_defs {

std::string BulkPrinter::bulkToString(const bulk_defs::Bulk& bulk)
{
    auto &&commands = bulk.commands();

    if (commands.empty())
        return {};

    std::string res {"bulk: " + commands.front()};

    if (commands.size() > 1) {
        const auto ce {commands.cend()};
        std::for_each(std::next(commands.cbegin()), ce,
        [&res](const auto &str)
        {
            res.append(", " + str);
        });
    }
    
    return res;
}

}
