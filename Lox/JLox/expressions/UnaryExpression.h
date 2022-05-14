#pragma once
#include "Expression.h"
#include "Token.h"
#include "ExpressionVisitor.h"

#include <memory>

/**
* Represents  a unary expression: e.g. !expression.
*/
class UnaryExpression : public Expression
{
	std::unique_ptr<Expression> right_;
	Token operation_;

public:
	UnaryExpression(Token operation, std::unique_ptr<Expression> right);

	void accept(ExpressionVisitor& v) const override
	{
		v.visit(*this);
	}

	const Expression& right() const { return *right_; }
	const Token& token() const { return operation_; }
};



