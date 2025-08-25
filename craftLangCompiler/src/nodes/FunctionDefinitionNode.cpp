#include "nodes/FunctionDefinitionNode.hpp"
#include "runtime/RuntimeContext.hpp"
#include <iostream>

std::shared_ptr<FunctionDefinitionNode> FunctionDefinitionNode::currentFunction = nullptr;

FunctionDefinitionNode::FunctionDefinitionNode(const std::string &name, const std::vector<std::string> &params)
    : name_(name), params_(params) {}

void FunctionDefinitionNode::execute(RuntimeContext &ctx) {
    // Register function in context
    ctx.registerFunction(name_, shared_from_this());
}

void FunctionDefinitionNode::addBodyLine(std::shared_ptr<AstNode> stmt) {
    if (stmt) body_.push_back(stmt);
}

RuntimeContext::Value FunctionDefinitionNode::call(RuntimeContext &ctx, const std::vector<RuntimeContext::Value> &args) {
    if (args.size() != params_.size()) {
        std::cerr << "[Error] Wrong number of arguments for function " << name_ << "\n";
        return std::string(""); 
    }

    ctx.pushStackFrame();
    for (size_t i = 0; i < params_.size(); ++i)
        ctx.setVariable(params_[i], args[i]);

    RuntimeContext::Value returnVal;
    try {
        for (const auto &stmt : body_)
            stmt->execute(ctx);
    } catch (const std::string &signal) {
        if (signal == "__return")
            returnVal = ctx.getVariable("__return");
        else
            throw; 
    }

    ctx.popStackFrame();
    return returnVal;
}
