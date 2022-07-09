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

class Rational: public Value
{
private:
	double		_rational;

public:
	Rational();
	Rational(Lexer const &lex);
	Rational(double rat);
	Rational(const Rational &other) = delete;
	Rational &operator=(const Rational &other) = delete;
	virtual ~Rational();

	virtual void			print() const;
	virtual std::string		to_string() const;

	virtual Value*			operator+(const Value *rhs) const;
	virtual Value*			operator-(const Value *rhs) const;
	virtual Value*			operator*(const Value *rhs) const;
	virtual Value*			operator/(const Value *rhs) const;
	virtual Value*			operator%(const Value *rhs) const;
	virtual Value*			operator^(const Value *rhs) const;
	virtual Value*			matrix_miltiple(const Value *rhs) const;
};
