#include "Lox.h"
#include "Scanner.h"
#include "Token.h"
#include "parser/Parser.h"
#include "expressions/AstPrinter.h"

#include <memory>
#include <vector>
#include <iostream>
#include <format>

void Lox::run(const std::string& source)
{
	Scanner scanner{source, *this};
	const auto& tokens = scanner.scan();

	Parser parser(tokens, *this);
	std::unique_ptr<Expression> expression = parser.parse();

	if (hadError())
		return;

	AstPrinter printer;
	std::cout << printer.print(*expression);
}

bool Lox::hadError() const
{
	return errors_.size() > 0;
}

const std::vector<std::string>& Lox::errors() const
{
	return errors_;
}

void Lox::clearErrors()
{
	errors_.clear();
}

void Lox::error(int lineNumber, const std::string& message)
{
	report(lineNumber, "", message);
}

void Lox::report(int lineNumber, const std::string& where, const std::string& message)
{
    auto error = std::format("[line {}] Error {} {}", lineNumber, where, message);
	errors_.push_back(error);
}

void Lox::error(const Token& token, const std::string& errorMessage)
{
	if (token.getType() == TokenType::END_OF_FILE)
	{
		report(token.getLineNumber(), " at end ", errorMessage);
	}
	else {
		report(token.getLineNumber(), " at '" + token.getLexeme() + "' ", errorMessage);
	}
}