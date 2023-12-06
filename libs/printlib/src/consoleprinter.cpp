#include <iostream>
#include "consoleprinter.hpp"

namespace hw_io {

    void ConsolePrinter::print(const std::string &data)
    {
        std::cout << data << std::endl;
    }

}