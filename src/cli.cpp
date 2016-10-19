#include <iostream>
#include <string>

#include "compiler.hpp"

int main (int argc, char* argv[]){
    std::string input;
    if (argc != 2){
        std::cout << "Awaiting input: " << std::endl;
        std:: cin >> input;
    } else {
        input = argv[1];
    }
    auto parse_result = task1_grammar_lexer(input);
    if (parse_result.first) {
        std::cout << parse_result.second << std::endl;
    } else {
        std::cerr << "Expression not fully recognized\n";
    }
}