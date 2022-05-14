#pragma once
#include "Expression.h"
#include "Token.h"
#include "ExpressionVisitor.h"

#include <memory>

/**
* Represents a parenthesized expression
*/
class GroupingExpression : public Expression
{
	std::unique_ptr<Expression> expression_;

public:
	GroupingExpression(std::unique_ptr<Expression> expression);

	void accept(ExpressionVisitor& v) const override
	{
		v.visit(*this);
	}

	const Expression& expression() const { return *expression_;  }
};



