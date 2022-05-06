#pragma once
#include "Expression.h"
#include "Token.h"
#include "ExpressionVisitor.h"

#include <memory>

class GroupingExpression : public Expression
{
	std::unique_ptr<Expression> expression_;
	Token operator_;

public:
	void accept(ExpressionVisitor& v) const override
	{
		v.visit(*this);
	}
};



