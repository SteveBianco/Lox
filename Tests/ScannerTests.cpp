#include "pch.h"
#include "CppUnitTest.h"
#include "Token.h"
#include "TokenType.h"
#include "Scanner.h"
#include "ErrorRecorder.h"
#include "MockErrorRecorder.h"

#include <vector>
#include <unordered_map>
#include <memory>

using std::vector;
using std::unordered_map;
using std::unique_ptr;
using enum TokenType;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(ScannerTests)
	{
	public:

		TEST_METHOD(AllSingleCharacterTokensAppearOnce)
		{
			const std::string source = "{} () ,. -+ ;*/ = < >";

			MockErrorRecorder errors;
			Scanner scanner{ source, errors };
			const auto& tokens = scanner.scan();

			validateTokenCountsAllEqualOne(tokens);
		}

		TEST_METHOD(AllTokensAppearOnce)
		{
			const std::string source = "<= >= == !=";

			MockErrorRecorder errors;
			Scanner scanner{ source, errors };
			const auto& tokens = scanner.scan();

			const int expectedTokenCount = 5; // inlcudes eof token
			Assert::AreEqual(expectedTokenCount, (int)tokens.size());
			validateTokenCountsAllEqualOne(tokens);
		}

		TEST_METHOD(ShouldIgnoreComment)
		{
			const std::string source = " \" A STRING LITERAL \" // followd by a comment 3*4+5/6";

			MockErrorRecorder errors;
			Scanner scanner{ source, errors };
			const auto& tokens = scanner.scan();

			const int expectedTokenCount = 2; // a string and an eof token
			Assert::AreEqual(expectedTokenCount, (int)tokens.size());
			
			auto counts = countByType(tokens);
			Assert::AreEqual(1, counts[STRING]);
		}

		TEST_METHOD(ShouldScanNumbersAndIdentifiers)
		{
			const std::string source = "x = 1.2 * aa; \n y2 = 3.14 * xyz;";

			MockErrorRecorder errors;
			Scanner scanner{ source, errors };
			const auto& tokens = scanner.scan();

			const int expectedTokenCount = 13; // include eof token
			Assert::AreEqual(expectedTokenCount, (int)tokens.size());

			auto counts = countByType(tokens);
			Assert::AreEqual(4, counts[IDENTIFIER]);
			Assert::AreEqual(2, counts[NUMBER]);
		}

		unordered_map<TokenType, int> countByType(const vector<Token>& tokens)
		{
			unordered_map<TokenType, int> actualCounts;

			for (const auto& token : tokens)
			{
				++actualCounts[token.getType()];
			}

			return actualCounts;
		}

		void validateTokenCounts(const vector<Token>& tokens, const unordered_map<TokenType, int>& expectedCounts)
		{
			unordered_map<TokenType, int> actualCounts;

			for (const auto& token : tokens)
			{
				++actualCounts[token.getType()];
			}

			Assert::IsTrue(actualCounts == expectedCounts);
		}

		void validateTokenCountsAllEqualOne(const vector<Token>& tokens)
		{
			unordered_map<TokenType, int> actualCounts;

			for (const auto& token : tokens)
			{
				++actualCounts[token.getType()];
			}

			for (const auto& entry : actualCounts)
			{
				Assert::AreEqual(1, entry.second);
			}
		}
	};

	
}
