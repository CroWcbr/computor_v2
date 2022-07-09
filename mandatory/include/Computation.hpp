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
	Value*	result;
//	Value*	(Value::*op)(const Value *rhs) const;


	void		_math(std::stack<Value*> &_st_n, std::stack<Token> &_st_o);
	int			_getRang(std::string const &oper);


	Value* (Value::*_op(std::string const &op_str))(const Value *rhs) const;

	// void f0(char) {}
	// void (*f1())(char) { return f0; }
public:
	Computation() = delete;
	Computation(std::vector<Token> const &tokens, std::map<std::string, Value*> const &val);
	~Computation();
	Computation(Computation const &copy) = delete;
	Computation &operator=(Computation const &copy) = delete;

	Value*		getValue() { return result; }
};
