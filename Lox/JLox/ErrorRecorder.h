#pragma once
#include <string>

class Token;

struct ErrorRecorder
{
	virtual void error(int lineNumber, const std::string& message) = 0;
	virtual void error(const Token& token, const std::string& errorMessage) = 0;
};

