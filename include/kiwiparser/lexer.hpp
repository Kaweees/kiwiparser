#pragma once

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace kiwiparser {
// An enum representing the type of token
enum class Token {
  // End of file
  TOKEN_EOF,

  // Commands
  TOKEN_DEF,
  TOKEN_EXTERN,

  // Modifiers
  TOKEN_PUBLIC,
  TOKEN_PRIVATE,
  TOKEN_EXPORT,

  // Primary expressions
  TOKEN_IDENTIFIER,
  TOKEN_NUMBER,

  // Operators
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_ASTERISK,
  TOKEN_SLASH,

  // Punctuation
  TOKEN_LPAREN,
  TOKEN_RPAREN,

  // Invalid token
  TOKEN_INVALID,
};

static std::string IdentifierStr;
static double NumVal;

/// gettok - Return the next token from standard input.
static Token gettok() {
  static int LastChar = ' ';

  // Skip any whitespace.
  while (isspace(LastChar)) LastChar = getchar();

  if (isalpha(LastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
    IdentifierStr = LastChar;
    while (isalnum((LastChar = getchar()))) IdentifierStr += LastChar;

    if (IdentifierStr == "def") return Token::TOKEN_DEF;
    if (IdentifierStr == "extern") return Token::TOKEN_EXTERN;
    return Token::TOKEN_IDENTIFIER;
  }

  if (isdigit(LastChar) || LastChar == '.') { // Number: [0-9.]+
    std::string NumStr;
    do {
      NumStr += LastChar;
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');

    NumVal = strtod(NumStr.c_str(), nullptr);
    return Token::TOKEN_NUMBER;
  }

  if (LastChar == '#') {
    // Comment until end of line.
    do LastChar = getchar();
    while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

    if (LastChar != EOF) return gettok();
  }

  // Check for end of file.  Don't eat the EOF.
  if (LastChar == EOF) return Token::TOKEN_EOF;

  // Otherwise, return an invalid token
  return Token::TOKEN_INVALID;
}

// // Operators
// const std::map<std::string, Token> OPERATORS = {
//     {"+", Token::TOKEN_PLUS},
//     {"-", Token::TOKEN_MINUS},
//     {"*", Token::TOKEN_ASTERISK},
//     {"/", Token::TOKEN_SLASH},
// };
} // namespace kiwiparser
