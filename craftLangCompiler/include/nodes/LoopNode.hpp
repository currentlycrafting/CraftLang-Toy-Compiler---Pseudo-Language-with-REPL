#pragma once
#include "AstNode.hpp"
#include "runtime/RuntimeContext.hpp"
#include <vector>
#include <memory>

class LoopNode : public AstNode {
public:
    LoopNode(int count, const std::vector<std::shared_ptr<AstNode>> &body)
        : count_(count), body_(body) {}

    void execute(RuntimeContext &ctx) override {
        for (int i = 0; i < count_; ++i) {
            for (auto &stmt : body_) {
                stmt->execute(ctx);
            }
        }
    }
private:
    int count_;
    std::vector<std::shared_ptr<AstNode>> body_;
};
