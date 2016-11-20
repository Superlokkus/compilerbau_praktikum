/*! @file lexer.hpp
 *
 */

#ifndef COMPILERBAU_PRAKTIKUM_LEXER_HPP
#define COMPILERBAU_PRAKTIKUM_LEXER_HPP


#include <string>
#include <unordered_set>
#include <map>
#include <utility>
#include <fstream>
#include <boost/variant.hpp>


namespace PL0{
    using string = std::string;
    using number = int32_t;
    using special_symbol_id = int;

    const std::unordered_set<std::string> keywords = {"BEGIN", "CALL", "CONST", "DO", "END", "IF", "ODD", "PROCEDURE",
                                                      "THEN", "VAR", "WHILE"};
    const std::map<std::string, special_symbol_id> special_symbol_ids = {{":",  3},
                                                                         {"<",  4},
                                                                         {">",  5},
                                                                         {":=", 6},
                                                                         {"<=", 7},
                                                                         {">=", 8},
                                                                         {"=",  9},
                                                                         {",",  10},
                                                                         {"+",  11},
                                                                         {"-",  12},
                                                                         {"*",  13},
                                                                         {"/",  14},
                                                                         {";",  15},
                                                                         {".",  16},
                                                                         {"(",  17},
                                                                         {")",  18},
                                                                         {"!",  19},
                                                                         {"?",  20},
                                                                         {"#",  21},};

    enum struct morphem_class{
        empty,
        symbol,
        keyword,
        number,
        string,
    };

    struct position {
        size_t line_number; //!< Count from 1
        size_t position_in_line; //!< Count from 1
        position() : line_number(1), position_in_line(1) {}
    };

    struct morphem{
        boost::variant<string, number, special_symbol_id> value;
        morphem_class morphem_class;
        position position;

        morphem() :
                morphem_class(morphem_class::empty) {}
    };

    class lexer{
    public:
        lexer(std::ifstream &&input_stream);

        bool end() const;
        morphem lex();
        morphem operator()() {return lex();}
        morphem lexGetMorph() const;
        morphem lexNextMorph() {return lex();}

    private:
        std::ifstream input_stream_;
        position position_in_file;
    };

    struct ostream_visitor : boost::static_visitor<> {
        ostream_visitor(std::ostream &os) : os(os) {}

        template<typename T>
        void operator()(const T &arg) const {
            os << arg;
        }

    private :
        std::ostream &os;
    };
}

std::ostream& operator<< (std::ostream &os, const PL0::morphem& morphem);

std::ostream &operator<<(std::ostream &os, const PL0::morphem_class &morphem_class);

std::ostream &operator<<(std::ostream &os, const PL0::position &position);


#endif //COMPILERBAU_PRAKTIKUM_LEXER_HPP
