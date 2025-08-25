#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "runtime/RuntimeContext.hpp"
#include "parser/Grammar.hpp"
#include "nodes/AstNode.hpp"
#include "nodes/ExitNode.hpp"
#include "nodes/FunctionDefinitionNode.hpp"
#include "nodes/LoopNode.hpp"      // new loop node
#include "nodes/ReturnNode.hpp"    // new return node

// Helper: parse a single line into AST nodes using the grammar
template <typename Grammar, typename It>
bool parseLine(const std::string &line, Grammar &grammar, std::vector<std::shared_ptr<AstNode>> &out) {
    out.clear();
    It it = line.begin();
    It end = line.end();
    bool ok = phrase_parse(it, end, grammar, ascii::space, out);
    return ok && (it == end);
}

int main() {
    std::cout << "CraftLang REPL. Type 'exit' to quit.\n";

    RuntimeContext ctx;
    using It = std::string::const_iterator;
    CraftLangGrammar<It> grammar;

    while (true) {
        std::cout << "> ";
        std::string line;
        if (!std::getline(std::cin, line)) break; // EOF
        if (line.empty()) continue;

        // --- Handle function definitions ---
        if (line.rfind("define function", 0) == 0) {
            std::vector<std::string> funcLines;
            funcLines.push_back(line);

            while (true) {
                std::cout << "... ";
                std::string bodyLine;
                if (!std::getline(std::cin, bodyLine)) break; // EOF mid-function
                if (bodyLine == "end" || bodyLine == "end function") break;
                funcLines.push_back(bodyLine);
            }

            // Parse lines and attach statements to current function
            for (const auto &l : funcLines) {
                std::vector<std::shared_ptr<AstNode>> nodes;
                if (!parseLine<CraftLangGrammar<It>, It>(l, grammar, nodes)) {
                    std::cerr << "Parse failed at: '" << l << "'\n";
                    FunctionDefinitionNode::currentFunction.reset();
                    break;
                }

                for (auto &node : nodes) {
                    if (auto current = FunctionDefinitionNode::currentFunction) {
                        auto header = std::dynamic_pointer_cast<FunctionDefinitionNode>(node);
                        if (header) {
                            header->execute(ctx);
                        } else {
                            current->addBodyLine(node);
                        }
                    } else {
                        node->execute(ctx);
                    }
                }
            }

            FunctionDefinitionNode::currentFunction.reset();
            continue;
        }

        // --- Handle repeat loops ---
        if (line.rfind("repeat", 0) == 0) {
            int count = 0;
            try {
                size_t pos = line.find("times");
                if (pos != std::string::npos) {
                    count = std::stoi(line.substr(7, pos - 7));
                }
            } catch (...) {
                std::cerr << "[Error] Invalid repeat count\n";
                continue;
            }

            std::vector<std::shared_ptr<AstNode>> body;
            while (true) {
                std::cout << "... ";
                std::string bodyLine;
                if (!std::getline(std::cin, bodyLine)) break;
                if (bodyLine == "end") break;

                std::vector<std::shared_ptr<AstNode>> nodes;
                if (!parseLine<CraftLangGrammar<It>, It>(bodyLine, grammar, nodes)) {
                    std::cerr << "Parse failed at: '" << bodyLine << "'\n";
                    break;
                }
                body.insert(body.end(), nodes.begin(), nodes.end());
            }

            auto loopNode = std::make_shared<LoopNode>(count, body);
            loopNode->execute(ctx);
            continue;
        }

        // --- Normal single-line parse ---
        std::vector<std::shared_ptr<AstNode>> ast;
        if (!parseLine<CraftLangGrammar<It>, It>(line, grammar, ast)) {
            std::cerr << "Parse failed at: '" << line << "'\n";
            continue;
        }

        // Execute nodes; if ExitNode encountered, quit
        for (auto &stmt : ast) {
            if (!stmt) continue;
            if (dynamic_cast<ExitNode*>(stmt.get()) != nullptr) {
                std::cout << "Goodbye!\n";
                return 0;
            }
            try {
                stmt->execute(ctx);
            } catch (const std::string &signal) {
                if (signal != "__return") throw; // propagate unexpected signals
            }
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}