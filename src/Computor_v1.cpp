#include "../include/Computor_v1.hpp"

Computor_v1::Computor_v1(Value const *val)
{
	if (val->GetType() == value_type::RATIONAL)
	{
		_map[0] = static_cast<const Rational*>(val)->getReal();
		_x = "x";
	}
	else
	{
		_map = static_cast<const Function*>(val)->getMap();
		_x = static_cast<const Function*>(val)->getUnknown();
	}
	_update_polinom_argument();
	_decision();
}

Computor_v1::~Computor_v1() {}

std::string	&Computor_v1::getMSG() { return _msg_decision; }

void Computor_v1::_print_polinom_map()
{
	std::cout << "_print_polinom_map : " << std::endl;
	for (auto &p : _map)
		std::cout << "\t" << p.first << "\t:\t" << p.second << std::endl;
}

void Computor_v1::_update_polinom_argument()
{
	if (_map.size() > 0)
		_degree = _map.rbegin()->first;
	else
		_degree = 0;

	_a = _b = _c = 0;
	if (_map.find(2) != _map.end())
		_a = _map.find(2)->second;
	if (_map.find(1) != _map.end())	
		_b = _map.find(1)->second;
	if (_map.find(0) != _map.end())
		_c = _map.find(0)->second;
	_D = _b * _b + _a * _c * (-4);
}

void Computor_v1::_decision()
{
	if (_degree == 0 && _c == 0)
		_msg_decision = _x + " may be any";
	else if (_degree == 0)
		_msg_decision = "Inequality is wrong : " + std::to_string(_c) + " = 0" ;
	else if (_degree == 1)
		_msg_decision = "The solution is : " + std::to_string(-_c / _b);
	else if (_degree > 2)
		_msg_decision = "The polynomial degree is " + std::to_string(_degree) + ", I can't solve.";
	else
	{
		double part_1;
		if (_b == 0)
			part_1 = 0;
		else
			part_1 = (_b * -1)/(_a * 2);
		double part_2_sqrt = _D / (_a * _a * 2 * 2);
		if (_D < 0)
			_msg_decision = "First solution : " + std::to_string(part_1)  + " + i * " + std::to_string(_ft_sqrt_rat(-part_2_sqrt)) + \
								   "\nSecond solution : " + std::to_string(part_1)  + " - i * " + std::to_string(_ft_sqrt_rat(-part_2_sqrt));
		else if (_D == 0)
			_msg_decision = "The solution is : " + std::to_string(part_1);
		else
			_msg_decision = "First solution : " + std::to_string(part_1 + _ft_sqrt_rat(part_2_sqrt)) + \
								   "\nSecond solution : " + std::to_string(part_1 - _ft_sqrt_rat(part_2_sqrt));
	}
}
