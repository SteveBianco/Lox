#include "pch.h"
#include "CppUnitTest.h"
#include "interpreter/interpreter.h"
#include "expressions/BinaryExpression.h"
#include "expressions/LiteralExpression.h"
#include "Scanner.h"
#include "MockErrorRecorder.h"

#include <variant>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(InterpreterTests)
	{
	public:

		TEST_METHOD(TestBinaryExpression)
		{
			const std::string source = "1.5 * 2.0";

			MockErrorRecorder errors;
			Scanner scanner{ source, errors };
			const auto& tokens = scanner.scan();

			auto left = std::make_unique< LiteralExpression>( tokens[0] );
			Token operand = { tokens[1] };
			auto right = std::make_unique< LiteralExpression>(tokens[2]);

			BinaryExpression exp = { operand, std::move(left), std::move(right)};
			
			Interpreter interpreter;
			interpreter.evaluate(exp);
			auto value = interpreter.value();
			Assert::AreEqual(std::get<double>(value), 3.0);
		}
	};
}
