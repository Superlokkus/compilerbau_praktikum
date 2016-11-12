/*! @file lexer.cpp
 *
 */

#include "lexer.hpp"

#include <iomanip>

namespace PL0 {
    lexer::lexer(std::ifstream &&input_stream) : input_stream_(std::move(input_stream)) {

    }

    morphem lexer::lex() {
        auto new_morphem = morphem{};
        new_morphem.morphem_class = morphem_class::empty;

        bool first_no_space_char = false;

        for (std::char_traits<char>::int_type c; (c = this->input_stream_.peek()) != std::char_traits<char>::eof();) {
            position_in_file.position_in_line++;
            if (c == '\n') {
                position_in_file.line_number++;
                position_in_file.position_in_line = 1;
                this->input_stream_.get();
                continue;
            }
            if (isspace(c)) {
                this->input_stream_.get();
                continue;
            }
            if (!first_no_space_char) {
                first_no_space_char = true;
                new_morphem.position = this->position_in_file;
            }

            {
                if (isdigit(c)) {
                    new_morphem.morphem_class = morphem_class::number;
                    number new_number;
                    this->input_stream_ >> new_number;
                    new_morphem.value = std::move(new_number);
                } else if (isalpha(c)) {
                    new_morphem.morphem_class = morphem_class::string;

                    std::string new_string;
                    this->input_stream_ >> new_string;
                    new_morphem.value = std::move(new_string);
                } else {
                    this->input_stream_.get();
                    //fail
                }

                break;
            }
        }


        return new_morphem;
    }

};

std::ostream &operator<<(std::ostream &os, const PL0::morphem &morphem) {
    os << "Morphem class: " << std::setw(10) << morphem.morphem_class
       << " value: \"";
    {
        PL0::ostream_visitor os_visitor(os);
        boost::apply_visitor(os_visitor, morphem.value);
    }
    os << "\"";

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

    return this->input_stream_.eof();
}


