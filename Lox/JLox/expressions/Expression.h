#pragma once

class ExpressionVisitor;

/**
 * Base class for all expressions.
 * Primarily provides ability to accept ExpressionVisitors.
 */
class Expression
{
public:
	virtual void accept(ExpressionVisitor& v) const = 0;

	// Make this an abstract class
	virtual ~Expression() = 0 
	{
	}
};
