/*! @file lexer.hpp
 *
 */

#ifndef COMPILERBAU_PRAKTIKUM_LEXER_HPP
#define COMPILERBAU_PRAKTIKUM_LEXER_HPP


#include <string>
#include <utility>
#include <fstream>
#include <boost/variant.hpp>


namespace PL0{
    using string = std::string;
    using number = int32_t;

    enum struct morphem_class{
        symbol,
        number,
        identifier,
    };

    struct position {

    };

    struct morphem{
        boost::variant<string,number> value;
        morphem_class morphem_class;
        position position;
    };

    class lexer{
    public:
        lexer(std::ifstream &file);

        bool end() const;
        morphem lex();
        morphem operator()() {return lex();}
        morphem lexGetMorph() const;
        morphem lexNextMorph() {return lex();}

    };
}

std::ostream& operator<< (std::ostream &os, const PL0::morphem& morphem);

std::ostream &operator<<(std::ostream &os, const PL0::morphem_class &morphem_class);



#endif //COMPILERBAU_PRAKTIKUM_LEXER_HPP
