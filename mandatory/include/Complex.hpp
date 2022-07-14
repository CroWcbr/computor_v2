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
	Complex() = delete;
	Complex(const Complex &other) = delete;
	Complex &operator=(const Complex &other) = delete;

	Complex(Lexer const &lex);
	Complex(double rat, double com);
	virtual ~Complex();

	double const			&getRational() const { return _rational; }
	double const			&getComplex() const { return _complex; }

	virtual void 			print() const;
	virtual std::string		to_string() const;
	virtual Value*			clone() const;

	virtual Value*			operator+(const Value *rhs) const;
	virtual Value*			operator-(const Value *rhs) const;
	virtual Value*			operator*(const Value *rhs) const;
	virtual Value*			operator/(const Value *rhs) const;
	virtual Value*			operator%(const Value *rhs) const;
	virtual Value*			operator^(const Value *rhs) const;
	virtual Value*			matrix_miltiple(const Value *rhs) const;
};
