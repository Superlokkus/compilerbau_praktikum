
#include <string>
#include <utility>

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