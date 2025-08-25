#pragma once
#include <vector>
#include <memory>
#include "nodes/AstNode.hpp"
#include "runtime/RuntimeContext.hpp"

class Executor {
public:
    void execute(const std::vector<std::shared_ptr<AstNode>> &program, RuntimeContext &ctx) {
        for (const auto &stmt : program) {
            if (stmt) stmt->execute(ctx);
        }
    }
};
