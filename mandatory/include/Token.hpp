#pragma once

# include <string>
# include <iostream>

# include "enum.hpp"

class Token
{
private:
	std::string		_lexeme;
	token_type		_type;

private: // Forbidden
	Token();

private:
	token_type _which_token_type(std::string const &lexeme)
	{
		if (lexeme == "=")
			return token_type::EQUAL;
		else if (lexeme == "+")
			return token_type::PLUS;
		else if (lexeme == "-")
			return token_type::MINUS;
		else if (lexeme == "**")
			return token_type::MATRIX_MULTIPLICATION;
		else if (lexeme == "*")
			return token_type::MULTIPLICATION;
		else if (lexeme == "/")
			return token_type::DIVISION;
		else if (lexeme == "%")
			return token_type::DIVISION_MOD;
		else if (lexeme == "^")
			return token_type::POWER;
		else if (lexeme == "(")
			return token_type::ROUND_BRACET_OPEN;
		else if (lexeme == ")")
			return token_type::ROUND_BRACET_CLOSE;
		else if (lexeme == "[")
			return token_type::SQUARE_BRACET_OPEN;
		else if (lexeme == "]")
			return token_type::SQUARE_BRACET_CLOSE;
		else if (lexeme == ",")
			return token_type::COMMA;
		else if (lexeme == ";")
			return token_type::SEMICOLON;
		else if (lexeme == "?")
			return token_type::QUESTION;
		else if (lexeme == "i")
			return token_type::COMPLEX;
		else if (_is_digit_int(lexeme))
			return token_type::DIGIT_INT;
		else if (_is_digit_double(lexeme))
			return token_type::DIGIT_DOUBLE;
		else if (_is_str(lexeme))
			return token_type::VARIABLE;
		else
			throw std::runtime_error("TOKEN ERROR! Unknown lexeme : " + lexeme);
	}

	bool _is_digit_int(std::string const &lexeme) const
	{
		for (const auto &symbol : lexeme)
			if (!isdigit(symbol))
				return false;
		return true;
	}

	bool _is_digit_double(std::string const &lexeme) const
	{
		bool point = false;
		for (const auto &symbol : lexeme)
		{
			if (symbol == '.' && point == true)
				return false;
			else if (symbol == '.')
				point = true;
			else if (!isdigit(symbol))
				return false;
		}
		return true;
	}

	bool _is_str(std::string const &lexeme) const
	{
		for (const auto &symbol : lexeme)
			if (!isalpha(symbol))
				return false;
		return true;
	}

public:
	Token(std::string const &lexeme)
	{
		_lexeme = lexeme;
		_type = _which_token_type(lexeme);
	}

	~Token() {}

	Token(Token const &copy) 
	{
		*this = copy;
	}

	Token &operator=(Token const &copy)
	{
		if (this == &copy)
			return *this;
		_lexeme = copy._lexeme;
		_type = copy._type;
		return *this;
	}

	std::string const &getLexem() const { return _lexeme; }
	token_type const &getType() const { return _type; }
};
