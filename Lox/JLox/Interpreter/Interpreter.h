#pragma once
#include "expressions/ExpressionVisitor.h"
#include "Token.h"

#include <string>

class Interpreter : public ExpressionVisitor
{
	LiteralValue value_;

public:
	void evaluate(const Expression& e);
	const LiteralValue& value() const { return value_; }

	virtual void visit(const Expression& e) override;
	virtual void visit(const BinaryExpression& e) override;
	virtual void visit(const UnaryExpression& e) override;
	virtual void visit(const GroupingExpression& e) override;
	virtual void visit(const LiteralExpression& e) override;

private:
	struct RunTimeError
	{
		Token token_;
		std::string message_;

		RunTimeError(Token token, std::string message);
	};

	// Validates whether the token has a literal value of the specified type.
	// If not, throws RunTimeError.
	template<typename ValueT>
	void validateOperand(const Token& operation, const LiteralValue& operand, const std::string& message);
};

