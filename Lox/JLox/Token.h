#pragma once
#include "TokenType.h"
#include <string>

class Token
{
	const TokenType type_;
	const std::string lexeme_;

	//TODO decide how to handle literals. std::variant?

	const int line_;

public:
	Token(TokenType type, const std::string& lexeme, int line);
	~Token() = default;

	operator std::string() const;
};

