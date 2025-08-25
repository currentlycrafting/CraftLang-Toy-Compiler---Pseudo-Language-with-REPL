#include "nodes/PrintNode.hpp"
#include <iostream>

PrintNode::PrintNode(const std::vector<std::string> &items)
    : items_(items) {}

void PrintNode::execute(RuntimeContext &ctx) {
    for (size_t i = 0; i < items_.size(); ++i) {
        RuntimeContext::Value v = ctx.getVariable(items_[i]);
        std::cout << ctx.valueToString(v);
        if (i + 1 < items_.size()) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}
