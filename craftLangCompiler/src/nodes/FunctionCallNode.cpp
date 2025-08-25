#include "nodes/FunctionCallNode.hpp"
#include "nodes/FunctionDefinitionNode.hpp"
#include "runtime/RuntimeContext.hpp"
#include <iostream>
#include <cctype>

FunctionCallNode::FunctionCallNode(const std::string &name, const std::vector<std::string> &args)
    : name_(name), args_(args) {}

static inline std::string trimCopy(const std::string &s) {
    size_t i = 0, j = s.size();
    while (i < j && std::isspace(static_cast<unsigned char>(s[i]))) ++i;
    while (j > i && std::isspace(static_cast<unsigned char>(s[j-1]))) --j;
    return s.substr(i, j - i);
}

RuntimeContext::Value FunctionCallNode::evaluateExpression(const std::string &expr, RuntimeContext &ctx) {
    std::string t = trimCopy(expr);

    try {
        if (t.find('.') != std::string::npos) return std::stof(t);

        size_t pos = (t.size() && (t[0] == '+' || t[0] == '-')) ? 1 : 0;
        bool isDigits = pos < t.size();
        for (size_t i = pos; i < t.size(); ++i) {
            if (!std::isdigit(static_cast<unsigned char>(t[i]))) { isDigits = false; break; }
        }
        if (isDigits) return std::stoi(t);
    } catch (...) {}

    return ctx.getVariable(t);
}

void FunctionCallNode::execute(RuntimeContext &ctx) {
    auto func = ctx.getFunction(name_);
    if (!func) {
        std::cerr << "[Error] Function '" << name_ << "' not defined.\n";
        return;
    }

    std::vector<RuntimeContext::Value> resolvedArgs;
    for (const auto &a : args_)
        resolvedArgs.push_back(evaluateExpression(a, ctx));

    RuntimeContext::Value ret = func->call(ctx, resolvedArgs);

    // Print return value immediately
    if (std::holds_alternative<int>(ret)) std::cout << std::get<int>(ret) << std::endl;
    else if (std::holds_alternative<float>(ret)) std::cout << std::get<float>(ret) << std::endl;
    else if (std::holds_alternative<std::string>(ret)) std::cout << std::get<std::string>(ret) << std::endl;
}
