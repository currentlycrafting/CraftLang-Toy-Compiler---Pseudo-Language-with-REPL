#pragma once
#include "AstNode.hpp"
#include "runtime/RuntimeContext.hpp"
#include "nodes/FunctionCallNode.hpp" // for evaluateExpression
#include <string>

class ReturnNode : public AstNode {
public:
    explicit ReturnNode(const std::string &expr) : expr_(expr) {}

    void execute(RuntimeContext &ctx) override {
        RuntimeContext::Value val = FunctionCallNode::evaluateExpression(expr_, ctx);
        ctx.setVariable("__return", val); 
        throw std::string("__return");   
    }

private:
    std::string expr_;
};
