#include "Token.h"

Token::Token(TokenType type, const std::string& lexeme, int line):
	type_{type}, lexeme_{lexeme}, line_{line}
{
}

Token::Token(const std::string& lexeme, std::string literalValue, int line):
	Token(TokenType::STRING, lexeme, line)
{
	literal_ = literalValue;
}

Token::Token(const std::string& lexeme, double literalValue, int line) :
	Token(TokenType::NUMBER, lexeme, line)
{
	literal_ = literalValue;
}

TokenType Token::getType() const
{
	return type_;
}

const std::string& Token::getLexeme() const
{
	return lexeme_;
}

int Token::getLineNumber() const
{
	return line_;
}

std::string Token::getStringLiteral() const
{
	return std::get<std::string>(literal_);
}

double Token::getNumericLiteral() const
{
	return std::get<double>(literal_);
}

Token::operator std::string() const
{
	// TODO include type and literal value (if any)
	return lexeme_;
}