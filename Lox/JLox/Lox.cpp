#include "Lox.h"
#include "Scanner.h"

#include <memory>
#include <vector>

void Lox::run(const std::string& source)
{
	Scanner scanner{source};
	const auto& tokens = scanner.scan();
}
