#include "../include/Computation.hpp"

Computation::Computation(std::vector<Token> const &token, std::map<std::string, Value*> const &val)
{
	for (int i = 0, len = token.size(); i < len; )
	{
		if (token[i].getType() == token_type::DIGIT)
		{
			_st_n.push(new Rational(stod(token[i].getLexem())));
			i++;
		}
		else if (token[i].getType() == token_type::COMPLEX)
		{
			_st_n.push(new Complex(0, 1));
			i++;
		}
		else if (token[i].getType() == token_type::VARIABLE)
		{
			if (val.find(token[i].getLexem()) != val.end())
			{
				_st_n.push(val.find(token[i].getLexem())->second->clone());
				i++;
			}
			else
			{
				_clear_stack();
				throw std::runtime_error("UNKNOWN VARIABLE!!!");
			}
		}
		else if (token[i].getType() == token_type::FUNCTION)
		{
			const Function *ttt = static_cast<const Function*>(val.find(token[i].getLexem())->second);
			if (token[i + 1].getLexem() == "(" && \
				token[i + 2].getLexem() == ttt->getUnknown() && \
				val.find(token[i + 2].getLexem()) == val.end() &&
				token[i + 3].getLexem() == ")")
			{
				_st_n.push(val.find(token[i].getLexem())->second->clone());
				i += 3;
				i++;	
			}
			else
			{
				_st_o.push(token[i]);
				i++;
			}
		}
		else if (token[i].getLexem() == ")")
		{
			while(_st_o.top().getLexem() != "(")
				_math(val);
			_st_o.pop();
			i++;
		}
		else
		{
			if (_st_o.empty() || token[i].getLexem() == "(")
			{
				_st_o.push(token[i]);
				i++;
			}
			else if (token[i].getRang() > _st_o.top().getRang())
			{
				_st_o.push(token[i]);
				i++;
			}
			else
			{
				while (!_st_o.empty() && token[i].getRang() <= _st_o.top().getRang())
					_math(val);
				_st_o.push(token[i]);
				i++;
			}
		}
	}
	while (!_st_o.empty())
		_math(val);
}

Computation::~Computation()
{
	_clear_stack();
	std::cout << "ALL CLEAR Computation : " << _st_n.size() << std::endl;
}

void Computation::_clear_stack()
{
	while (!_st_n.empty())
	{
		delete _st_n.top();
		_st_n.pop();
	}
}

void Computation::_math(std::map<std::string, Value*> const &val)
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
		{
			std::cout << "FUNC!!!" << std::endl;
			const Function *ttt = static_cast<const Function*>(val.find(_st_o.top().getLexem())->second);
			std::map<std::string, Value*> new_val;
			new_val[ttt->getUnknown()] = a;
			Computation result(ttt->getFunc(), new_val);
			std::cout << "\t\t !!! : " ;
			Value *tmp = result.getValue();
			tmp->print();
			_st_n.push(tmp);
		}
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
	//	std::cout << e.what() << std::endl;
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
