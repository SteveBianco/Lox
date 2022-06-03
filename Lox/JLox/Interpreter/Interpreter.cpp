#include "Interpreter.h"

#include "expressions/BinaryExpression.h"
#include "expressions/UnaryExpression.h"
#include "expressions/GroupingExpression.h"
#include "expressions/LiteralExpression.h"

void Interpreter::evaluate(const Expression& e)
{
	e.accept(*this);
}

void Interpreter::visit(const Expression& e)
{
}

namespace
{
	bool isEqual(const LiteralValue& value1, const LiteralValue& value2)
	{
		return value1 == value2;
	}
}

void Interpreter::visit(const BinaryExpression& e)
{
	evaluate(e.left());
	LiteralValue left = value_;

	evaluate(e.right());
	LiteralValue right = value_;

	switch (e.token().getType())
	{
	case TokenType::BANG_EQUAL:
		value_ = !isEqual(left, right);
		break;

	case TokenType::EQUAL_EQUAL:
		value_ = isEqual(left, right);
		break;

	case TokenType::GREATER:
		value_ = std::get<double>(left) > std::get<double>(right);
		break;

	case TokenType::GREATER_EQUAL:
		value_ = std::get<double>(left) >= std::get<double>(right);
		break;

	case TokenType::LESS:
		value_ = std::get<double>(left) < std::get<double>(right);
		break;

	case TokenType::LESS_EQUAL:
		value_ = std::get<double>(left) <= std::get<double>(right);
		break;

	case TokenType::PLUS:
		if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right))
		{
			value_ = std::get<double>(left) + std::get<double>(right);
		}
		
		if (std::holds_alternative<std::string>(left) && std::holds_alternative<std::string>(right))
		{
			value_ = std::get<std::string>(left) + std::get<std::string>(right);
		}

		break;

	case TokenType::MINUS:
		value_ = std::get<double>(left) - std::get<double>(right);
		break;

	case TokenType::STAR:
		value_ = std::get<double>(left) * std::get<double>(right);
		break;

	case TokenType::SLASH:
		value_ = std::get<double>(left) / std::get<double>(right);
		break;
	}
}

namespace
{
	bool isTruthy(const LiteralValue& value)
	{
		if (std::holds_alternative<bool>(value))
		{
			return std::get<bool>(value);
		}

		if (std::holds_alternative<nullptr_t>(value))
		{
			return false;
		}

		return true;
	}
}

void Interpreter::visit(const UnaryExpression& e)
{
	evaluate(e.right());
	
	switch (e.token().getType())
	{
	case TokenType::MINUS: 
		value_ = -1.0 * std::get<double>(value_); 
		break;

	case TokenType::BANG:
		value_ = ! isTruthy(value_);
		break;
	}
}

void Interpreter::visit(const GroupingExpression& e)
{
	// this sets this.value_
	evaluate(e.expression());
}

void Interpreter::visit(const LiteralExpression& e)
{
	value_ = e.getValue();
}
