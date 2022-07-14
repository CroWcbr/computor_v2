#pragma once

# include <vector>
# include <stack>
# include <string>
# include <map>

# include "Token.hpp"
# include "Value.hpp"

# include "Rational.hpp"
# include "Complex.hpp"

class Token;
class Value;

class Computation
{
private:
	std::stack<Value*>	_st_n;
	std::stack<Token>	_st_o;

	void		_math(std::map<std::string, Value*> const &val);
	Value*		(Value::*_op(std::string const &op_str))(const Value *rhs) const;
	void		_clear_stack();



public:
	Computation() = delete;
	Computation(Computation const &copy) = delete;
	Computation &operator=(Computation const &copy) = delete;

	Computation(std::vector<Token> const &tokens, \
				std::map<std::string, Value*> const &val);
	~Computation();

	Value*		getValue() const { return _st_n.top()->clone(); }
};
