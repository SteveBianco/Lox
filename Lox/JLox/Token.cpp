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

Token::Token(const std::string& lexeme, bool literalValue, int line) :
	Token(literalValue ? TokenType::TRUE : TokenType::FALSE, lexeme, line)
{
	literal_ = literalValue;
}

Token::Token(const std::string& lexeme, nullptr_t literalValue, int line) :
	Token(TokenType::NIL, lexeme, line)
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

std::optional<LiteralValue> Token::getOptionalValue() const
{
	return literal_;
}

namespace
{
	struct LiteralToString
	{
		std::string operator() (double x) const
		{
			return std::to_string(x);
		}

		std::string operator() (const std::string& str) const
		{
			return str;
		}

		std::string operator() (bool val) const
		{
			return val ? "true" : "false";
		}

		std::string operator() (nullptr_t) const
		{
			return "null";
		}
	};
}

Token::operator std::string() const
{
	std::string str = to_string(type_) + " " + lexeme_;

	auto valueOptional = getOptionalValue();

	if (valueOptional)
	{
		str += " " + std::visit(LiteralToString{}, valueOptional.value());
	}

	return str;
}