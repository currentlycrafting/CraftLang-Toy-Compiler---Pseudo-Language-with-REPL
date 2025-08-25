#pragma once
#include "AstNode.hpp"
#include "runtime/RuntimeContext.hpp"
#include "nodes/FunctionCallNode.hpp" // for evaluateExpression
#include <string>

class VariableAssignmentNode : public AstNode {
public:
    enum class VarType { Integer, Float, String, Reference, Expression };

    VariableAssignmentNode(const std::string &name,
                           const std::string &rawValue,
                           VarType type);

    void execute(RuntimeContext &ctx) override;

private:
    std::string name_;
    std::string rawValue_;
    VarType type_;
};
