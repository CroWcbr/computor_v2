#pragma once

# include "Token.hpp"

# include <string>
# include <vector>
# include <map>

class Computor_v1_Parser
{
private:
	std::map<int, double>	_pol;
	std::string				_x;

private:
	Computor_v1_Parser();
	Computor_v1_Parser(Computor_v1_Parser const &copy);
	Computor_v1_Parser &operator=(Computor_v1_Parser const &copy);

	void _polinom_parse(std::vector<Token> const &token)
	{
		for (int i = 0, znak = 1, arg = 1, degree = 0, len = token.size(); \
				i < len;)
		{
			token_type		type_i = token[i].getType();
			std::string		lexem_i = token[i].getLexem();

			std::cout << i << " : " << lexem_i << std::endl;
			if (lexem_i == "-" || lexem_i == "+" || lexem_i == "*" || lexem_i == "^")
				;
			else if (type_i == token_type::VARIABLE)
			{
				if (_x == "")
					_x = lexem_i;
				if (_x != lexem_i)
					throw std::runtime_error("INPUT ERROR! more then one unknown!");
				if (i < len - 1 && token[i + 1].getLexem() == "^")
				{
					i += 2;
					degree += std::stod(lexem_i.c_str());
				}
				else
					degree++;
			}
			else if (type_i == token_type::DIGIT)
				arg *= std::stod(lexem_i.c_str());

			if (lexem_i == "-" || \
				lexem_i == "+" || \
				i == len - 1)
			{
				std::cout << "\t" << i << " : " << degree << " : " << arg << " : " << znak << std::endl;
				if (_pol.find(degree) != _pol.end())
					_pol[degree] += arg * znak;
				else
					_pol[degree] = arg * znak;
				
				arg = 1;
				degree = 0;
				znak = 1;
				if (lexem_i == "-")
					znak = -1;
			}
			i++;
		}
	}

	void _check_handle_error(std::string msg, int i) const
	{
		// std::string where_error;
		// for (int ii = 0; ii <= i; ii++)
		// 	where_error += _tokens[ii].getLexem();
		// throw std::runtime_error("PARSE ERROR in : " + where_error + " : " + msg);
	}

public:
	Computor_v1_Parser(std::vector<Token> const &token)
	{
		std::cout << "Computor_v1_Parser!!!" << std::endl;
		_polinom_parse(token);

		for (auto s : _pol)
		{
			std::cout << s.first << " : " << s.second << std::endl;
		}
	}

	~Computor_v1_Parser() {};

	std::map<int, double> const getPolinom() const { return _pol; }
	std::string const getX() const { return _x; }

};
