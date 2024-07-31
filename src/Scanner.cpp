#include "Scanner.h"

#include "Terminal.h"

#include <iostream>
#include <cctype>
#include <fstream>
#include <string>
using namespace std::literals;
using enum TokenType;

std::unordered_map<std::string, TokenType> keyWords ={
    {"u8", U8},
    {"u16", U16},
    {"u32", U32},
    {"u64", U64},
    {"s8", S8},
    {"s16", S16},
    {"s32", S32},
    {"s64", S64},
    {"bool", BOOL},
    {"float", FLOAT},
    {"double", DOUBLE},
    {"char", CHAR},
    {"string", STRING},
    {"if", IF},
    {"else", ELSE},
    {"struct", STRUCT},
    {"and", AND},
    {"or", OR},
    {"not", NOT},
    {"for", FOR},
    {"while", WHILE},
    {"NULL", NIL},
    {"true", TRUE},
    {"false", FALSE},
    {"print", PRINT}
};

std::string AnyPrint(const std::any &value)
{
    if (auto x = std::any_cast<int>(&value)) {
        return std::to_string(*x);
    }
    if (auto x = std::any_cast<float>(&value)) {
        return std::to_string(*x);
    }
    if (auto x = std::any_cast<double>(&value)) {
        return std::to_string(*x);
    }
    if (auto x = std::any_cast<std::string>(&value)) {
        return *x;
    }
    if (auto x = std::any_cast<const char*>(&value)) {
        return *x;
    }
    return "invalidType";
}

std::vector<Token> ScanFile(const std::string& filename)
{
    std::ifstream file(filename, std::ifstream::in);
    std::vector<Token> tokens;

	unsigned int lineNumber = 1;

    auto startPos = file.tellg();

    auto matchNextChar = [&](char c)
        {
            if(c == file.peek())
                return true;
            return false;
        };

    auto addToken = [&](TokenType type)
        {
            tokens.push_back( {type, NULL, lineNumber} );
        };

    auto checkForChar = [&]()
        {
            char value;
            file.get(value);
            tokens.push_back( Token{CHAR, value, lineNumber} );
        };

    char curr;
    auto checkForString = [&]()
        {
            bool foundStringEnd = false;
            int length = 0;
            startPos = file.tellg();
            while(!foundStringEnd && file.get(curr))
            {
                if(curr == '"')
                    foundStringEnd = true;
                else
                    length++;
            }

            if(foundStringEnd)
            {
                std::string result;
                result.reserve(length);
                file.seekg(startPos);
                for(int i = 0; i < length; i++)
                    file.get(result[i]);

                file.get(curr); //Skip quotation
                tokens.push_back( Token{TEXT, result, lineNumber} );
            }
            else
                Terminal::Print(filename, lineNumber, "Lack of string end quotation", ERROR);
        };

    auto checkForNumber = [&]()
        {
            bool hasDot = false;
            int length = 0;
            do
            {
                if(curr == '.')
                {
                    if(!hasDot)
                        hasDot = true;
                    else
                    {
                        Terminal::Print(filename, lineNumber, "The number has two comas", ERROR);
                        break;
                    }
                }
                length++;
                file.get(curr);
            } while(std::isdigit(curr) || curr == '.');

            std::string result;
            result.reserve(length);
            file.seekg(startPos);
            for(int i = 0; i < length; i++)
                file.get(result[i]);

            if(hasDot)
            {
                double num = std::stod(result);
                tokens.push_back( Token{REAL, num, lineNumber} );
            }
            else
            {
                long long num = std::stoi(result);
                tokens.push_back( Token{INT, num, lineNumber} );
            }

        };

    auto checkForIdentifier = [&]()
        {
            int length = 0;
            do
            {
                length++;
                file.get(curr);
            } while(std::isalnum(curr) || curr == '_');

            std::string result;
            result.resize(length);
            file.seekg(startPos);
            for(int i = 0; i < length; i++)
                 file.get(result[i]);

            if(keyWords.contains(result.c_str()))
                tokens.push_back( Token{keyWords[result.c_str()], NULL, lineNumber} );
            else
                tokens.push_back( Token{IDENTIFIER, result, lineNumber} );
        };

    while(file.get(curr))
    {
        switch(curr)
        {
        case '(': addToken(LEFT_PAREN); break;
        case ')': addToken(RIGHT_PAREN); break;
        case '[': addToken(LEFT_BRACKET); break;
        case ']': addToken(RIGHT_BRACKET); break;
        case '{': addToken(LEFT_BRACE); break;
        case '}': addToken(RIGHT_BRACE); break;

        case '+':
        {
            matchNextChar('=') ? addToken(PLUS_EQUAL) : addToken(PLUS);
        } break;
        case '-':
        {
            matchNextChar('=') ? addToken(MINUS_EQUAL) : addToken(MINUS);
        } break;
        case '/':
        {
            if(matchNextChar('/'))
                addToken(DSLASH);
            else
                matchNextChar('=') ? addToken(SLASH_EQUAL) : addToken(SLASH);
        } break;
        case '=':
        {
            matchNextChar('=') ? addToken(DEQUAL) : addToken(EQUAL);
        } break;
        case '*':
        {
            matchNextChar('=') ? addToken(STAR_EQUAL) : addToken(STAR);
        } break;
        case '^':
        {
            matchNextChar('=') ? addToken(HAT_EQUAL) : addToken(HAT);
        } break;
        case '>':
        {
            matchNextChar('=') ? addToken(GREATER_EQUAL) : addToken(GREATER);
        } break;
        case '<':
        {
            matchNextChar('=') ? addToken(LESS_EQUAL) : addToken(LESS);
        } break;
        case '.':
        {
            if(isdigit(file.peek()))
                checkForNumber();
            else
                addToken(DOT);
        } break;
        case '?': addToken(QUESTION); break;
        case '!': addToken(NOT); break;
        case '#': addToken(HASH); break;
        case ';': addToken(SEMI); break;
        case ':': addToken(COLON); break;
        case '"': checkForString(); break;
        case '\'': checkForChar(); break;
        case '\n': lineNumber++;
        case '\r':
        case '\t':
        case ' ':
            break;
        default:
        {
            if(std::isdigit(curr))
                checkForNumber();
            else if(std::isalpha(curr) || curr == '_')
                checkForIdentifier();
            else
                Terminal::Print(filename, lineNumber, "Unrecognized character: "s + curr, ERROR);
        } break;

        }

        startPos = file.tellg();
    }

    file.close();
    return tokens;
}
