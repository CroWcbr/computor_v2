#include "../include/Computation.hpp"
#include "../include/Matrix.hpp"

Computation::Computation(std::vector<Token> const &token, std::map<std::string, Value*> const &val): _val(val)
{
if (is_debug)
{
	std::cout << "Computation:" << std::endl;
	for (auto i : token)
		std::cout << i.getLexem() << " ";
	std::cout << std::endl;
}

	for (int i = 0, len = token.size(); i < len; i++)
	{
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
		else if (token[i].getLexem() == "[")
		{
			std::vector<Token>	matrix;
			int b = 1;
			matrix.push_back(token[i]);
			i++;
			while (b != 0 && i < len)
			{
				matrix.push_back(token[i]);
				if (token[i].getLexem() == "[")
					b++;
				if (token[i].getLexem() == "]")
					b--;
				i++;
			}
			i--;
			_st_n.push(new Matrix(matrix, val));
		}
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
		// if (is_debug)
		// {
		// 	std::cout << "!!!!!!!!!!!!!!" << std::endl;
		// 	_st_n.top()->print();
		// 	std::cout << std::endl;
		// 	_st_o.top().getLexem();
		// 	std::cout << "!!!!!!!!!!!!!!" << std::endl;
		// }
	}
	while (!_st_o.empty())
		_math();
}

Computation::~Computation()
{
	_clear_stack();
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
		if (_st_o.top().getLexem() == "norm")
			_st_n.push(_standart_funk(_st_o.top().getLexem())(a));
		else if (a->GetType() == value_type::RATIONAL)
			_st_n.push(_standart_funk(_st_o.top().getLexem())(a));
		else if (a->GetType() == value_type::MATRIX || \
				a->GetType() == value_type::COMPLEX)
			throw std::runtime_error("invalid type for standart Function");
		else
		{
			const Function	*tmp_fun = static_cast<const Function*>(a);
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
	Value *a = _st_n.top();
	_st_n.pop();
	Value *b = NULL;
	if (_st_o.top().getType() != token_type::FUNCTION)
	{
		b = _st_n.top();
		_st_n.pop();
	}
	try
	{
		if (_st_o.top().getType() == token_type::FUNCTION)
			_math_function(a);
		else
			_st_n.push((b->*_op(_st_o.top().getLexem()))(a));
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
