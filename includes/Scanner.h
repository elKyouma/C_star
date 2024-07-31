#pragma once

#include <vector>
#include <any>
#include <string>
#include <unordered_map>

enum class TokenType
{
	LEFT_PAREN, RIGHT_PAREN, LEFT_BRACKET, RIGHT_BRACKET,
	LEFT_BRACE, RIGHT_BRACE,

	PLUS, MINUS, SLASH, STAR, HAT, DOT, DSLASH,
	QUESTION, SEMI, HASH, COLON,

	NOT, NOT_EQUAL, EQUAL, DEQUAL,
	PLUS_EQUAL, MINUS_EQUAL, SLASH_EQUAL,
	STAR_EQUAL, HAT_EQUAL,
	GREATER, GREATER_EQUAL,
	LESS, LESS_EQUAL,

	IDENTIFIER, REAL, INT, TEXT, TRUE, FALSE, NIL,

	FLOAT, DOUBLE, STRING, CHAR, BOOL,
	U8, S8, U16, S16, U32, S32, U64, S64,

	AND, OR, STRUCT, IF, ELSE,
	PRINT, RETURN, WHILE, FOR
};

static std::unordered_map<TokenType, std::string> tokenTypeToString = {
    {TokenType::LEFT_PAREN, "LEFT_PAREN"},
    {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
    {TokenType::LEFT_BRACKET, "LEFT_BRACKET"},
    {TokenType::RIGHT_BRACKET, "RIGHT_BRACKET"},
    {TokenType::LEFT_BRACE, "LEFT_BRACE"},
    {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
    {TokenType::PLUS, "PLUS"},
    {TokenType::MINUS, "MINUS"},
    {TokenType::SLASH, "SLASH"},
    {TokenType::STAR, "STAR"},
    {TokenType::HAT, "HAT"},
    {TokenType::DOT, "DOT"},
    {TokenType::DSLASH, "DSLASH"},
    {TokenType::COLON, "COLON"},
    {TokenType::QUESTION, "QUESTION"},
    {TokenType::SEMI, "SEMI"},
    {TokenType::HASH, "HASH"},
    {TokenType::NOT, "NOT"},
    {TokenType::NOT_EQUAL, "NOT_EQUAL"},
    {TokenType::EQUAL, "EQUAL"},
    {TokenType::PLUS_EQUAL, "PLUS_EQUAL"},
    {TokenType::MINUS_EQUAL, "MINUS_EQUAL"},
    {TokenType::SLASH_EQUAL, "SLASH_EQUAL"},
    {TokenType::STAR_EQUAL, "STAR_EQUAL"},
    {TokenType::HAT_EQUAL, "HAT_EQUAL"},
    {TokenType::GREATER, "GREATER"},
    {TokenType::GREATER_EQUAL, "GREATER_EQUAL"},
    {TokenType::LESS, "LESS"},
    {TokenType::LESS_EQUAL, "LESS_EQUAL"},
    {TokenType::IDENTIFIER, "IDENTIFIER"},
    {TokenType::REAL, "REAL"},
    {TokenType::INT, "INT"},
    {TokenType::TEXT, "TEXT"},
    {TokenType::TRUE, "TRUE"},
    {TokenType::FALSE, "FALSE"},
    {TokenType::NIL, "NIL"},
    {TokenType::FLOAT, "FLOAT"},
    {TokenType::DOUBLE, "DOUBLE"},
    {TokenType::STRING, "STRING"},
    {TokenType::CHAR, "CHAR"},
    {TokenType::BOOL, "BOOL"},
    {TokenType::U8, "U8"},
    {TokenType::U16, "U16"},
    {TokenType::S16, "S16"},
    {TokenType::U32, "U32"},
    {TokenType::S32, "S32"},
    {TokenType::U64, "U64"},
    {TokenType::S64, "S64"},
    {TokenType::AND, "AND"},
    {TokenType::OR, "OR"},
    {TokenType::STRUCT, "STRUCT"},
    {TokenType::IF, "IF"},
    {TokenType::ELSE, "ELSE"},
    {TokenType::PRINT, "PRINT"},
    {TokenType::RETURN, "RETURN"},
    {TokenType::WHILE, "WHILE"},
    {TokenType::FOR, "FOR"}
};

struct Token
{
	TokenType type;
	std::any objectValue;
	unsigned int line;
};

std::vector<Token> ScanFile(const std::string& filename);
