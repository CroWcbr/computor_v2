#pragma once

# include <string>
# include <map>

# include "enum.hpp"
# include "Token.hpp"
# include "Lexer.hpp"

// # include "Rational.hpp"
// # include "Complex.hpp"
// # include "Matrix.hpp"
// # include "Function.hpp"

class Rational;
class Complex;
class Matrix;
class Function;

class Value
{
private:
	value_type			_type;
	std::string			_name;

public:
	Value() = delete;
	Value(value_type const &type, std::string const &name): 
		_type(type),
		_name(name)
	{}
	Value(const Value &other) = delete;
	Value &operator=(const Value &other) = delete;
	virtual ~Value() {};

	value_type const		&GetType() const { return _type; };
	std::string const		&GetName() const { return _name; };

	void					setName(std::string const &name) { _name = name; }

	virtual void			print() const = 0;
	virtual std::string		to_string() const = 0;

	virtual Value*			operator+(const Value *rhs) const = 0;
	virtual Value*			operator-(const Value *rhs) const = 0;
	virtual Value*			operator*(const Value *rhs) const = 0;
	virtual Value*			operator/(const Value *rhs) const = 0;
	virtual Value*			operator%(const Value *rhs) const = 0;
	virtual Value*			operator^(const Value *rhs) const = 0;
	virtual Value*			matrix_miltiple(const Value *rhs) const = 0;
};
