#pragma once
#include "Expression.h"
#include "Token.h"

#include <memory>

class UnaryExpression : public Expression
{
	std::unique_ptr<Expression> right_;
	Token operator_;
};



