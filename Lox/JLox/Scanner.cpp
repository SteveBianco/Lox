#include "Scanner.h"

Scanner::Scanner(const std::string& source):
	source_{source}
{
}

Scanner::~Scanner()
{
}

const std::vector<std::shared_ptr<Token>>& Scanner::scan()
{
	return tokens_;
}
