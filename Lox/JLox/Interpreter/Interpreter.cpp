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

Interpreter::RunTimeError::RunTimeError(Token token, std::string message):
	token_{token}, message_{message}
{
}


template<typename ValueT>
void Interpreter::validateOperand(const Token& operation, const LiteralValue& operand, const std::string& message)
{
	if (!std::holds_alternative<ValueT>(operand))
		throw RunTimeError(operation, message);
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
		validateOperand<double>(e.token(), left, "Expected numerical value");
		validateOperand<double>(e.token(), right, "Expected numerical value");

		value_ = std::get<double>(left) > std::get<double>(right);
		break;

	case TokenType::GREATER_EQUAL:
		validateOperand<double>(e.token(), left, "Expected numerical value");
		validateOperand<double>(e.token(), right, "Expected numerical value");

		value_ = std::get<double>(left) >= std::get<double>(right);
		break;

	case TokenType::LESS:
		validateOperand<double>(e.token(), left, "Expected numerical value");
		validateOperand<double>(e.token(), right, "Expected numerical value");

		value_ = std::get<double>(left) < std::get<double>(right);
		break;

	case TokenType::LESS_EQUAL:
		validateOperand<double>(e.token(), left, "Expected numerical value");
		validateOperand<double>(e.token(), right, "Expected numerical value");

		value_ = std::get<double>(left) <= std::get<double>(right);
		break;

	case TokenType::PLUS:
		if (std::holds_alternative<double>(left) && std::holds_alternative<double>(right))
		{
			value_ = std::get<double>(left) + std::get<double>(right);
		}
		else if (std::holds_alternative<std::string>(left) && std::holds_alternative<std::string>(right))
		{
			value_ = std::get<std::string>(left) + std::get<std::string>(right);
		}
		else
		{
			throw RunTimeError(e.token(), "Expected two numerical values or two strings");
		}

		break;

	case TokenType::MINUS:
		validateOperand<double>(e.token(), left, "Expected numerical value");
		validateOperand<double>(e.token(), right, "Expected numerical value");
		value_ = std::get<double>(left) - std::get<double>(right);
		break;

	case TokenType::STAR:
		validateOperand<double>(e.token(), left, "Expected numerical value");
		validateOperand<double>(e.token(), right, "Expected numerical value");

		value_ = std::get<double>(left) * std::get<double>(right);
		break;

	case TokenType::SLASH:
		validateOperand<double>(e.token(), left, "Expected numerical value");
		validateOperand<double>(e.token(), right, "Expected numerical value");

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
		validateOperand<double>(e.token(), value_, "Expected numerical value");
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
