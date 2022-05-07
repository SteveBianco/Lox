#pragma once

class Expression;
class BinaryExpression;
class UnaryExpression;
class GroupingExpression;
class LiteralExpression;

/**
* A base class for all expresssion visitors
*/
class ExpressionVisitor
{
public:
	virtual void visit(const Expression& e) = 0;
	virtual void visit(const BinaryExpression& e) = 0;
	virtual void visit(const UnaryExpression& e) = 0;
	virtual void visit(const GroupingExpression& e) = 0;
	virtual void visit(const LiteralExpression& e) = 0;
};

