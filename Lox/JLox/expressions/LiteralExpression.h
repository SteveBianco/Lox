#pragma once
#include "Expression.h"
#include "Token.h"
#include "ExpressionVisitor.h"

#include <variant>
#include <memory>

/**
* Represents a literal: e.g. a number or a string
*/
class LiteralExpression : public Expression
{
	Token token_;

public:
	LiteralExpression(const Token& token);

	const LiteralValue& getValue() const;

	void accept(ExpressionVisitor& v) const override
	{
		v.visit(*this);
	}

	const Token& token() const;
	std::string to_string() const;
};



