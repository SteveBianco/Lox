#include "Scanner.h"
#include "Token.h"

#include <cctype>

Scanner::Scanner(const std::string& source):
	source_{source}
{
}

Scanner::~Scanner()
{
}

const std::vector<std::shared_ptr<Token>>& Scanner::scan()
{
	while (!isAtEnd())
	{
		start_ = current_;
		scanToken();
	}

	tokens_.emplace_back(new Token(TokenType::END_OF_FILE, "", line_));
	return tokens_;
}

bool Scanner::isAtEnd() const
{
	return current_ >= source_.size();
}

char Scanner::advance()
{
	return source_[current_++];
}

char Scanner::peek() const
{
	return source_[current_];
}

char Scanner::peekNext() const
{
	if (current_ + 1 >= source_.size())
		return '\0';

	return source_[current_ + 1];
}

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
	return source_.substr(start_, current_);
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
		//TODO Error: unterminated string
	}

	// eat the closing '"'
	advance();

	std::string str = source_.substr(start_ + 1, current_ - 1);
	addLiteralToken(str);
}

void Scanner::number()
{
	while (std::isdigit(peek()))
	{
		advance();
	}

	if (peek() == '.' && std::isdigit(peekNext()))
	{
		// consume the decimal point
		advance();

		while (std::isdigit(peek()))
		{
			advance();
		}
	}

	std::string numberStr = source_.substr(start_, current_);
	addLiteralToken(std::stod(numberStr));
}

void Scanner::scanToken()
{
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
			while (peek() != '\n' && !isAtEnd())
			{
				advance();
			}
		}
		else
		{
			// its just a slash
			addToken(TokenType::SLASH);
		}
		break;

	case '"': string(); break;

	// Encountered new line.
	case '\n': line_++; break;

	}

	if (std::isdigit(c))
	{
		number();
	}

	// Ignore white space
	if (!std::isspace(c))
	{
		//TODO Error: unexpected character
	}
}
