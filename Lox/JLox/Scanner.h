#pragma once
#include "TokenType.h"

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class Token;
struct ErrorRecorder;

class Scanner
{
	const std::string& source_;
	ErrorRecorder& errorRecorder_;
	std::unordered_map<std::string, TokenType> keywords_;

	std::vector<std::shared_ptr<Token>> tokens_;

	int start_ = 0;
	int current_ = 0;
	int line_ = 0;

public:
	Scanner(const std::string& source, ErrorRecorder& errorRecorder);
	~Scanner();

	const std::vector<std::shared_ptr<Token>>& scan();

private:
	bool isAtEnd() const;
	char advance();
	char peek() const;
	char peekNext() const;
	bool match(char expected);
	std::string getLexeme() const;

	void scanToken();
	void string();
	void number();
	void identifier();
	void addToken(TokenType type);
	void addLiteralToken(double number);
	void addLiteralToken(const std::string& str);
};

