#include "Parser.h"
#include "expressions/BinaryExpression.h"
#include "expressions/UnaryExpression.h"
#include "expressions/GroupingExpression.h"
#include "expressions/LiteralExpression.h"


Parser::Parser(const std::vector<Token>& tokens, ErrorRecorder& errorReporter):
	tokens_{ tokens }, errorReporter_{ errorReporter }
{
}

std::unique_ptr<Expression> Parser::parse()
{
	try
	{
		return expression();
	}
	catch (Parser::ParseError)
	{
		return nullptr;
	}
}

std::unique_ptr<Expression> Parser::expression()
{
	return equality();
}

// equality -> comparison ( '==' | '!=' ) comparison 
std::unique_ptr<Expression> Parser::equality()
{
	std::unique_ptr<Expression> expr = comparison();

	while (match({ TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL }))
	{
		// eith == or !=
		const Token& operation = previous();
		std::unique_ptr<Expression> rhs = comparison();
		expr = std::make_unique<BinaryExpression>(operation, std::move(expr), std::move(rhs));
	}

	return expr;
}

// comparison-> term ('>' | '>=' | '<' | '<=') term
std::unique_ptr<Expression> Parser::comparison()
{
	std::unique_ptr<Expression> expr = term();

	while (match({ TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL }))
	{
		// one of > , >= , < , <= 
		const Token& operation = previous();
		std::unique_ptr<Expression> rhs = term();
		expr = std::make_unique<BinaryExpression>(operation, std::move(expr), std::move(rhs));
	}

	return expr;
}

// term -> factor ( '+' | '-' ) factor
std::unique_ptr<Expression> Parser::term()
{
	std::unique_ptr<Expression> expr = factor();

	while (match({ TokenType::PLUS, TokenType::MINUS }))
	{
		// eith + or -
		const Token& operation = previous();
		std::unique_ptr<Expression> rhs = factor();
		expr = std::make_unique<BinaryExpression>(operation, std::move(expr), std::move(rhs));
	}

	return expr;
}

// factor -> unary ( "*' | '/' ) unary
std::unique_ptr<Expression> Parser::factor()
{
	std::unique_ptr<Expression> expr = unary();

	while (match({ TokenType::STAR, TokenType::SLASH }))
	{
		// eith * or /
		const Token& operation = previous();
		std::unique_ptr<Expression> rhs = unary();
		expr = std::make_unique<BinaryExpression>(operation, std::move(expr), std::move(rhs));
	}

	return expr;
}

// unary -> ( '!' | '-'  ) unary | primary
std::unique_ptr<Expression> Parser::unary()
{
	if (match({ TokenType::BANG , TokenType::MINUS }))
	{
		const Token& operation = previous();
		std::unique_ptr<Expression> rhs = unary();
		return std::make_unique<UnaryExpression>(operation, std::move(rhs));
	}
	else 
	{
		return primary();
	}
}

// 
std::unique_ptr<Expression> Parser::primary()
{
	// Parse number or string literals, 'true', 'false' and 'nil'.
	if (match({TokenType::NUMBER, TokenType::STRING, TokenType::TRUE, TokenType::FALSE, TokenType::NIL}))
	{
		// the literal is defined by its corresponding token
		return std::make_unique<LiteralExpression>(previous());
	}

	// Parse '(' expr ')'
	if (match(TokenType::LEFT_PAREN))
	{
		std::unique_ptr<Expression> expr = expression();

		consume(TokenType::RIGHT_PAREN, "Expected ')'");

		return std::make_unique<GroupingExpression>(std::move(expr));
	}

	throw error(peek(), "Expect expression");
}

bool Parser::match(TokenType t)
{
	std::initializer_list<TokenType> list = { t };
	return match(list);
}

bool Parser::match(const std::vector<TokenType>& ts) 
{
	for (auto type : ts)
	{
		if (check(type))
		{
			advance();
			return true;
		}
	}
	return false;
}

const Token& Parser::consume(TokenType t, const std::string& errorMessage)
{
	if (check(t))
		return advance();

	throw error(peek(), errorMessage);
}

Parser::ParseError Parser::error(const Token& token, const std::string& errorMessage)
{
	errorReporter_.error(token, errorMessage);
	return ParseError();
}

const Token& Parser::peek() const
{
	// TODO should check current >= tokens_.size()?
	return tokens_[current];
}

const Token& Parser::previous() const
{
	return tokens_[current - 1];
}

bool Parser::check(TokenType t) const
{
	if (isAtEnd())
		return false;
	
	return peek().getType() == t;
}

const Token& Parser::advance()
{
	if (!isAtEnd())
	{
		current++;
	}

	return previous();
}

bool Parser::isAtEnd() const
{
	// TODO should check current >= tokens_.size()?
	return tokens_[current].getType() == TokenType::END_OF_FILE;
}

void Parser::synchronize() {
	advance();

	while (!isAtEnd()) {
		if (previous().getType() == TokenType::SEMICOLON) 
			return;

		switch (peek().getType()) 
		{
		case TokenType::CLASS:
		case TokenType::FUN:
		case TokenType::VAR:
		case TokenType::FOR:
		case TokenType::IF:
		case TokenType::WHILE:
		case TokenType::PRINT:
		case TokenType::RETURN:
			return;
		}

		advance();
	}
}