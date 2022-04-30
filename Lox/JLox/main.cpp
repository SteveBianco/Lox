// This file contains the 'main' function. Program execution begins and ends there.
//
#include "Lox.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Executes Lox statements entered at the command prompt,
// i.e. runs a REPL.
void runPrompt()
{
    Lox lox;

    std::string line;
    std::cout << "> ";

    while (std::getline(std::cin, line))
    {
        lox.run(line);
        std::cout << "> ";
    }
}

// Runs a Lox program from the specified file.
void runFile(std::string fileName)
{
    // read the file contents into a string
    std::ifstream fs{ fileName };

    auto start = std::istreambuf_iterator<char>(fs);
    auto end = std::istreambuf_iterator<char>();
    std::string source(start, end);

    // execute the program
    Lox lox;
    lox.run(source);
}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        runPrompt();
    }
    else if (argc == 2)
    {
        runFile(argv[1]);
    }
    else
    {
        //TODO need a better usage message
        std::cerr << "Usage: jlox <path to script>\n";
        return 64;
    }

    return 0;
}
