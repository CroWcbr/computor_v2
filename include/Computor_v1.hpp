#pragma once

# include "main_library.hpp"
# include <string>
# include <map>

class Value;

class Computor_v1
{
private:
	std::map<int, double>		_map;

	std::string					_x;
	int							_degree;
	double						_a;
	double						_b;
	double						_c;
	double						_D;

	std::string					_msg_decision;

private:
	void				_update_polinom_argument();
	void				_decision();

	void				_print_polinom_map();

public:
	Computor_v1() = delete;
	Computor_v1(Computor_v1 const &copy) = delete;
	Computor_v1 &operator=(Computor_v1 const &copy) = delete;

	Computor_v1(Value const *val);
	~Computor_v1();

	std::string	&getMSG();
};
