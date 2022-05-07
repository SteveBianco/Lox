#include "AstPrinter.h"
#include "BinaryExpression.h"
#include "UnaryExpression.h"
#include "GroupingExpression.h"
#include "LiteralExpression.h"

#include <sstream>

namespace
{

}

std::string AstPrinter::print(const Expression& e)
{

	ss.clear();
	e.accept(*this);
	return ss.str();
}

void AstPrinter::visit(const Expression& e)
{
}

void AstPrinter::visit(const BinaryExpression& e)
{
	parenthesize(e.token().getLexeme(), { &e.left(), &e.right() });
}

void AstPrinter::visit(const UnaryExpression& e)
{
	parenthesize(e.token().getLexeme(), { 1, &e.right() });
}

void AstPrinter::visit(const GroupingExpression& e)
{
	parenthesize("group", { 1, &e.expression() });
}

void AstPrinter::visit(const LiteralExpression& e)
{
	ss << e.to_string();
}

void AstPrinter::parenthesize(const std::string& name, const std::vector<const Expression*>& exprs)
{
	ss << "(";

	for (const auto e : exprs)
	{
		ss << " ";
		e->accept(*this);
	}

	ss << ")";
}
