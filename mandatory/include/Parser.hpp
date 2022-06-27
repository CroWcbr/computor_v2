#pragma once

# include <vector>

# include "Token.hpp"
# include "enum.hpp"

class Parser
{
private:
	lexer_type					_type;

private: // Forbidden
	Parser(Parser const &copy);
	Parser &operator=(Parser const &copy);

private:
	Parser();

	lexer_type _find_type(std::vector<Token> const &tokens)
	{
		int	len = tokens.size();
		if (len < 3) // a = 1 - min nessesary
			throw std::runtime_error("PARSE ERROR! token.size() < 3");
		else if (tokens[len - 1].getType() == token_type::QUESTION && \
				tokens[len - 2].getType() == token_type::EQUAL)
			return lexer_type::SOLVE;
		else if (tokens[len - 1].getType() == token_type::QUESTION && \
				tokens[len - 2].getType() != token_type::EQUAL)
		{
			if (len < 4) // a = 1 ? - min nessesary
				throw std::runtime_error("PARSE ERROR! Polinom token.size() < 4");			
			return lexer_type::POLINOM;
		}
		else if (tokens[0].getType() == token_type::VARIABLE && \
				tokens[1].getType() == token_type::ROUND_BRACET_OPEN)
		{
			if (len < 6) // f(x) = 1 - min nessesary
				throw std::runtime_error("PARSE ERROR! Function token.size() < 6");
			if (!(tokens[0].getType() == token_type::VARIABLE && \
					tokens[1].getType() == token_type::ROUND_BRACET_OPEN && \
					tokens[2].getType() == token_type::VARIABLE && \
					tokens[3].getType() == token_type::ROUND_BRACET_CLOSE && \
					tokens[4].getType() == token_type::EQUAL))
				throw std::runtime_error("PARSE FUNCTION ERROR! TYPE");
			if (tokens[0].getLexem() == tokens[2].getLexem())
				throw std::runtime_error("PARSE FUNCTION ERROR! Function name and variable are same");
			return lexer_type::FUNCTION;
		}
		else if (tokens[0].getType() == token_type::VARIABLE && \
				tokens[1].getType() == token_type::EQUAL && \
				tokens[2].getType() == token_type::SQUARE_BRACET_OPEN)
		{
			if (len < 7) // a = [[1]] - min nessesary
				throw std::runtime_error("PARSE ERROR! Matrix token.size() < 7");
			if (!(tokens[0].getType() == token_type::VARIABLE && \
					tokens[1].getType() == token_type::EQUAL && \
					tokens[2].getType() == token_type::SQUARE_BRACET_OPEN && \
					tokens[3].getType() == token_type::SQUARE_BRACET_OPEN && \
					tokens[len - 2].getType() == token_type::SQUARE_BRACET_CLOSE && \
					tokens[len - 1].getType() == token_type::SQUARE_BRACET_CLOSE))
				throw std::runtime_error("PARSE MATRIX ERROR! TYPE");
			return lexer_type::MATRIX;
		}
		else if (tokens[0].getType() == token_type::VARIABLE && \
				tokens[1].getType() == token_type::EQUAL)
			return lexer_type::VARIABLE;
		else
			throw std::runtime_error("PARSE ERROR! Cannot check type");
	}

	void _print()
	{
		std::cout << "\033[94m";
		std::cout << "PARSER: " << std::endl;
		std::cout << "\t";
		if (_type == lexer_type::SOLVE)
			std::cout << "Solve" << std::endl;
		else if (_type == lexer_type::POLINOM)
			std::cout << "Polinom" << std::endl;
		else if (_type == lexer_type::VARIABLE)
			std::cout << "Variable" << std::endl;
		else if (_type == lexer_type::FUNCTION)
			std::cout << "Function" << std::endl;
		else if (_type == lexer_type::MATRIX)
			std::cout << "Matrix" << std::endl;
		std::cout << "\033[0m";
	}

public:
	Parser(std::vector<Token> const &tokens)
	{
		_type = _find_type(tokens);

	}

	~Parser() {};

	void						print() { _print(); };

	lexer_type const &getType() const { return _type; }
};
