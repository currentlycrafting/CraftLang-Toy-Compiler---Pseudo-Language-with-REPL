#pragma once
#include "AstNode.hpp"
#include "runtime/RuntimeContext.hpp"
#include <string>
#include <vector>
#include <memory>

class FunctionDefinitionNode : public AstNode, public std::enable_shared_from_this<FunctionDefinitionNode> {
public:
    FunctionDefinitionNode(const std::string &name, const std::vector<std::string> &params);

    void execute(RuntimeContext &ctx) override; // registers itself in ctx
    void addBodyLine(std::shared_ptr<AstNode> stmt);

    // Call with resolved args; returns function return value
    RuntimeContext::Value call(RuntimeContext &ctx, const std::vector<RuntimeContext::Value> &args);

    static std::shared_ptr<FunctionDefinitionNode> currentFunction;

    const std::string& name() const { return name_; }
    const std::vector<std::string>& params() const { return params_; }

    // Public getter for function body
    const std::vector<std::shared_ptr<AstNode>>& body() const { return body_; }

private:
    std::string name_;
    std::vector<std::string> params_;
    std::vector<std::shared_ptr<AstNode>> body_;
};
