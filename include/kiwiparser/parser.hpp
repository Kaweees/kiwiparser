#pragma once

#include "ast.hpp"
#include "lexer.hpp"

namespace kiwiparser {

static Token CurTok;

static Token getNextToken() { return CurTok = gettok(); }

/// @brief The parser.
class Parser {
  public:
    Parser(Lexer& lexer);

    std::unique_ptr<ASTNode> parse();
};

} // namespace kiwiparser
