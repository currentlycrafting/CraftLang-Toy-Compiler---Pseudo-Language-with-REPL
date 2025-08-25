#include "runtime/RuntimeContext.hpp"
#include "nodes/FunctionDefinitionNode.hpp"

void RuntimeContext::setVariable(const std::string &name, const Value &value) {
    if (!callStack_.empty()) {
        callStack_.top()[name] = value; // local
    } else {
        globals_[name] = value;         // global
    }
}

RuntimeContext::Value RuntimeContext::getVariable(const std::string &name) const {
    if (!callStack_.empty()) {
        auto it = callStack_.top().find(name);
        if (it != callStack_.top().end()) return it->second;
    }
    auto git = globals_.find(name);
    if (git != globals_.end()) return git->second;

    std::cerr << "[Error] Undefined variable: " << name << "\n";
    return std::string(""); // empty string by default
}

std::string RuntimeContext::valueToString(const Value &v) const {
    if (std::holds_alternative<int>(v))   return std::to_string(std::get<int>(v));
    if (std::holds_alternative<float>(v)) return std::to_string(std::get<float>(v));
    if (std::holds_alternative<std::string>(v)) return std::get<std::string>(v);
    return std::string("");
}

void RuntimeContext::registerFunction(const std::string &name, std::shared_ptr<FunctionDefinitionNode> func) {
    functions_[name] = std::move(func);
}

std::shared_ptr<FunctionDefinitionNode> RuntimeContext::getFunction(const std::string &name) const {
    auto it = functions_.find(name);
    if (it == functions_.end()) return nullptr;
    return it->second;
}

void RuntimeContext::pushStackFrame() {
    callStack_.push(Frame{});
}

void RuntimeContext::popStackFrame() {
    if (!callStack_.empty()) callStack_.pop();
}
