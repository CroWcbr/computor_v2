#include "../include/Complex.hpp"

Complex::Complex(Lexer const &lex):Value(value_type::COMPLEX, lex.getVarName())
{
	_rational = 0;
	_complex = 1;
};

Complex::Complex(double rat, double com):Value(value_type::COMPLEX, "tmp")
{
	std::cout << "Complex construct" << std::endl;	
	_rational = rat;
	_complex = com;
};

Complex::~Complex() {};

void Complex::print() const { std::cout << "\t" << _rational << " : " << _complex << std::endl; }

std::string Complex::to_string() const { return std::to_string(_rational) + " : " + std::to_string(_complex); }

Value* Complex::clone() const
{
	return new Complex(_rational, _complex);
}

Value* Complex::operator+(const Value *rhs) const
{
	std::cout << "Complex *operator+" << std::endl;
	double real;
	double image;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		real = _rational + tmp_rat->getRational();
		image = _complex;
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		real = _rational + tmp_com->getRational();
		image = _complex + tmp_com->getComplex();
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Complex *operator+");
	if (image == 0)
		return new Rational(real);
	return new Complex (real, image);
}

Value* Complex::operator-(const Value *rhs) const
{
	std::cout << "Complex *operator-" << std::endl;
	double real;
	double image;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		real = _rational - tmp_rat->getRational();
		image = _complex;
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		real = _rational - tmp_com->getRational();
		image = _complex - tmp_com->getComplex();
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Complex *operator-");
	if (image == 0)
		return new Rational(real);
	return new Complex (real, image);
}

Value* Complex::operator*(const Value *rhs) const
{
	std::cout << "Complex *operator*" << std::endl;
	double real;
	double image;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		real = _rational * tmp_rat->getRational();
		image = _complex * tmp_rat->getRational();
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		real = _rational * tmp_com->getRational() - _complex * tmp_com->getComplex();
		image = _rational * tmp_com->getComplex() + _complex * tmp_com->getRational();
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Complex *operator*");
	if (image == 0)
		return new Rational(real);
	return new Complex (real, image);
}

Value* Complex::operator/(const Value *rhs) const
{
	std::cout << "Complex *operator/" << std::endl;
	double real;
	double image;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		if (tmp_rat->getRational() == 0)
			throw std::runtime_error("COMPUTATION ERROR! Complex *operator/ : zero division");
		real = _rational / tmp_rat->getRational();
		image = _complex / tmp_rat->getRational();
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		double denominator = tmp_com->getRational() * tmp_com->getRational() + \
							 tmp_com->getComplex() *  tmp_com->getComplex();
		real = (_rational * tmp_com->getRational() + _complex * tmp_com->getComplex()) / denominator;
		image = (_complex * tmp_com->getRational() - _rational * tmp_com->getComplex()) / denominator;
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Complex *operator/");
	if (image == 0)
		return new Rational(real);
	return new Complex (real, image);
}

Value* Complex::operator%(const Value *rhs) const
{
	throw std::runtime_error("ERROR!!! Complex operator%");
}

Value* Complex::operator^(const Value *rhs) const
{
	std::cout << "Rational *operator^" << std::endl;
	double real = _rational;
	double image = _complex;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		if (tmp_rat->getRational() < 0)
			throw std::runtime_error("COMPUTATION ERROR! Rational *operator^ : pow < 0");
		if (tmp_rat->getRational() != static_cast<int>(tmp_rat->getRational()))
			throw std::runtime_error("COMPUTATION ERROR! Rational *operator^ : pow is not int");
		for (int i = tmp_rat->getRational(); i > 0; i--)
		{
			double tmp_real = real;
			double tmp_image = image;
			real = tmp_real * _rational - tmp_image * _complex;
			image = tmp_image * _rational + tmp_real * _complex;
		}
	}
	else
		throw std::runtime_error("ERROR!!! Complex operator^");
	if (image == 0)
		return new Rational(real);
	return new Complex (real, image);
}

Value* Complex::matrix_miltiple(const Value *rhs) const
{
	throw std::runtime_error("ERROR!!! Complex matrix_miltiple");
}
