#pragma once

#include <vector>
#include <any>
#include <string>
#include <unordered_map>

enum TokenType
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
    {LEFT_PAREN, "LEFT_PAREN"}, {RIGHT_PAREN, "RIGHT_PAREN"},
    {LEFT_BRACKET, "LEFT_BRACKET"}, {RIGHT_BRACKET, "RIGHT_BRACKET"},
    {LEFT_BRACE, "LEFT_BRACE"}, {RIGHT_BRACE, "RIGHT_BRACE"},
    {PLUS, "PLUS"}, {MINUS, "MINUS"}, {SLASH, "SLASH"}, {STAR, "STAR"},
    {HAT, "HAT"}, {DOT, "DOT"}, {DSLASH, "DSLASH"}, {COLON, "COLON"},
    {QUESTION, "QUESTION"}, {SEMI, "SEMI"}, {HASH, "HASH"},
    {NOT, "NOT"}, {NOT_EQUAL, "NOT_EQUAL"}, {EQUAL, "EQUAL"},
    {DEQUAL, "DEQUAL"},
    {PLUS_EQUAL, "PLUS_EQUAL"}, {MINUS_EQUAL, "MINUS_EQUAL"},
    {SLASH_EQUAL, "SLASH_EQUAL"},
    {STAR_EQUAL, "STAR_EQUAL"}, {HAT_EQUAL, "HAT_EQUAL"},
    {GREATER, "GREATER"}, {GREATER_EQUAL, "GREATER_EQUAL"},
    {LESS, "LESS"}, {LESS_EQUAL, "LESS_EQUAL"},
    {IDENTIFIER, "IDENTIFIER"}, {REAL, "REAL"}, {INT, "INT"},
    {TEXT, "TEXT"}, {TRUE, "TRUE"}, {FALSE, "FALSE"}, {NIL, "NIL"},
    {FLOAT, "FLOAT"}, {DOUBLE, "DOUBLE"}, {STRING, "STRING"},
    {CHAR, "CHAR"}, {BOOL, "BOOL"},
    {U8, "U8"}, {S8, "S8"}, {U16, "U16"}, {S16, "S16"},
    {U32, "U32"}, {S32, "S32"}, {U64, "U64"}, {S64, "S64"},
    {AND, "AND"}, {OR, "OR"}, {STRUCT, "STRUCT"}, {IF, "IF"},
    {ELSE, "ELSE"}, {PRINT, "PRINT"}, {RETURN, "RETURN"},
    {WHILE, "WHILE"}, {FOR, "FOR"}
};

struct Token
{
	TokenType type;
	std::any objectValue;
	unsigned int line;
};

std::vector<Token> ScanFile(const std::string& filename);
