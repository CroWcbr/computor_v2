#pragma once

# include "main_library.hpp"

class Value;
class Token;

class Complex: public Value
{
private:
	double		_real;
	double		_imag;

public:
	Complex() = delete;
	Complex(const Complex &other) = delete;
	Complex &operator=(const Complex &other) = delete;

	Complex(double const real, double const imag);
	virtual ~Complex();

	double const				&getReal() const;
	double const				&getImage() const;

	virtual void 				print() const;
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
