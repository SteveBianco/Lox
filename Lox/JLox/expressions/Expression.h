#pragma once

class ExpressionVisitor;

class Expression
{
public:
	virtual void accept(ExpressionVisitor& v) const = 0;

	// Make this an abstract class
	virtual ~Expression() = 0 
	{
	}
};
