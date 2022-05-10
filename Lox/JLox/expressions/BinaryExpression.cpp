#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(Token operation, 
	std::unique_ptr<Expression> lhs, 
	std::unique_ptr<Expression> rhs):
	operation_{operation},
	left_{std::move(lhs)},
	right_{std::move(rhs)}
{
}