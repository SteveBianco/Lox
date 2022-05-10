#include "Parser.h"

Parser::Parser(const std::vector<std::unique_ptr<Token>>& tokens):
	tokens_{tokens}
{
}

std::unique_ptr<Expression> Parser::expression()
{
	return equality();
}

std::unique_ptr<Expression> Parser::equality()
{
	auto expr = comparison();

	while (match({ TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL }))
	{

	}

	return std::unique_ptr<Expression>();
}

std::unique_ptr<Expression> Parser::comparison()
{
	return std::unique_ptr<Expression>();
}

std::unique_ptr<Expression> Parser::term()
{
	return std::unique_ptr<Expression>();
}

std::unique_ptr<Expression> Parser::factor()
{
	return std::unique_ptr<Expression>();
}

std::unique_ptr<Expression> Parser::unary()
{
	return std::unique_ptr<Expression>();
}

std::unique_ptr<Expression> Parser::primary()
{
	return std::unique_ptr<Expression>();
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

const Token& Parser::peek() const
{
	// TODO should check current >= tokens_.size()?
	return *tokens_[current];
}

const Token& Parser::previous() const
{
	return *tokens_[current - 1];
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
	return tokens_[current]->getType() == TokenType::END_OF_FILE;
}
