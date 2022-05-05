#pragma once
#include "Expression.h"
#include "Token.h"

#include <memory>

class BinaryExpression : public Expression
{
	std::unique_ptr<Expression> left_, right_;
	Token operator_;
};

