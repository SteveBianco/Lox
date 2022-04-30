// This file contains the 'main' function. Program execution begins and ends there.
//
#include "Lox.h"
#include <iostream>
#include <fstream>
#include <sstream>

struct ErrorCodes
{
    const static int OK = 0;
    const static int InternalError = 64;
    const static int InvalidArgument = 65;
};

// Executes Lox statements entered at the command prompt,
// i.e. runs a REPL.
int runPrompt()
{
    Lox lox;

    std::string line;
    std::cout << "> ";

    while (std::getline(std::cin, line))
    {
        // execute the last line entered
        lox.run(line);

        //TODO how to report errors
        lox.clearErrors();

        // prompt for next line
        std::cout << "> ";
    }

    return ErrorCodes::OK;
}

// Runs a Lox program from the specified file.
int runFile(std::string fileName)
{
    // read the file contents into a string
    std::ifstream fs{ fileName };

    auto start = std::istreambuf_iterator<char>(fs);
    auto end = std::istreambuf_iterator<char>();
    std::string source(start, end);

    // execute the program
    Lox lox;
    lox.run(source); 

    if (lox.hadError())
    {
        for (const auto& error : lox.errors())
        {
            std::cerr << error << "\n";
            return ErrorCodes::InternalError;
        }
    }

    return ErrorCodes::OK;
}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        runPrompt();
    }
    else if (argc == 2)
    {
        return runFile(argv[1]);
    }
    else
    {
        //TODO need a better usage message
        std::cerr << "Usage: jlox <path to script>\n";
        return ErrorCodes::InvalidArgument;
    }

    return ErrorCodes::OK;
}
