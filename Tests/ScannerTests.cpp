#include "pch.h"
#include "CppUnitTest.h"
#include "Token.h"
#include "TokenType.h"
#include "Scanner.h"
#include "ErrorRecorder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	struct MockErrorRecorder : public ErrorRecorder
	{
		int errors = 0;

		void error(int lineNumber, const std::string& message) override
		{
			errors++;
		}
	};

	TEST_CLASS(ScannerTests)
	{
	public:

		TEST_METHOD(ScannerTest1)
		{
			std::string source = "area = (b + c * d)";
			MockErrorRecorder errors;
			Scanner scanner{ source, errors };
			const auto& tokens = scanner.scan();

			Assert::IsTrue(tokens.size() == 10);
		}
	};
}
