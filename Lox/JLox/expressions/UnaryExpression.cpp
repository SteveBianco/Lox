#include "UnaryExpression.h"

UnaryExpression::UnaryExpression(Token operation, std::unique_ptr<Expression> right):
	operation_{operation}, right_{std::move(right)}
{
}
