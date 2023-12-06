#include <gtest/gtest.h>
#include <commandscontroller.hpp>
#include <thread>
#include <bulk.hpp>
#include <streamredirect.hpp>

// обработка и проверка набора команд с эталонными значениями
void cmdProcessingTest(std::size_t commandsLimit, const std::vector<std::string> &etalons)
{
    bulk_defs::CommandsController cmdProc{commandsLimit};

    std::stringstream outputStream;
    helpers::stream_redirect sr {std::cout, outputStream.rdbuf()};
    
    auto it = etalons.cbegin();

    std::string strCommand;
    while (!cmdProc.isFinished() && std::cin >> strCommand) {
        cmdProc.addCommand(std::exchange(strCommand, ""));

        outputStream.tie(&std::cout);

        if (outputStream.str().size() > 0) {
            EXPECT_EQ(*it, outputStream.str());
            outputStream.str("");
            outputStream.clear();
            std::advance(it, 1);
        }
    }
};

/// @brief Проверка первой тестовой последовательности
/// @param Название набора тестов
/// @param Название тестового примера 
TEST(BulklibTest, FirstSequenceTestCase)
{
    std::istringstream input1("cmd1\ncmd2\ncmd3\ncmd4\ncmd5\nEOF");
    helpers::stream_redirect sr {std::cin, input1.rdbuf()};

    std::vector<std::string> etalons {
        "bulk: cmd1, cmd2, cmd3\n",
        "bulk: cmd4, cmd5\n"
    };

    // обработка первого примера блока команд
    cmdProcessingTest(3, etalons);
}

/// @brief Проверка первой тестовой последовательности с динамическими блоками
/// @param Название набора тестов 
/// @param Название тестового примера 
TEST(BulklibTest, SecondSequenceTestCase)
{
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

    const std::vector<std::string> etalons {
        "bulk: cmd1, cmd2\n",
        "bulk: cmd3, cmd4\n",
        "bulk: cmd5, cmd6, cmd7, cmd8, cmd9\n"
    };

    // обработка и проверка примера блока команд
    cmdProcessingTest(3, etalons);
}
