#pragma once
#include "Scanner.h"
#include <initializer_list>


class Expression
{
public:
	virtual void evaluate() = 0;
	virtual ~Expression(){}
};


class BinaryExpr : public Expression
{
public:
	BinaryExpr(Expression& left, Expression& right, TokenType type);
	void evaluate() override{}

	virtual ~BinaryExpr(){}
private:
	Expression& left;
	Expression& right;
	TokenType type;
};

class UnaryExpr : public Expression
{
public:
	UnaryExpr(Expression& right, TokenType type);
	void evaluate() override{}

private:
	Expression& right;
	TokenType type;
};

class LiteralExpr : public Expression
{
public:
	LiteralExpr(std::any value) : value(value){}
	void evaluate() override{}

private:
	std::any value;
};

class GroupExpr : public Expression
{
public:
	void evaluate() override{}
};

class InvalidExpr : public Expression
{
public:
	InvalidExpr(const Token token) : token(token){}
	void evaluate() override{}

private:
	Token token;
};


class Parser
{
public:
	std::vector<Expression*> parse(std::vector<Token>);

private:
	bool match(std::initializer_list<TokenType>);

	Token& CurrentToken();
	Token& NextToken();
	Token& PrevToken();

	Expression* checkForEquality();
	Expression* checkForComparison();
	Expression* checkForTerm();
	Expression* checkForFactor();
	Expression* checkForBinary();
	Expression* checkForUnary();
	Expression* checkForPrimary();

private:
	unsigned int currId{0};
	std::vector<Token> tokens;
};
