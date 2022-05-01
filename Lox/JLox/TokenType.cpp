#include "TokenType.h"

using std::string;

// Mighht want to customize output of to_string for TokenType in the future.
// E.G. Eliminate the underscore.
string prettify(const string& in)
{
    return in;
}

std::string to_string(TokenType t)
{
    switch (t)
    {
    case TokenType::LEFT_PAREN: return prettify("LEFT_PAREN");
    case TokenType::RIGHT_PAREN: return prettify("RIGHT_PAREN");
    case TokenType::LEFT_BRACE: return prettify("LEFT_BRACE");
    case TokenType::RIGHT_BRACE: return prettify("RIGHT_BRACE");
    case TokenType::COMMA: return prettify("COMMA");
    case TokenType::DOT: return prettify("DOT");
    case TokenType::MINUS: return prettify("MINUS");
    case TokenType::PLUS: return prettify("PLUS");
    case TokenType::SEMICOLON: return prettify("SEMICOLON");
    case TokenType::SLASH: return prettify("SLASH");
    case TokenType::STAR: return prettify("STAR");
    case TokenType::BANG: return prettify("BANG");
    case TokenType::BANG_EQUAL: return prettify("BANG_EQUAL");
    case TokenType::EQUAL: return prettify("EQUAL");
    case TokenType::EQUAL_EQUAL: return prettify("EQUAL_EQUAL");
    case TokenType::GREATER: return prettify("GREATER");
    case TokenType::GREATER_EQUAL: return prettify("GREATER_EQUAL");
    case TokenType::LESS: return prettify("LESS");
    case TokenType::LESS_EQUAL: return prettify("LESS_EQUAL");
    case TokenType::IDENTIFIER: return prettify("IDENTIFIER");
    case TokenType::STRING: return prettify("STRING");
    case TokenType::NUMBER: return prettify("NUMBER");
    case TokenType::AND: return prettify("AND");
    case TokenType::CLASS: return prettify("CLASS");
    case TokenType::ELSE: return prettify("ELSE");
    case TokenType::FALSE: return prettify("FALSE");
    case TokenType::FUN: return prettify("FUN");
    case TokenType::FOR: return prettify("FOR");
    case TokenType::IF: return prettify("IF");
    case TokenType::NIL: return prettify("NIL");
    case TokenType::OR: return prettify("OR");
    case TokenType::PRINT: return prettify("PRINT");
    case TokenType::RETURN: return prettify("RETURN");
    case TokenType::SUPER: return prettify("SUPER");
    case TokenType::THIS: return prettify("THIS");
    case TokenType::TRUE: return prettify("TRUE");
    case TokenType::VAR: return prettify("VAR");
    case TokenType::WHILE: return prettify("WHILE");
    case TokenType::END_OF_FILE: return prettify("END_OF_FILE");
    }

    return "Unkown token type";
}
