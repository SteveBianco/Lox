#include "Lox.h"
#include "Scanner.h"

#include <memory>
#include <vector>
#include <iostream>
#include <format>

void Lox::run(const std::string& source)
{
	Scanner scanner{source};
	const auto& tokens = scanner.scan();
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