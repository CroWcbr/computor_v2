#include "../include/Rational.hpp"

Rational::Rational(Lexer const &lex):Value(value_type::RATIONAL, lex.getVarName())
{
	_rational = std::stod(lex.getTokens()[0].getLexem());
};

Rational::Rational(double rat):Value(value_type::RATIONAL, "tmp")
{
	_rational = rat;
};

Rational::~Rational() {};

void Rational::print() const { std::cout << _rational << std::endl; }

std::string Rational::to_string() const { return std::to_string(_rational); }

Value* Rational::operator+(const Value *rhs) const
{
	std::cout << "Rational *operator+" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*r_var = static_cast<const Rational*>(rhs);
		return(new Rational(_rational + r_var->_rational));
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		const Complex	*c_var = static_cast<const Complex*>(rhs);
		return (*c_var + this);
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Rational *operator+");
}

Value* Rational::operator-(const Value *rhs) const
{
	std::cout << "Rational *operator-" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*r_var = static_cast<const Rational*>(rhs);
		return(new Rational(_rational - r_var->_rational));
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Rational *operator-");
}

Value* Rational::operator*(const Value *rhs) const
{
	std::cout << "Rational *operator*" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*r_var = static_cast<const Rational*>(rhs);
		return(new Rational(_rational * r_var->_rational));
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Rational *operator*");
}

Value* Rational::operator/(const Value *rhs) const
{
	std::cout << "Rational *operator/" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*r_var = static_cast<const Rational*>(rhs);
		return(new Rational(_rational / r_var->_rational));
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Rational *operator/");
}

Value* Rational::operator%(const Value *rhs) const
{
	throw std::runtime_error("ERROR!!! Rational operator%");
}

Value* Rational::operator^(const Value *rhs) const
{
	throw std::runtime_error("ERROR!!! Rational operator^");
}

Value* Rational::matrix_miltiple(const Value *rhs) const
{
	throw std::runtime_error("ERROR!!! Rational matrix_miltiple");
}
