/*! @file lexer.cpp
 *
 */

#include "lexer.hpp"


namespace PL0{
    lexer::lexer(std::ifstream &file) {

    }
    morphem lexer::lex() {
        return morphem{};
    }

};

std::ostream& operator<< (std::ostream &os, const PL0::morphem& morphem){
    os << "Morphem class:" << morphem.morphem_class;

    return os;
}