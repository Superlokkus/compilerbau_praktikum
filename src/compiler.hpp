
#include <string>
#include <utility>
#include <fstream>
#include <boost/variant.hpp>

/*! @brief Simple arithmatic parsing
 *
 * @return If the expression was fully matched and if true the result
 */

using result_t = unsigned;
std::pair<bool,result_t> task1_grammar_lexer(std::string&);

namespace task1_grammar{
    bool expression(std::string& input, result_t& output);
    bool term(std::string& input, result_t& output);
    bool factor(std::string& input, result_t& output);
}


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
        lexer(std::fstream &file);
        morphem lex();
        morphem operator()() {return lex();}
        morphem lexGetMorph() const;
        morphem lexNextMorph() {return lex();}

    };
}