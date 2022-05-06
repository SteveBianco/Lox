#pragma once
#include "Expression.h"
#include "Token.h"
#include "ExpressionVisitor.h"

#include <variant>
#include <memory>

class LiteralExpression : public Expression
{
	std::variant<std::string, double> value_;

public:
	void accept(ExpressionVisitor& v) const override
	{
		v.visit(*this);
	}
};



