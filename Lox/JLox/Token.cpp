#include "Token.h"

Token::Token(TokenType type, const std::string& lexeme, int line):
	type_{type}, lexeme_{lexeme}, line_{line}
{
}

Token::operator std::string() const
{
	// TODO include type and literal value (if any)
	return lexeme_;
}