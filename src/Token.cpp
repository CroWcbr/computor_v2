#include "../include/Token.hpp"

Token::Token(std::string const &lexeme, std::map<std::string, Value*> const &val)
{
	_lexeme = lexeme;
	_which_token_type(lexeme);

	if (_type == token_type::VARIABLE && \
			val.find(_lexeme) != val.end() && \
			val.find(_lexeme)->second->GetType() == value_type::FUNCTION)
		_type = token_type::FUNCTION;

	_setRang();
}

Token::Token(std::string const &lexeme, token_type const &type)
{
	_lexeme = lexeme;
	_type = type;
	_setRang();
}

Token::~Token() 
{}

Token::Token(Token const &copy) 
{
	*this = copy;
}

Token &Token::operator=(Token const &copy)
{
	if (this == &copy)
		return *this;
	_lexeme = copy._lexeme;
	_type = copy._type;
	_rang = copy._rang;
	return *this;
}

void Token::_setRang()
{
	if (_lexeme == "+" || _lexeme == "-")
		_rang = 1;
	else if (_lexeme == "*" || _lexeme == "/" || \
			_lexeme == "**" || _lexeme == "%")
		_rang = 2;
	else if (_lexeme == "^")
		_rang = 3;
	else if (_type == token_type::FUNCTION)
		_rang = 4;
	else
		_rang = 0;
}

void Token::_which_token_type(std::string const &lexeme)
{
	if (lexeme[0] == (char)27)
		throw std::runtime_error("TOKEN ERROR! Unknown lexeme");
	else if (lexeme == "+" || lexeme == "-" || \
			lexeme == "**" || lexeme == "*" || \
			lexeme == "/" || lexeme == "%" || \
			lexeme == "^")
		_type = token_type::OPERATION;
	else if (lexeme == "[" || lexeme == "]" || \
			lexeme == "," || lexeme == ";")
		_type = token_type::MATRIX_PARSE;
	else if (lexeme == "(" || lexeme == ")")
		_type = token_type::BRACET;
	else if (_is_digit(lexeme))
		_type = token_type::DIGIT;
	else if (lexeme == "i")
		_type = token_type::COMPLEX;
	else if (_is_func(lexeme))
		_type = token_type::FUNCTION;
	else if (_is_str(lexeme))
		_type = token_type::VARIABLE;
	else
		throw std::runtime_error("TOKEN ERROR! Unknown lexeme : |" + lexeme + "|");
}

bool Token::_is_digit(std::string const &lexeme) const
{
	if (lexeme.front() == '.' || lexeme.back() == '.')
		return false;
	for (const auto &symbol : lexeme)
		if (!isdigit(symbol) && symbol != '.')
			return false;
	return true;
}

bool Token::_is_str(std::string const &lexeme) const
{
	for (const auto &symbol : lexeme)
		if (!isalpha(symbol))
			return false;
	return true;
}

bool Token::_is_func(std::string const &lexeme) const
{
	if (_is_str(lexeme))
	{
		if (lexeme == "sin" || lexeme == "cos" || \
			lexeme == "tan" || lexeme == "ctg" || \
			lexeme == "sqrt" || lexeme == "ln" || lexeme == "log" || \
			lexeme == "abs" || lexeme == "exp" || \
			lexeme == "norm")
			return true;
	}
	return false;
}
