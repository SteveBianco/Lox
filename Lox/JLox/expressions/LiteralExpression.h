#pragma once
#include "Expression.h"
#include "Token.h"

#include <variant>
#include <memory>

class LiteralExpression : public Expression
{
	std::variant<std::string, double> value_;
};



