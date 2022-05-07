#pragma once
#include "TokenType.h"
#include <string>
#include <variant>

class Token
{
	const TokenType type_;
	const std::string lexeme_;

	std::variant<std::string, double> literal_;
	 
	const int line_;

public:
	// Constructs a generic token, i.e. not a lteral type.
	Token(TokenType type, const std::string& lexeme, int line);

	// Constructs a token representing a string literal.
	Token(const std::string& lexeme, std::string literalValue, int line);

	// Constructs a token representing a numeric literal.
	Token(const std::string& lexeme, double literalValue, int line);

	Token(const Token&) = default;
	~Token() = default;

	TokenType getType() const;
	const std::string& getLexeme() const;
	int getLineNumber() const;

	// Throws unless token type is STRING.
	std::string getStringLiteral() const;
	
	// Throws unless token type is NUMBER
	double getNumericLiteral() const;

	operator std::string() const;
};

