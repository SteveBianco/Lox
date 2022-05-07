#pragma once

class Expression;
class BinaryExpression;
class UnaryExpression;
class GroupingExpression;
class LiteralExpression;


class ExpressionVisitor
{
public:
	virtual void visit(const Expression& e) = 0;
	virtual void visit(const BinaryExpression& e) = 0;
	virtual void visit(const UnaryExpression& e) = 0;
	virtual void visit(const GroupingExpression& e) = 0;
	virtual void visit(const LiteralExpression& e) = 0;
};


/*
* Inheritng from this, using CRTP, allows the host to
* be visited by the visitor.
* 
* Usage:
* class MyClass : Accept<SomeVisitor, MyClass>
* {
* }
*/
template<typename Visitor, typename Host>
class Accept
{
public:
	void accept(Visitor& v) const override
	{
		v.visit(static_cast<Host&>(*this));
	}
};
