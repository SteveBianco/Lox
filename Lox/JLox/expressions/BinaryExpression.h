#pragma once
#include "Expression.h"
#include "Token.h"
#include "ExpressionVisitor.h"

#include <memory>

/**
*  Represents a binary expression, e.g. two expressions combined 
* addording to an operator: e.g. a+b or a*b.
*/
class BinaryExpression : public Expression
{
	std::unique_ptr<Expression> left_, right_;
	Token operator_;

public:
	void accept(ExpressionVisitor& v) const override
	{
		v.visit(*this);
	}

	const Expression& left() const { return *left_; }
	const Expression& right() const { return *right_; }
	const Token& token() const { return operator_; }
};

