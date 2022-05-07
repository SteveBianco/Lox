#pragma once
#include "ExpressionVisitor.h"

#include <string>
#include <vector>
#include <sstream>

/**
* Implements pretty-printing of expressions.
*/
class AstPrinter : public ExpressionVisitor
{
	std::stringstream ss;

public:
	std::string print(const Expression& e);

	virtual void visit(const Expression& e);
	virtual void visit(const BinaryExpression& e);
	virtual void visit(const UnaryExpression& e);
	virtual void visit(const GroupingExpression& e);
	virtual void visit(const LiteralExpression& e);

private:
	void parenthesize(const std::string& name, const std::vector<const Expression*>& exprs);
};
