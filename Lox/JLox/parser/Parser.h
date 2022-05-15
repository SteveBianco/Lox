#pragma once
#include "Token.h"
#include "expressions/Expression.h"
#include "ErrorRecorder.h"

#include <vector>
#include <memory>
#include <functional>

class Parser
{
	const std::vector<Token>& tokens_;
	int current = 0;
	ErrorRecorder& errorReporter_;

public:
	Parser(const std::vector<Token>& tokens, ErrorRecorder& errorReporter);
	std::unique_ptr<Expression> parse();

private:
	std::unique_ptr<Expression> expression();
	std::unique_ptr<Expression> equality(); 
	std::unique_ptr<Expression> comparison();
	std::unique_ptr<Expression> term();
	std::unique_ptr<Expression> factor();
	std::unique_ptr<Expression> unary();
	std::unique_ptr<Expression> primary();
	std::unique_ptr<Expression> makeBinaryExpression(const std::vector<TokenType>& operations, 
		std::function<std::unique_ptr<Expression>()>&& expressionProducer);

	bool check(TokenType t) const;
	bool match(TokenType t);
	bool match(const std::vector<TokenType>& ts);
	const Token& consume(TokenType t, const std::string& errorMessage);

	const Token& peek() const;
	const Token& previous() const;
	const Token& advance(); bool  isAtEnd() const;

	class ParseError {};
	ParseError error(const Token& token, const std::string& errorMessage);

	void synchronize();
};

