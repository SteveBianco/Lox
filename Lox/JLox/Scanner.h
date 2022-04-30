#pragma once
#include <string>
#include <vector>
#include <memory>

class Token;

class Scanner
{
	const std::string& source_;
	std::vector<std::shared_ptr<Token>> tokens_;


public:
	Scanner(const std::string& source);
	~Scanner();

	const std::vector<std::shared_ptr<Token>>& scan();
};

