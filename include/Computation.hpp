#pragma once

# include "main_library.hpp"
# include <map>
# include <stack>

class Value;

class Computation
{
private:
	std::stack<Value*>						_st_n;
	std::stack<Token>						_st_o;
	std::map<std::string, Value*> const		&_val;

	void		_clear_stack();

	void		_math();
	void		_math_function(Value *a);
	Value*		(Value::*_op(std::string const &op_str))(const Value *rhs) const;

	Value*		(*_standart_funk(std::string const &f_str))(const Value *rhs);

public:
	Computation() = delete;
	Computation(Computation const &copy) = delete;
	Computation &operator=(Computation const &copy) = delete;

	Computation(std::vector<Token> const &tokens, \
				std::map<std::string, Value*> const &val);
	~Computation();

	Value*		getValue() const { return _st_n.top(); }
};
