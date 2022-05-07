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
	std::variant<std::string, double> value_;

public:
	void accept(ExpressionVisitor& v) const override
	{
		v.visit(*this);
	}

	std::string to_string() const;
};



