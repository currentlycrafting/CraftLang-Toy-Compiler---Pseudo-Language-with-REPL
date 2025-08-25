#pragma once
#include "AstNode.hpp"
#include "runtime/RuntimeContext.hpp"
#include <cstdlib>

class ExitNode : public AstNode {
public:
    void execute(RuntimeContext &ctx) override {
        std::exit(0);
    }
};