#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>

#include "runtime/RuntimeContext.hpp"
#include "parser/Grammar.hpp"       
#include "nodes/AstNode.hpp"
#include <boost/spirit/include/qi.hpp>

int main() {
    // Open test file
    std::ifstream f("../tests/test_basic.cl");
    if (!f) {
        std::cerr << "Cannot open test file\n";
        return 1;
    }

    // Read entire file into a string
    std::string code((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());

    // Strip comment lines starting with '#'
    std::string code_cleaned;
    std::istringstream iss(code);
    std::string line;
    while (std::getline(iss, line)) {
        if (!line.empty() && line[0] != '#') {
            code_cleaned += line + '\n';
        }
    }

    using It = std::string::const_iterator;
    CraftLangGrammar<It> grammar;
    std::vector<std::shared_ptr<AstNode>> ast;

    It iter = code_cleaned.begin(), end = code_cleaned.end();
    bool ok = boost::spirit::qi::phrase_parse(iter, end, grammar, boost::spirit::ascii::space, ast);

    if (!ok || iter != end) {
        std::cerr << "Parse failed at: '" << std::string(iter, end) << "'\n";
        return 1;
    }

    RuntimeContext ctx;
    for (auto &stmt : ast) {
        stmt->execute(ctx);
    }

    return 0;
}
