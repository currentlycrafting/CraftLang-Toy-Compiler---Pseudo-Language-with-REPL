#include "nodes/VariableAssignmentNode.hpp"
#include "nodes/FunctionCallNode.hpp"
#include <iostream>
#include <stdexcept>

VariableAssignmentNode::VariableAssignmentNode(const std::string &name,
                                               const std::string &rawValue,
                                               VarType type)
    : name_(name), rawValue_(rawValue), type_(type) {}

void VariableAssignmentNode::execute(RuntimeContext &ctx) {
    RuntimeContext::Value val;

    switch (type_) {
        case VarType::Integer:
            try {
                val = std::stoi(rawValue_);
            } catch (...) {
                std::cerr << "[Error] Invalid integer: " << rawValue_ << "\n";
                return;
            }
            break;

        case VarType::Float:
            try {
                val = std::stof(rawValue_);
            } catch (...) {
                std::cerr << "[Error] Invalid float: " << rawValue_ << "\n";
                return;
            }
            break;

        case VarType::String:
            val = rawValue_;
            break;

        case VarType::Reference:
            val = ctx.getVariable(rawValue_);
            break;

        case VarType::Expression:
            val = FunctionCallNode::evaluateExpression(rawValue_, ctx);
            break;
    }

    ctx.setVariable(name_, val);
}
