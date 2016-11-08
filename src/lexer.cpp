/*! @file lexer.cpp
 *
 */

#include "lexer.hpp"


namespace PL0 {
    lexer::lexer(std::ifstream &file) {

    }

    morphem lexer::lex() {
        return morphem{};
    }

};

std::ostream &operator<<(std::ostream &os, const PL0::morphem &morphem) {
    os << "Morphem class:" << morphem.morphem_class;

    return os;
}

std::ostream &operator<<(std::ostream &os, const PL0::morphem_class &morphem_class) {
    using namespace PL0;
    switch (morphem_class) {
        case morphem_class::identifier:
            os << "identifier";
            break;
        case morphem_class::number:
            os << "number";
            break;
        case morphem_class::symbol:
            os << "symbol";
            break;
    }
    return os;
}

bool PL0::lexer::end() const {

    return false;
}


