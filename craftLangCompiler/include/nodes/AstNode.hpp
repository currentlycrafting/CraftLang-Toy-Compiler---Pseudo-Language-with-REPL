#pragma once
#include "runtime/RuntimeContext.hpp"

class AstNode {
public:
    virtual ~AstNode() = default;
    virtual void execute(RuntimeContext &ctx) = 0;
};