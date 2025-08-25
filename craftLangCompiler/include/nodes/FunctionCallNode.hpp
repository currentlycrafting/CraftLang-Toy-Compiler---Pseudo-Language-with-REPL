#pragma once
#include "AstNode.hpp"
#include "runtime/RuntimeContext.hpp"
#include <string>
#include <vector>

class FunctionCallNode : public AstNode {
public:
    FunctionCallNode(const std::string &name, const std::vector<std::string> &args);

    void execute(RuntimeContext &ctx) override;

    static RuntimeContext::Value evaluateExpression(const std::string &expr, RuntimeContext &ctx);

private:
    std::string name_;
    std::vector<std::string> args_;
};