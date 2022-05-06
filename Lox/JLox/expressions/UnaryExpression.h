#pragma once
#include "Expression.h"
#include "Token.h"
#include "ExpressionVisitor.h"

#include <memory>

class UnaryExpression : public Expression
{
	std::unique_ptr<Expression> right_;
	Token operator_;

public:
	void accept(ExpressionVisitor& v) const override
	{
		v.visit(*this);
	}
};



