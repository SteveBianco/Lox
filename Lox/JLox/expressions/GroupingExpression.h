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
	Token operator_;

public:
	void accept(ExpressionVisitor& v) const override
	{
		v.visit(*this);
	}

	const Expression& expression() const { return *expression_;  }
	const Token& token() const { return operator_; }
};



