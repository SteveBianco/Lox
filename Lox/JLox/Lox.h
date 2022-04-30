#pragma once
#include <string>
#include <vector>

/*
Implements an interpreter for the Lox language.
*/

class Lox
{
	std::vector<std::string> errors_;

public:
	void run(const std::string& source);
	bool hadError() const;
	const std::vector<std::string>& errors() const;
	void clearErrors();

private:
	void error(int lineNumber, const std::string& message);
	void report(int line, const std::string& where, const std::string& message);
};

