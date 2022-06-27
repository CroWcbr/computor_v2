#pragma once

# include <string>
# include <vector>

# include "Token.hpp"

class Lexer
{
private:
	std::vector<Token>	_tokens;

private: // Forbidden
	Lexer(Lexer const &copy);
	Lexer &operator=(Lexer const &copy);

private:
	void _addToken(std::string &tmp_lexeme)
	{
		_tokens.push_back(Token(tmp_lexeme));
		tmp_lexeme.clear();
	}

	void _check_read_str_or_number(const char &symbol, int &read_number, int &read_str)
	{
		if (read_number == 0 && read_str == 0)
		{
			if (isalpha(symbol))
				read_str = 1;
			if (isdigit(symbol) || symbol == '.')
				read_number = 1;
		}
	}

	void _split(std::string const &input)
	{
		std::string	tmp_lexeme;
		int			read_number = 0;
		int			read_str = 0;

		for (int i = 0, len = input.size(); i < len; i++)
		{
			char symbol = input[i];
			_check_read_str_or_number(symbol, read_number, read_str);
			if (_is_separate_symbol(symbol))
			{
				read_number = read_str = 0;
				if (!(tmp_lexeme.empty()))
					_addToken(tmp_lexeme);
				if (!isspace(symbol))
				{
					tmp_lexeme += symbol;
					if (symbol == '*' && i != len - 1 && input[i + 1] == '*')
						tmp_lexeme +=  input[++i];
					_addToken(tmp_lexeme);
				}
				continue;
			}
			else if (read_number == 1 && isalpha(symbol))
			{
				read_number = 0;
				read_str = 1;
				_addToken(tmp_lexeme);
				tmp_lexeme += '*';
				_addToken(tmp_lexeme);
			}
			tmp_lexeme += symbol;
		}
		if (!(tmp_lexeme.empty()))
			_addToken(tmp_lexeme);
	}

	bool _is_separate_symbol(char symbol)
	{
		return  symbol == '=' || \
				symbol == '+' || \
				symbol == '-' || \
				symbol == '*' || \
				symbol == '/' || \
				symbol == '%' || \
				symbol == '^' || \
				symbol == '(' || \
				symbol == ')' || \
				symbol == '[' || \
				symbol == ']' || \
				symbol == ',' || \
				symbol == ';' || \
				symbol == '?' || \
				isspace(symbol);
	}

	void _print()
	{
		std::cout << "\033[94m";
		std::cout << "LEXER: " << std::endl;
		std::cout << "\t";
		for (const auto &symbol : _tokens)
			std::cout << symbol.getLexem() << " ";
		std::cout <<  std::endl;
		std::cout << "\033[0m";
	}

public:
	Lexer() {};
	~Lexer() {};

	void parsing(std::string const &input)	{ _split(input); }

	std::vector<Token> const	&getTokens() const { return _tokens; }
	void						print() { _print(); };
};
