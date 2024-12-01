#pragma once

#include <memory>
#include <string>
#include <vector>

namespace kiwiparser {

/// @brief Abstract base class for all AST nodes.
class ASTNode {
  public:
    virtual ~ASTNode() = default;
};

/// @brief AST node for a numeric literal.
class NumberNode : public ASTNode {
  public:
    /// @brief The value of the number.
    double value;

    NumberNode(double value)
      : value(value) {}
};

/// @brief AST node for a unary operator.
class UnaryOperatorNode : public ASTNode {
  public:
    /// @brief The operator.
    char op;
    /// @brief The operand.
    std::unique_ptr<ASTNode> operand;
};

/// @brief AST node for a binary operator.
class BinaryOperatorNode : public ASTNode {
  public:
    /// @brief The operator.
    char op;
    /// @brief The left operand.
    std::unique_ptr<ASTNode> left;
    /// @brief The right operand.
    std::unique_ptr<ASTNode> right;

    BinaryOperatorNode(char op, std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right)
      : op(op),
        left(std::move(left)),
        right(std::move(right)) {}
};

/// @brief AST node for a variable.
class VariableNode : public ASTNode {
  public:
    /// @brief The name of the variable.
    std::string name;

    VariableNode(const std::string& name)
      : name(name) {}
};

/// @brief AST node for a function call.
class FunctionCallNode : public ASTNode {
  public:
    /// @brief The name of the function.
    std::string name;
    /// @brief The arguments.
    std::vector<std::unique_ptr<ASTNode>> args;

    FunctionCallNode(const std::string& name, std::vector<std::unique_ptr<ASTNode>> args)
      : name(name),
        args(std::move(args)) {}
};

/// @brief AST node for a function prototype.
class FunctionPrototypeNode : public ASTNode {
  public:
    /// @brief The name of the function.
    std::string name;
    /// @brief The parameters.
    std::vector<std::string> params;

    FunctionPrototypeNode(const std::string& name, std::vector<std::string> params)
      : name(name),
        params(std::move(params)) {}
};

/// @brief AST node for a function definition.
class FunctionNode : public ASTNode {
  public:
    /// @brief The function prototype.
    std::unique_ptr<FunctionPrototypeNode> prototype;
    /// @brief The function body.
    std::unique_ptr<ASTNode> body;

    // /// @brief The return type.
    // std::unique_ptr<TypeNode> return_type;

    FunctionNode(std::unique_ptr<FunctionPrototypeNode> prototype, std::unique_ptr<ASTNode> body)
      : prototype(std::move(prototype)),
        body(std::move(body)) {}
};

} // namespace kiwiparser
