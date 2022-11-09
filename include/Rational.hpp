#pragma once

# include "main_library.hpp"

class Value;
class Token;

class Rational: public Value
{
private:
	double		_real;

public:
	Rational() = delete;
	Rational(const Rational &other) = delete;
	Rational &operator=(const Rational &other) = delete;

	Rational(double real);
	virtual ~Rational();

	double const				&getReal() const;

	virtual void				print() const;
	virtual std::string			to_string() const;
	virtual Value*				clone() const;
	virtual std::vector<Token>	to_token() const;
	virtual bool				getSimple() const;

	virtual Value*				operator+(const Value *rhs) const;
	virtual Value*				operator-(const Value *rhs) const;
	virtual Value*				operator*(const Value *rhs) const;
	virtual Value*				operator/(const Value *rhs) const;
	virtual Value*				operator%(const Value *rhs) const;
	virtual Value*				operator^(const Value *rhs) const;
	virtual Value*				matrix_miltiple(const Value *rhs) const;
};
