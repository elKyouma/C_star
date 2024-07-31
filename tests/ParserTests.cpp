#include <gtest/gtest.h>
#include "Scanner.h"
#include "Parser.h"


using enum TokenType;

class ParserTests : public testing::Test
{
protected:
	void Validate(){
		Parser parser{};
		ExpressionPrinter printer{};
		auto expressions = parser.parse(tokens);
		auto str = printer.toString(expressions[0]);
		EXPECT_STREQ(str.c_str(), expected.c_str());
	}


protected:
	std::vector<Token> tokens;
	std::string expected;
};

TEST_F(ParserTests, Arythmetics)
{
	//2 + 5 - 8 * 2 ^ 2 / 3;
	tokens = {
		{INT, 2, 0},
		{PLUS, NULL, 0},
		{INT, 5, 0},
		{MINUS, NULL, 0},
		{INT, 8, 0},
		{STAR, NULL, 0},
		{INT, 2, 0},
		{HAT, 2, 0},
		{INT, 2, 0},
		{SLASH, NULL, 0},
		{INT, 3, 0}
	};

	expected = "( PLUS 2 ( MINUS 5 ( STAR 8 ( SLASH ( HAT 2 2 ) 3 ) ) ) )";
	Validate();
}

TEST_F(ParserTests, VariableDeclaration)
{
	//2 + 5 - 8 * 2 ^ 2 / 3;
	std::vector<Token> tokens{
		{INT, 2, 0},
		{PLUS, NULL, 0},
		{INT, 5, 0},
		{MINUS, NULL, 0},
		{INT, 8, 0},
		{STAR, NULL, 0},
		{INT, 2, 0},
		{HAT, 2, 0},
		{INT, 2, 0},
		{SLASH, NULL, 0},
		{INT, 3, 0}
	};

	expected = "( PLUS 2 ( MINUS 5 ( STAR 8 ( SLASH ( HAT 2 2 ) 3 ) ) ) )";

	Validate();
}
