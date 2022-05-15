#pragma once
#include "TokenType.h"
#include "Token.h"

#include <string>
#include <vector>
#include <unordered_map>

struct ErrorRecorder;

/**
* Scans a string of source code and converts it to
* a sequence of tokens.
*/
class Scanner
{
	const std::string& source_;
	ErrorRecorder& errorRecorder_;
	std::unordered_map<std::string, TokenType> keywords_;

	std::vector<Token> tokens_;

	// index of first character of token currently being parsed
	int start_ = 0;

	// index of current character being processed
	int current_ = 0;

	// The line currently being parsed.
	// incremented whenever a new line character is encounterd.
	int line_ = 0;

public:
	Scanner(const std::string& source, ErrorRecorder& errorRecorder);
	~Scanner();

	const std::vector<Token>& scan();

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

