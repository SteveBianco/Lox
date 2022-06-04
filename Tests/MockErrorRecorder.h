#pragma once
#include "ErrorRecorder.h"
#include <string>

class Token;

struct MockErrorRecorder : public ErrorRecorder
{
	int errors = 0;

	void error(int lineNumber, const std::string& message) override
	{
		errors++;
	}

	void error(const Token& token, const std::string& errorMessage) override
	{

	}
};