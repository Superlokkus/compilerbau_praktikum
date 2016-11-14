#include <string>
#include <fstream>
#include <iostream>

#include "lexer.hpp"

int main(int argc, char *argv[]) {
    try {
        if (argc < 2) {
            std::cerr << "Usage: " << argv[0] << " <file path>\n";
            return EXIT_FAILURE;
        }

        PL0::lexer lexer{std::ifstream(argv[1])};

        std::cout << "Lexing file " << argv[1] << "\n";
        while (!lexer.end()) {
            auto morphem = lexer.lex();
            if (morphem.morphem_class != PL0::morphem_class::empty)
                std::cout << morphem << "\n";
        }

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        throw;
    }

}