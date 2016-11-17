/*! @file lexer.cpp
 *
 */

#include "lexer.hpp"

#include <iomanip>
#include <algorithm>

namespace PL0 {
    lexer::lexer(std::ifstream &&input_stream) : input_stream_(std::move(input_stream)) {

    }

    morphem lexer::lex() {
        auto new_morphem = morphem{};
        new_morphem.morphem_class = morphem_class::empty;
        new_morphem.position = this->position_in_file;

        for (std::char_traits<char>::int_type c;
             (c = this->input_stream_.get()) != std::char_traits<char>::eof();) {
            ++position_in_file.position_in_line;
            
            if (c == '\n') {
                ++position_in_file.line_number;
                position_in_file.position_in_line = 1;
                break;
            } else if (isspace(c)) {
                break;
            } else if (isdigit(c)) {
                new_morphem.morphem_class = morphem_class::number;
                number new_number;
                this->input_stream_.putback(c);
                auto pre = this->input_stream_.tellg();
                this->input_stream_ >> new_number;
                position_in_file.position_in_line = input_stream_.tellg() - pre - 1;
                new_morphem.value = std::move(new_number);
                break;
            } else if (isalpha(c)) {
                if (new_morphem.morphem_class != morphem_class::string) {
                    new_morphem.morphem_class = morphem_class::string;
                    new_morphem.value = std::string{};
                }
                boost::get<std::string>(new_morphem.value) += static_cast<char>(c);
            } else if (new_morphem.morphem_class == morphem_class::string) {
                break;
            } else {
                //fail
                break;
            }

        }

        if (new_morphem.morphem_class == PL0::morphem_class::string) {
            std::string as_upper = boost::get<std::string>(new_morphem.value);
            std::for_each(as_upper.begin(), as_upper.end(), toupper);
            if (PL0::keywords.count(as_upper)) {
                new_morphem.morphem_class = PL0::morphem_class::keyword;
                new_morphem.value = std::move(as_upper);
            }
        }


        return new_morphem;
    }

};

std::ostream &operator<<(std::ostream &os, const PL0::morphem &morphem) {
    os << "Morphem class: " << std::setw(10) << morphem.morphem_class
       << " value: \"" << std::setw(15);
    {
        PL0::ostream_visitor os_visitor(os);
        boost::apply_visitor(os_visitor, morphem.value);
    }
    os << "\"";
    os << " Position:" << morphem.position;

    return os;
}

std::ostream &operator<<(std::ostream &os, const PL0::morphem_class &morphem_class) {
    using namespace PL0;
    switch (morphem_class) {
        case morphem_class::empty:
            os << "empty";
            break;
        case morphem_class::string:
            os << "string";
            break;
        case morphem_class::keyword:
            os << "keyword";
            break;
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

std::ostream &operator<<(std::ostream &os, const PL0::position &position) {
    os << "line: " << position.line_number << " column: " << position.position_in_line;
    return os;
}

bool PL0::lexer::end() const {

    return this->input_stream_.eof();
}


