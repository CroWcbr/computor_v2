#pragma once

# include "Token.hpp"
# include "Computor_v1_Parser.hpp"

# include <string>
# include <vector>
# include <map>
# include <iostream>

class Computor_v1
{
private:
	std::vector<Token>		_tokens;


	std::string				_input;
	std::map<int, double>	_pol;
	
	std::string				_reduce_form;
	int						_degree;
	std::string				_msg_decision;


	double					_a;
	double					_b;
	double					_c;
	std::string				_x;
	double					_D;

private:
	Computor_v1();
	Computor_v1(Computor_v1 const &copy);
	Computor_v1 &operator=(Computor_v1 const &copy);

	std::string			_check_input(int argc, char **argv);
	void 				_update_polinom();
	void				_update_reduce_form();

	std::string			_clear_arg(double arg) const;
	double				_sqrt(double n) const;
public:
	Computor_v1(std::vector<Token> const &token);
	~Computor_v1();

	void			decision();
	void			polinom_print();
};
