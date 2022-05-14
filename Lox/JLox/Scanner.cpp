#include "Scanner.h"
#include "ErrorRecorder.h"
#include "Token.h"

#include <cctype>
#include <unordered_map>

namespace
{
	bool isDigit(char c)
	{
		return std::isdigit(c);
	}

	bool isSpace(char c)
	{
		return std::isspace(c);
	}

	bool isAlpha(char c)
	{
		return std::isalpha(c) || c == '_';
	}

	bool isAlphaNumeric(char c)
	{
		return isAlpha(c) || isDigit(c);
	}
}

namespace
{
	std::unordered_map<std::string, TokenType> keywords()
	{
		std::unordered_map<std::string, TokenType> keywords;

		keywords.insert({ "and", TokenType::AND });
		keywords.insert({ "class", TokenType::CLASS });
		keywords.insert({ "else", TokenType::ELSE });
		keywords.insert({ "false", TokenType::FALSE });
		keywords.insert({ "for", TokenType::FOR });
		keywords.insert({ "fun", TokenType::FUN });
		keywords.insert({ "if", TokenType::IF });
		keywords.insert({ "nil", TokenType::NIL });
		keywords.insert({ "or", TokenType::OR });
		keywords.insert({ "print", TokenType::PRINT });
		keywords.insert({ "return", TokenType::RETURN });
		keywords.insert({ "super", TokenType::SUPER });
		keywords.insert({ "this", TokenType::THIS });
		keywords.insert({ "true", TokenType::TRUE });
		keywords.insert({ "var", TokenType::VAR });
		keywords.insert({ "while", TokenType::WHILE });

		return keywords;
	}
}

Scanner::Scanner(const std::string& source, ErrorRecorder& errorRecorder):
	source_{source}, errorRecorder_{ errorRecorder }, keywords_{keywords()}
{

}

Scanner::~Scanner()
{
}

bool Scanner::isAtEnd() const
{
	return current_ >= source_.size();
}

// Returns teh current character and eats it.
char Scanner::advance()
{
	return source_[current_++];
}

// Returns current character but does not eat it.
char Scanner::peek() const
{
	return source_[current_];
}

// Returns one beyond the current character.
char Scanner::peekNext() const
{
	if (current_ + 1 >= source_.size())
		return '\0';

	return source_[current_ + 1];
}

// if the current character matches the specified character,
// eat it and returs its value, otherwise return the null character.
bool Scanner::match(char expected)
{
	if (isAtEnd())
		return false;

	if (source_[current_] != expected)
		return false;

	// Eat the character
	advance();
	return true;
}

std::string Scanner::getLexeme() const
{
	// current_ is the first character we have not
	// yet processed.
	return source_.substr(start_, current_ - start_);
}

void Scanner::addToken(TokenType type)
{
	tokens_.emplace_back(new Token(type, getLexeme(), line_));
}

void Scanner::addLiteralToken(double number)
{
	tokens_.emplace_back(new Token(getLexeme(), number, line_));
}

void Scanner::addLiteralToken(const std::string& str)
{
	tokens_.emplace_back(new Token(getLexeme(), str, line_));
}

void Scanner::string()
{
	// We have already seen the opening '"'.
	// Eat everything up to and including the closing '"'.
	while (peek() != '"' && !isAtEnd())
	{
		if (peek() == '\n')
			line_++;
		advance();
	}

	if (isAtEnd())
	{
		errorRecorder_.error(line_, "unterminated string");
	}

	// eat the closing '"'
	advance();

	std::string str = source_.substr(start_ + 1, current_ - start_ - 1);
	addLiteralToken(str);
}

void Scanner::number()
{
	// eat sequence of digits
	while (std::isdigit(peek()))
	{
		advance();
	}

	// if there is  a decimal point, eat it
	// and the following sequence of digits.
	if (peek() == '.' && isDigit(peekNext()))
	{
		// consume the decimal point
		advance();

		while (isDigit(peek()))
		{
			advance();
		}
	}

	std::string numberStr = source_.substr(start_, current_ - start_);
	addLiteralToken(std::stod(numberStr));
}

void Scanner::identifier()
{
	// Eat a sequence of alphanumeric characters
	while (isAlphaNumeric(peek()) && !isAtEnd())
	{
		advance();
	}

	// is the identifier a reserved word?
	const std::string identifier = source_.substr(start_, current_ - start_);
	const auto reservedWord = keywords_.find(identifier);

	if (reservedWord != keywords_.end())
	{
		addToken(reservedWord->second);
	}
	else
	{
		addToken(TokenType::IDENTIFIER);
	}
}

void Scanner::scanToken()
{
	// First character of the next token
	const char c = advance();

	switch (c)
	{
	// Handle single character tokens
	case '(': addToken(TokenType::LEFT_PAREN); break;
	case ')': addToken(TokenType::RIGHT_PAREN); break;
	case '{': addToken(TokenType::LEFT_BRACE); break;
	case '}': addToken(TokenType::RIGHT_BRACE); break;
	case ',': addToken(TokenType::COMMA); break;
	case '.': addToken(TokenType::DOT); break;
	case '-': addToken(TokenType::MINUS); break;
	case '+': addToken(TokenType::PLUS); break;
	case ';': addToken(TokenType::SEMICOLON); break;
	case '*': addToken(TokenType::STAR); break;

	// Handle tokens that could be single or two characters
		// Note match() will eat the next character if it matches
		// the specified character.
	case '!':
		addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
		break;
	case '=':
		addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
		break;
	case '<':
		addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
		break;
	case '>':
		addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
		break;

	case '/':
		if (match('/'))
		{
			// it's a double slash which starts a comment. 
			// Eat all chars till end of line, leaving the new line
			// so it will get processed and cause the line no. to increment.
			while (peek() != '\n' && !isAtEnd())
			{
				// eat the character
				advance();
			}
		}
		else
		{
			// its just a slash
			addToken(TokenType::SLASH);
		}
		break;

	// Handle string literal
	case '"': string(); break;

	// Encountered new line.
	case '\n': line_++; break;

	default:
		if (isDigit(c))
		{
			// Handle number literal
			number();
		}
		else if (isAlpha(c))
		{
			// Handle identifiers and keywords.
			identifier();
		}
		else
		{
			// Ignore white space - otherwise if we got here it's an error.
			if (!isSpace(c))
			{
				errorRecorder_.error(line_, "unexpected character");
			}
		}
	}
}

const std::vector<std::unique_ptr<Token>>& Scanner::scan()
{
	while (!isAtEnd())
	{
		// First character of next token is first unprocessed character
		start_ = current_;

		// Scan the next token
		scanToken();
	}

	tokens_.emplace_back(new Token(TokenType::END_OF_FILE, "", line_));
	return tokens_;
}

