#pragma once
#include "Expression.h"
#include "Token.h"

#include <memory>

class GroupingExpression : public Expression
{
	std::unique_ptr<Expression> expression_;
	Token operator_;
};



