#pragma once

# include <string>
# include <map>

# include "enum.hpp"
# include "Token.hpp"
# include "Lexer.hpp"
# include "Value.hpp"

# include "Rational.hpp"
# include "Complex.hpp"
# include "Matrix.hpp"
# include "Function.hpp"

class Value;

class Complex: public Value
{
private:
	double		_rational;
	double		_complex;

public:
	Complex();
	Complex(Lexer const &lex);
	Complex(double rat, double com);
	Complex(const Complex &other) = delete;
	Complex &operator=(const Complex &other) = delete;
	virtual ~Complex();

	virtual void 			print() const;
	virtual std::string		to_string() const;

	virtual Value*			operator+(const Value *rhs) const;
	virtual Value*			operator-(const Value *rhs) const;
	virtual Value*			operator*(const Value *rhs) const;
	virtual Value*			operator/(const Value *rhs) const;
	virtual Value*			operator%(const Value *rhs) const;
	virtual Value*			operator^(const Value *rhs) const;
	virtual Value*			matrix_miltiple(const Value *rhs) const;
};
