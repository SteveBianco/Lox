#pragma once
#include "ErrorRecorder.h"

#include <string>
#include <vector>

/*
Implements an interpreter for the Lox language.
*/

class Lox : public ErrorRecorder
{
	std::vector<std::string> errors_;

public:
	void run(const std::string& source);
	bool hadError() const;
	const std::vector<std::string>& errors() const;
	void clearErrors();

	void error(int lineNumber, const std::string& message) override;

private:
	void report(int line, const std::string& where, const std::string& message);
};

