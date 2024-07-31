#pragma once
#include "Scanner.h"
#include <initializer_list>
#include <string>

using namespace std::literals;

class Expression
{
public:
	virtual void evaluate() = 0;
	virtual ~Expression(){}
};


class BinaryExpr : public Expression
{
public:
	BinaryExpr(Expression* left, Expression* right, TokenType type);
	void evaluate() override{}

	Expression* GetLeft(){return left;}
	Expression* GetRight(){return right;}
	TokenType GetType(){return type;}

	virtual ~BinaryExpr(){}
private:
	Expression* left;
	Expression* right;
	TokenType type;
};

class UnaryExpr : public Expression
{
public:
	UnaryExpr(Expression* right, TokenType type);
	void evaluate() override{}

	Expression* GetRight(){return right;}
	TokenType GetType(){return type;}

private:
	Expression* right;
	TokenType type;
};

class LiteralExpr : public Expression
{
public:
	LiteralExpr(std::any value) : value(value){}
	void evaluate() override{}

	std::any GetValue() {return value;}
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


class ExpressionPrinter
{
public:
	static std::string toString(Expression* expr)
		{
			if(dynamic_cast<BinaryExpr*> (expr) != nullptr)
				return toString(dynamic_cast<BinaryExpr*> (expr));
			else if(dynamic_cast<UnaryExpr*> (expr) != nullptr)
				return toString(dynamic_cast<UnaryExpr*> (expr));
			else if(dynamic_cast<LiteralExpr*> (expr) != nullptr)
				return toString(dynamic_cast<LiteralExpr*> (expr));
			else
				return "ERROR";
		}

	static std::string toString(BinaryExpr* expr)
		{
			return "( "s + tokenTypeToString[expr->GetType()] +
				" " + toString(expr->GetLeft()) + " " + toString(expr->GetRight()) + " )";
		}

	static std::string toString(UnaryExpr* expr)
		{
			return "( "s + tokenTypeToString[expr->GetType()] +
				" " + toString(expr->GetRight()) + " )";
		}

	static std::string toString(LiteralExpr* expr)
		{
			return AnyPrint(expr->GetValue());
		}
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
	Expression* checkForPower();

private:
	unsigned int currId{0};
	std::vector<Token> tokens;
};
