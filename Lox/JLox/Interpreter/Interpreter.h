#pragma once
#include "expressions/ExpressionVisitor.h"
#include "Token.h"

class Interpreter : public ExpressionVisitor
{
	LiteralValue value_;

public:
	void evaluate(const Expression& e);

	virtual void visit(const Expression& e) override;
	virtual void visit(const BinaryExpression& e) override;
	virtual void visit(const UnaryExpression& e) override;
	virtual void visit(const GroupingExpression& e) override;
	virtual void visit(const LiteralExpression& e) override;

private:

};
