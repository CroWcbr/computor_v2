#include "../include/Computation.hpp"

Computation::Computation(std::vector<Token> const &token, std::map<std::string, Value*> const &val)
{
	std::stack<Value*>	_st_n;
	std::stack<Token>	_st_o;

	std::cout << "\t1 : " << _st_o.size() << std::endl;
	for (int i = 0, len = token.size(); i < len; )
	{
		std::cout << i << " : " << token[i].getLexem() << std::endl;
		if (token[i].getType() == token_type::FUNCTION)
			std::cout << "1FUNCTION" << std::endl;


		if (token[i].getType() == token_type::DIGIT)
			_st_n.push(new Rational(stod(token[i++].getLexem())));
		else if (token[i].getType() == token_type::COMPLEX)
		{
			_st_n.push(new Complex(0, 1));
			i++;
		}
		else if (token[i].getType() == token_type::VARIABLE)
		{
			
		}
		// else if (token[i].getType() == token_type::FUNCTION)
		// {
		// 	throw std::runtime_error("FUNC!!!");
		// //	Value *ttt = val.find(token[i].getLexem())->second;
		// }
		else if (token[i].getLexem() == ")")
		{
			while(_st_o.top().getLexem() != "(")
				_math(_st_n, _st_o);
			_st_o.pop();
			i++;
		}
		else
		{
			if (token[i].getType() == token_type::FUNCTION)
				std::cout << "111FUNCTION" << std::endl;


			if (_st_o.empty() || token[i].getLexem() == "(")
				_st_o.push(token[i++]);
			else if (token[i].getRang() > _st_o.top().getRang())
			{
				if (token[i].getType() == token_type::FUNCTION)
					std::cout << "222FUNCTION" << std::endl;
				
				_st_o.push(token[i++]);
				
				if (token[i - 1].getType() == token_type::FUNCTION)
					std::cout << "333FUNCTION" << std::endl;
			}
			else
				_math(_st_n, _st_o);
		}
	}
	std::cout << "while" << std::endl;
	while (_st_o.size() != 0)
		_math(_st_n, _st_o);
	result =  _st_n.top();
}

Computation::~Computation()
{}

void Computation::_math(std::stack<Value*> &_st_n, std::stack<Token> &_st_o)
{
	Value *a = _st_n.top();
	_st_n.pop();
	Value *b = NULL;

std::cout << "_math : " << _st_o.top().getLexem() << std::endl;
	

	if (_st_o.top().getType() != token_type::FUNCTION)
	{
		b = _st_n.top();
		_st_n.pop();
	}

		if (_st_o.top().getType() == token_type::FUNCTION)
			std::cout << "3FUNCTION" << std::endl;
// std::cout <<"111" << std::endl;

	// if (_st_o.top().getLexem() == "+")
	// 	op = &Value::operator+;
	// if (_st_o.top().getLexem() == "-")
	// 	op = &Value::operator-;
	// if (_st_o.top().getLexem() == "*")
	// 	op = &Value::operator*;
	// if (_st_o.top().getLexem() == "/")
	// 	op = &Value::operator/;

	// op = f1();
	std::cout << "222" << std::endl;
	try 
	{
		if (_st_o.top().getType() == token_type::FUNCTION)
		{
			std::cout << "FUNC!!!" << std::endl;
			_st_n.push(new Rational(42));
		}
		else
			_st_n.push((b->*_op(_st_o.top().getLexem()))(a));
	}
	catch(const std::exception& e)
	{
		delete a;
		delete b;
		while (_st_n.size())
		{
			delete _st_n.top();
			_st_n.pop();
		}
		std::cout << e.what() << std::endl;
		throw std::runtime_error("COMPUTATION ERROR!!!");
	}	
// std::cout <<"333" << std::endl;
	// if (_st_o.top().getLexem() == "+")
	// 		// _st_n.push(*a + b);
	// 		//_st_n.push(a->operator+(b));
	// else if (_st_o.top().getLexem() == "-")
	// 		_st_n.push(*b - a);
	// else if (_st_o.top().getLexem() == "*")
	// 		_st_n.push(*a * b);
	// else if (_st_o.top().getLexem() == "/")
	// 		_st_n.push(*b / a);
	// else if (_st_o.top().getLexem() == "&")
	// 		_st_n.push(*b % a);
	_st_o.pop();
	delete a;
	delete b;
}

Value* (Value::*Computation::_op(std::string const &op_str))(const Value *rhs) const
{
	if (op_str == "+")
		return &Value::operator+;
	else if (op_str == "-")
		return &Value::operator-;
	else if (op_str == "*")
		return &Value::operator*;
	else if (op_str == "/")
		return &Value::operator/;
	else if (op_str == "%")
		return &Value::operator%;
	else if (op_str == "^")
		return &Value::operator^;
	else if (op_str == "**")
		return &Value::matrix_miltiple;
	else
		throw std::runtime_error("FUNC???");
}
