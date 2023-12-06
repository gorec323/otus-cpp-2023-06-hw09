#include <iostream>
#include <sstream>
#include <thread>
#include <utility>
#include <commandscontroller.hpp>
#include <streamredirect.hpp>
#include "version.h"

// using namespace std;

int main(int argc, const char *argv[])
{
    std::cout << "Bulk version: " << PROJECT_VERSION << std::endl;

    const auto bulkSize = argc;
    if (bulkSize != 2) {
        std::cout << "Usage:" << std::endl;
        std::cout << argv[0] << " [number of commands]" << std::endl;
        return 1;
    }

    // обработка параметра командной строки с числом команд в блоке
    const int bulkCommandsLimit = std::atoi(argv[1]);
    if (bulkCommandsLimit < 1)
        return 0;

    // обработка набора команд
    auto cinCmdProcessing = [bulkCommandsLimit]()
    {
        std::string strCommand;
        bulk_defs::CommandsController cmdProc{static_cast<std::size_t>(bulkCommandsLimit)};

        while (!cmdProc.isFinished() && std::cin >> strCommand) {
            // std::cout << strCommand << std::endl;
            cmdProc.addCommand(std::exchange(strCommand, ""));
            using namespace std::chrono_literals;
            if (!cmdProc.isFinished())
                std::this_thread::sleep_for(1s);
        }
    };

    // examples

    { // обработка первого примера блока команд
        
        std::cout << std::endl << "example1: " << std::endl;

        std::istringstream inputStream("cmd1\ncmd2\ncmd3\ncmd4\ncmd5\nEOF");
        helpers::stream_redirect sr {std::cin, inputStream.rdbuf()};

        cinCmdProcessing();
    
    }

    { // обработка второго примера блока команд
        
        std::cout << std::endl << "example2: " << std::endl;

        std::stringstream inputStream; 
        inputStream << "cmd1" << std::endl
        << "cmd2" << std::endl
        << "{" << std::endl
        << "cmd3" << std::endl
        << "cmd4" << std::endl
        << "}" << std::endl
        << "{" << std::endl
        << "cmd5" << std::endl
        << "cmd6" << std::endl
        << "{" << std::endl
        << "cmd7" << std::endl
        << "cmd8" << std::endl
        << "}" << std::endl
        << "cmd9" << std::endl
        << "}" << std::endl
        << "{" << std::endl
        << "cmd10" << std::endl
        << "cmd11" << std::endl
        << "EOF" << std::endl;

        helpers::stream_redirect sr {std::cin, inputStream.rdbuf()};
    
        cinCmdProcessing();

    }

    std::cout << std::endl << "enter OEF to exit or enter the command:" << std::endl;

    cinCmdProcessing();

    return 0;
}
