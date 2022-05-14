#include "GroupingExpression.h"

GroupingExpression::GroupingExpression(std::unique_ptr<Expression> expression):
	expression_{std::move(expression)}
{
}
