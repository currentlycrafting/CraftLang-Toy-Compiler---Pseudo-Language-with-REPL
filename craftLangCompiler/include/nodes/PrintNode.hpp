#pragma once
#include "AstNode.hpp"
#include <vector>
#include <string>

class PrintNode : public AstNode {
public:
    explicit PrintNode(const std::vector<std::string> &items);
    void execute(RuntimeContext &ctx) override;

private:
    std::vector<std::string> items_;
};
