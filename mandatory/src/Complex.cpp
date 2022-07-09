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

void Complex::print() const { std::cout << _rational << " : " << _complex << std::endl; }

std::string Complex::to_string() const { return std::to_string(_rational) + " : " + std::to_string(_complex); }


Value* Complex::operator+(const Value *rhs) const
{
	std::cout << "Complex *operator+" << std::endl;
	if (rhs->GetType() == value_type::COMPLEX)
	{
		const Complex	*r_var = static_cast<const Complex*>(rhs);
		return(new Complex(_rational + r_var->_rational, _complex + r_var->_complex));
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Complex *operator+");
}

Value* Complex::operator-(const Value *rhs) const
{
	std::cout << "Complex *operator-" << std::endl;
	if (rhs->GetType() == value_type::COMPLEX)
	{
		const Complex	*r_var = static_cast<const Complex*>(rhs);
		return(new Complex(_rational - r_var->_rational, _complex - r_var->_complex));
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Complex *operator-");
}

Value* Complex::operator*(const Value *rhs) const
{
	std::cout << "Complex *operator*" << std::endl;
	// if (rhs->GetType() == value_type::COMPLEX)
	// {
	// 	const Complex	*r_var = static_cast<const Complex*>(rhs);
	// 	return(new Complex(_rational * r_var->_rational, _complex * r_var->_complex));
	// }
	// else
		throw std::runtime_error("COMPUTATION ERROR! Complex *operator*");
}

Value* Complex::operator/(const Value *rhs) const
{
	std::cout << "Complex *operator/" << std::endl;
	// if (rhs->GetType() == value_type::COMPLEX)
	// {
	// 	const Complex	*r_var = static_cast<const Complex*>(rhs);
	// 	return(new Complex(_rational * r_var->_rational, _complex * r_var->_complex));
	// }
	// else
		throw std::runtime_error("COMPUTATION ERROR! Complex *operator/");
}

Value* Complex::operator%(const Value *rhs) const
{
	throw std::runtime_error("ERROR!!! Complex operator%");
}

Value* Complex::operator^(const Value *rhs) const
{
	throw std::runtime_error("ERROR!!! Complex operator^");
}

Value* Complex::matrix_miltiple(const Value *rhs) const
{
	throw std::runtime_error("ERROR!!! Complex matrix_miltiple");
}
