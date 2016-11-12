#include <string>
#include <fstream>
#include <iostream>

#include "lexer.hpp"

int main (int argc, char* argv[]){
    try {
    if (argc < 2){
        std::cerr << "Usage: " << argv[0] << " <file path>\n";
        return EXIT_FAILURE;
    }

        PL0::lexer lexer{std::ifstream(argv[1])};

        std::cout << "Lexing file " << argv[1] << "\n";
        for (PL0::morphem morphem; !lexer.end();){
            std::cout << lexer.lex() << "\n";
        }

    } catch (const std::exception &e){
        std::cerr << e.what() << std::endl;
        throw;
    }

}