#pragma once
#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix.hpp>
#include <string>
#include <vector>
#include <memory>

#include "nodes/VariableAssignmentNode.hpp"
#include "nodes/PrintNode.hpp"
#include "nodes/FunctionDefinitionNode.hpp"
#include "nodes/FunctionCallNode.hpp"
#include "nodes/ExitNode.hpp"
#include "nodes/ReturnNode.hpp"

namespace qi    = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace px    = boost::phoenix;

template <typename Iterator>
struct CraftLangGrammar : qi::grammar<Iterator, std::vector<std::shared_ptr<AstNode>>(), ascii::space_type> {
    CraftLangGrammar() : CraftLangGrammar::base_type(start) {
        using qi::lit;
        using qi::lexeme;
        using ascii::char_;
        using qi::_1; using qi::_2; using qi::_val;

        identifier %= lexeme[(ascii::alpha | char_('_')) >> *(ascii::alnum | char_('_'))];
        text_tail  %= lexeme[+(char_ - qi::eol)];
        int_val    %= qi::int_;
        float_val  %= qi::float_;
        argument   %= identifier | int_val | float_val | text_tail;

        // variable assignments
        assignInt = (lit("assign") >> lit("integer") >> lit("variable") >> identifier >> lit("to") >> int_val)
            [_val = px::bind([](std::string name, int v) {
                return std::make_shared<VariableAssignmentNode>(name, std::to_string(v),
                    VariableAssignmentNode::VarType::Integer);
            }, _1, _2)];

        assignFloat = (lit("assign") >> lit("float") >> lit("variable") >> identifier >> lit("to") >> float_val)
            [_val = px::bind([](std::string name, float v) {
                return std::make_shared<VariableAssignmentNode>(name, std::to_string(v),
                    VariableAssignmentNode::VarType::Float);
            }, _1, _2)];

        assignString = (lit("assign") >> lit("string") >> lit("variable") >> identifier >> lit("to") >> text_tail)
            [_val = px::bind([](std::string name, std::string val) {
                return std::make_shared<VariableAssignmentNode>(name, val,
                    VariableAssignmentNode::VarType::String);
            }, _1, _2)];

        assignVar = (lit("assign") >> lit("variable") >> identifier >> lit("with") >> argument)
            [_val = px::bind([](std::string name, std::string expr) {
                return std::make_shared<VariableAssignmentNode>(name, expr,
                    VariableAssignmentNode::VarType::Expression);
            }, _1, _2)];

        // print statement
        printVars = (lit("print") >> -(lit("variable")) >> +identifier)
            [_val = px::bind([](std::vector<std::string> vars) {
                return std::make_shared<PrintNode>(vars);
            }, _1)];

        // define function
        defineFunc = (lit("define") >> lit("function") >> identifier
                      >> -(lit("with") >> lit("parameters") >> (identifier % (',' >> *ascii::space))))
            [_val = px::bind([](std::string name, boost::optional<std::vector<std::string>> paramsOpt) {
                std::vector<std::string> params;
                if (paramsOpt) params = *paramsOpt;
                auto func = std::make_shared<FunctionDefinitionNode>(name, params);
                FunctionDefinitionNode::currentFunction = func;
                return func;
            }, _1, _2)];

        // Call function
        callFunc = (lit("call") >> identifier 
                    >> -(lit("using") >> (argument % (',' >> *ascii::space))))
            [_val = px::bind([](std::string name, boost::optional<std::vector<std::string>> argsOpt) {
                std::vector<std::string> args;
                if (argsOpt) args = *argsOpt;
                return std::make_shared<FunctionCallNode>(name, args);
            }, _1, _2)];

        // Return statement
        returnStmt = (lit("return") >> argument)
            [_val = px::bind([](std::string expr) {
                return std::make_shared<ReturnNode>(expr);
            }, _1)];

        // exit
        exitStmt = (lit("exit") >> -(lit("program")))
            [_val = px::bind([](){ return std::make_shared<ExitNode>(); })];

        statement = exitStmt | printVars | assignInt | assignFloat | assignString | assignVar | callFunc | returnStmt;
        start = +(defineFunc | statement);

        qi::on_error<qi::fail>(
            start,
            std::cout << px::val("[Parse Error] Expecting ") << qi::_4
                      << px::val(" here: '") << px::construct<std::string>(qi::_3, qi::_2)
                      << px::val("'\n")
        );
    }

    qi::rule<Iterator, std::string(), ascii::space_type> identifier, text_tail;
    qi::rule<Iterator, int(), ascii::space_type> int_val;
    qi::rule<Iterator, float(), ascii::space_type> float_val;
    qi::rule<Iterator, std::string(), ascii::space_type> argument;

    qi::rule<Iterator, std::shared_ptr<AstNode>(), ascii::space_type> assignInt, assignFloat, assignString, assignVar;
    qi::rule<Iterator, std::shared_ptr<AstNode>(), ascii::space_type> printVars, defineFunc, callFunc, exitStmt, returnStmt;
    qi::rule<Iterator, std::shared_ptr<AstNode>(), ascii::space_type> statement;
    qi::rule<Iterator, std::vector<std::shared_ptr<AstNode>>(), ascii::space_type> start;
};