#pragma once
#include <string>
#include <variant>
#include <unordered_map>
#include <memory>
#include <stack>
#include <iostream>

class FunctionDefinitionNode;

class RuntimeContext {
public:
    using Value = std::variant<int, float, std::string>;

    // Variables
    void setVariable(const std::string &name, const Value &value);
    Value getVariable(const std::string &name) const;
    std::string valueToString(const Value &v) const;

    // Functions
    void registerFunction(const std::string &name, std::shared_ptr<FunctionDefinitionNode> func);
    std::shared_ptr<FunctionDefinitionNode> getFunction(const std::string &name) const;

    // Call stack (for function-local variables)
    void pushStackFrame();
    void popStackFrame();

private:
    // top of stack = most recent frame (locals). If empty, globals only.
    using Frame = std::unordered_map<std::string, Value>;
    std::stack<Frame> callStack_;

    std::unordered_map<std::string, Value> globals_;
    std::unordered_map<std::string, std::shared_ptr<FunctionDefinitionNode>> functions_;
};
