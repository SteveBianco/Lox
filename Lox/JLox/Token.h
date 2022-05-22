#pragma once
#include "TokenType.h"
#include <string>
#include <variant>
#include <optional>

using LiteralValue = std::variant<std::string, double, bool, nullptr_t>;

class Token
{
	const TokenType type_;
	const std::string lexeme_;

	std::optional<LiteralValue> literal_;
	 
	const int line_;

public:
	// Constructs a generic token, i.e. not a lteral type.
	Token(TokenType type, const std::string& lexeme, int line);

	// Constructs a token representing a string literal.
	Token(const std::string& lexeme, std::string literalValue, int line);

	// Constructs a token representing a numeric literal.
	Token(const std::string& lexeme, double literalValue, int line);

	Token(const std::string& lexeme, bool literalValue, int line);
	Token(const std::string& lexeme, nullptr_t literalValue, int line);

	Token(const Token&) = default;
	~Token() = default;

	TokenType getType() const;
	const std::string& getLexeme() const;
	int getLineNumber() const;

	// Returns non-empty optional if the token represents a literal value.
	std::optional<LiteralValue> getOptionalValue() const;

	operator std::string() const;
};

