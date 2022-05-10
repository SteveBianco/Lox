#pragma once
#include "Token.h"
#include "expressions/Expression.h"
#include <vector>
#include <memory>

class Parser
{
	const std::vector<std::unique_ptr<Token>>& tokens_;
	int current = 0;

public:
	Parser(const std::vector<std::unique_ptr<Token>>& tokens);

private:
	std::unique_ptr<Expression> expression();
	std::unique_ptr<Expression> equality(); 
	std::unique_ptr<Expression> comparison();
	std::unique_ptr<Expression> term();
	std::unique_ptr<Expression> factor();
	std::unique_ptr<Expression> unary();
	std::unique_ptr<Expression> primary();

	bool check(TokenType t) const;
	bool match(TokenType t);
	bool match(const std::vector<TokenType>& ts);
	bool  isAtEnd() const;

	const Token& peek() const;
	const Token& previous() const;
	const Token& advance();
};

