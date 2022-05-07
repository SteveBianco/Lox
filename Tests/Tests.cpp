#include "pch.h"
#include "CppUnitTest.h"
#include "Token.h"
#include "TokenType.h"
#include "Scanner.h"
#include "ErrorRecorder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Token t{ TokenType::AND, "and", 0 };
			Assert::IsTrue(t.getLexeme() == std::string("and"));
		}
	};
}
