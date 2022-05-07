#pragma once
#include <string>

struct ErrorRecorder
{
	virtual void error(int lineNumber, const std::string& message) = 0;
};

