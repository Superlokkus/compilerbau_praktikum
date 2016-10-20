
#include "compiler.hpp"

std::pair<bool,result_t> task1_grammar_lexer(std::string& input) {
    result_t output = 0;
    bool parsed = task1_grammar::expression(input, output);
    return std::make_pair(parsed,output);
}

namespace task1_grammar{
    bool expression(std::string& input, result_t& output) {
        if (!term(input, output)) {
            return false;
        }
        if (input.empty()){
            return true;
        } else if (input.at(0) == '+') { //look ahead
            input.erase(input.begin());
            result_t output2 = 0;
            if (!expression(input, output2))
                return false;
            output += output2;
        }
        return true;
    }
    bool term(std::string& input, result_t& output) {
        if (!factor(input,output)){
            return false;
        }
        if (input.empty()){
            return true;
        } else if (input.at(0) == '*'){
            input.erase(input.begin());
            result_t output2 = 1;
            if (!term(input, output2)){
                return false;
            }
            output *= output2;
            return true;
        }
        return true;
    }
    bool factor(std::string& input, result_t& output) {
        if (input.empty()){
            return false;
        }
        if (input.at(0) == '('){
            input.erase(input.begin());
            if (!expression(input,output) || input.empty() || input.at(0) != ')'){
                return false;
            }
            input.erase(input.begin());
            return true;
        } else {
            try {
                size_t pos = 0;
                auto number = std::stoll(input, &pos, 10);
                output = number;
                input.erase(input.begin(),input.begin()+pos);
                return true;
            } catch(...){
                return false;
            }
        }
        return false;
    }
}