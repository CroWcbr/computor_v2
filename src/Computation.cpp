#include "../include/Computation.hpp"

Computation::Computation(std::vector<Token> const &token, std::map<std::string, Value*> const &val): _val(val)
{
	// std::cout << "Computation : " << std::endl;
	for (int i = 0, len = token.size(); i < len; i++)
	{
		// std::cout << "i : " << i << " : " << token[i].getLexem() << " : " << token[i].getRang() << " : " << (int)token[i].getType() << std::endl;
		// if(!_st_n.empty())
		// 	std::cout << _st_n.top()->to_string() << " : ";
		// if (!_st_o.empty())
		// 	std::cout << _st_o.top().getLexem() << " : ";
		// std::cout << std::endl;
		// std::cout << "#########" << std::endl;
		if ((token[i].getLexem() == "+" || token[i].getLexem() == "-") && \
				(i == 0 || token[i - 1].getLexem() == "("))
			_st_n.push(new Rational(0));
		if (token[i].getType() == token_type::DIGIT)
			_st_n.push(new Rational(stod(token[i].getLexem())));
		else if (token[i].getType() == token_type::COMPLEX)
			_st_n.push(new Complex(0, 1));
		else if (token[i].getType() == token_type::VARIABLE)
		{
			if (val.find(token[i].getLexem()) != val.end())
				_st_n.push(val.find(token[i].getLexem())->second->clone());
			else
				_st_n.push(new Function(token[i].getLexem()));
		}
		else if (token[i].getType() == token_type::FUNCTION)
			_st_o.push(token[i]);
		else if (token[i].getLexem() == ")")
		{
			while(_st_o.top().getLexem() != "(")
				_math();
			_st_o.pop();
		}
		else
		{
			if (_st_o.empty() || token[i].getLexem() == "(")
				_st_o.push(token[i]);
			else if (token[i].getRang() > _st_o.top().getRang())
				_st_o.push(token[i]);
			else
			{
				while (!_st_o.empty() && token[i].getRang() <= _st_o.top().getRang())
					_math();
				_st_o.push(token[i]);
			}
		}
	}
	// std::cout << "WHILE : " << _st_n.size() << " : " << _st_o.size() << std::endl;
	while (!_st_o.empty())
		_math();
}

Computation::~Computation()
{
	_clear_stack();
	// std::cout << "ALL CLEAR Computation : " << _st_n.size() << std::endl;
}

void Computation::_clear_stack()
{
	while (!_st_n.empty())
	{
		delete _st_n.top();
		_st_n.pop();
	}
}

void Computation::_math_function(Value *a)
{
	if (_val.find(_st_o.top().getLexem()) == _val.end())
	{
		// std::cout << a->GetName() << std::endl;
		if (_st_o.top().getLexem() == "norm")
			_st_n.push(_standart_funk(_st_o.top().getLexem())(a));
		else if (a->GetType() == value_type::RATIONAL)
			_st_n.push(_standart_funk(_st_o.top().getLexem())(a));
		else if (a->GetType() == value_type::MATRIX || \
				a->GetType() == value_type::COMPLEX)
			throw std::runtime_error("invalid type for standert Function");
		else
		{
			const Function	*tmp_fun = static_cast<const Function*>(a);
			// std::cout << a->GetName() << std::endl;
			Function *tmp_new = new Function(*tmp_fun);
			tmp_new->_simple = false;
			tmp_new->_map.clear();
			tmp_new->_func.insert(tmp_new->_func.begin(), Token("(", token_type::BRACET));
			tmp_new->_func.insert(tmp_new->_func.begin(), Token(_st_o.top().getLexem(), token_type::FUNCTION));
			tmp_new->_func.push_back(Token(")", token_type::BRACET));
			_st_n.push(tmp_new);
		}
	}
	else
	{
		const Function *tmp_func = static_cast<const Function*>(_val.find(_st_o.top().getLexem())->second);

		std::map<std::string, Value*> new_val;
		new_val[tmp_func->getUnknown()] = a;
		Computation result(tmp_func->getFunc(), new_val);
		Value *tmp = result.getValue()->clone();
		_st_n.push(tmp);
	}
}

void Computation::_math()
{
	// std::cout << " _math 0 " << std::endl;
	Value *a = _st_n.top();
	_st_n.pop();
	// std::cout << " _math 0.51 : " << a->to_string() << " : " << (int)a->GetType() << std::endl;
	Value *b = NULL;
	// std::cout << " _math 0.52 : " << _st_o.top().getLexem() << " : " << (int)_st_o.top().getType() << std::endl;
	// std::cout << " _math 0.53 : " << (int)token_type::FUNCTION << std::endl;	
	if (_st_o.top().getType() != token_type::FUNCTION)
	{
		// std::cout << " _math 0.6 : " << std::endl;	
		b = _st_n.top();
		_st_n.pop();
	}
	// std::cout << " _math 1 " << std::endl;
	try
	{
		if (_st_o.top().getType() == token_type::FUNCTION)
		{
			// std::cout << " _math 3 " << std::endl;
			_math_function(a);
		}
		else
		{
			// std::cout << " _math 4 : " << _st_o.top().getLexem() << std::endl;
			// a->print();
			// b->print();

			_st_n.push((b->*_op(_st_o.top().getLexem()))(a));
		}
	// std::cout << " _math  6 : " << _st_o.size() << std::endl;
		// std::cout << "_math : " << std::endl;
		// // _st_n.top()->print();
		// // for (auto &s : _st_n.top()->to_token())
		// // {
		// // 	std::cout << s.getLexem() << " : " << (int)s.getType() << " : " << s.getRang() << std::endl;
		// // }

		_st_o.pop();
		delete a;
		delete b;
	}
	catch(const std::exception& e)
	{
		delete a;
		delete b;
		_clear_stack();
		throw std::runtime_error(e.what());
	}
	// std::cout << " _math 22 : " << _st_n.size() << " : " << _st_o.size() << std::endl;
	// std::cout << " _math 22 : " << (int)_st_n.top()->GetType() << std::endl;
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
		throw std::runtime_error("NO ANY ELSE POSSIBLE in operation");
}

Value* (*Computation::_standart_funk(std::string const &f_str))(const Value *rhs)
{
	if (f_str == "sin")
		return &ft_sin;
	else if (f_str == "cos")
		return &ft_cos;
	if (f_str == "tan")
		return &ft_tan;
	else if (f_str == "ctg")
		return &ft_ctg;
	else if (f_str == "sqrt")
		return &ft_sqrt;
	else if (f_str == "ln")
		return &ft_ln;
	else if (f_str == "log")
		return &ft_log;
	else if (f_str == "abs")
		return &ft_abs;
	else if (f_str == "exp")
		return &ft_exp;
	else if (f_str == "norm")
		return &ft_norm;
	else
		throw std::runtime_error("NO ANY ELSE POSSIBLE in standart function");
}