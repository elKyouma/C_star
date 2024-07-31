#include "Parser.h"

#include <string>
#include <vector>
#include "Scanner.h"
#include "Terminal.h"


BinaryExpr::BinaryExpr(Expression* left, Expression* right, TokenType type) :
	left(left), right(right), type(type)
{}
UnaryExpr::UnaryExpr(Expression* right, TokenType type) :
	right(right), type(type)
{}

std::vector<Expression*> Parser::parse(std::vector<Token> tokens)
{
	this->tokens = tokens;
	currId = 0;
	std::vector<Expression*> exprs{};
	switch(CurrentToken().type)
	{
	case TokenType::FOR: /*TODO implement*/ break;
	case TokenType::WHILE: /*TODO implement*/ break;
	case TokenType::STRUCT: /*TODO implement*/ break;
	case TokenType::IF: /*TODO implement*/ break;
	case TokenType::ELSE: /*TODO implement*/ break;
	case TokenType::DSLASH: /*TODO implement*/ break;
	case TokenType::INT:
	case TokenType::REAL:
	case TokenType::TEXT:
	case TokenType::IDENTIFIER: exprs.push_back(checkForEquality()); break;

	case TokenType::SEMI: currId++;
	default: THROW("Unexpected token at the beggining of the line");
	}

	return exprs;
}


Token& Parser::CurrentToken()
{
	return tokens[currId];
}

Token& Parser::NextToken()
{
	return tokens[currId+1];
}

Token& Parser::PrevToken()
{
	return tokens[currId-1];
}

bool Parser::match(std::initializer_list<TokenType> types)
{
	for(const TokenType& type : types)
		if(CurrentToken().type == type)
		{
			currId ++;
			return true;
		}

	return false;
}

Expression* Parser::checkForEquality()
{
	Expression* left = checkForComparison();
	if(match({TokenType::EQUAL, TokenType::HAT_EQUAL, TokenType::STAR_EQUAL,
				TokenType::SLASH_EQUAL, TokenType::PLUS_EQUAL, TokenType::MINUS_EQUAL}))
	{
		auto op = PrevToken().type;
		Expression* right = checkForComparison();
		return new BinaryExpr(left, right, op);
	}

	return left;
}

Expression* Parser::checkForComparison()
{
	Expression* left = checkForTerm();

	if(match({TokenType::NOT_EQUAL, TokenType::LESS_EQUAL, TokenType::GREATER_EQUAL,
				TokenType::GREATER, TokenType::LESS, TokenType::DEQUAL }))
	{
		auto op = PrevToken().type;
		Expression* right = checkForComparison();
		return new BinaryExpr(left, right, op);
	}

	return left;
}

Expression* Parser::checkForTerm()
{
	Expression* left = checkForFactor();

	if(match({TokenType::PLUS, TokenType::MINUS}))
	{
		auto op = PrevToken().type;
		Expression* right = checkForTerm();
		return new BinaryExpr(left, right, op);
	}

	return left;
}

Expression* Parser::checkForFactor()
{
	Expression* left = checkForUnary();

	if(match({TokenType::STAR, TokenType::SLASH}))
	{
		auto op = PrevToken().type;
		Expression* right = checkForFactor();
		return new BinaryExpr(left, right, op);
	}

	return left;
}

Expression* Parser::checkForUnary()
{
	if(match({TokenType::MINUS, TokenType::NOT}))
	{
		auto op = PrevToken().type;
		Expression* right = checkForUnary();
		return new UnaryExpr(right, op);
	}

	return checkForPower();
}
#include <iostream>
Expression* Parser::checkForPower()
{
	Expression* left = checkForPrimary();
	if(match({TokenType::HAT}))
	{
		std::cout << "HAT" << std::endl;
		auto op = PrevToken().type;
		Expression* right = checkForPower();
		return new BinaryExpr(left, right, op);
	}

	return left;
}

Expression* Parser::checkForPrimary()
{
	auto token = CurrentToken();
	currId++;
	switch(token.type)
	{
	case TokenType::TEXT:
	case TokenType::INT:
	case TokenType::REAL:
	case TokenType::FALSE:
	case TokenType::TRUE:
	case TokenType::NIL:
		return new LiteralExpr(token.objectValue);
	case TokenType::LEFT_PAREN:
		return new GroupExpr();
	case TokenType::SEMI:
		THROW("Improper expression, expected literal token"); //TODO line and file
	default:
		return new InvalidExpr(token);
	}
}
