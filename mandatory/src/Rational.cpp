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

void Rational::print() const { std::cout << "\t" << _rational << std::endl; }

std::string Rational::to_string() const { return std::to_string(_rational); }

Value* Rational::clone() const
{
	return new Rational(_rational);
}

Value* Rational::operator+(const Value *rhs) const
{
	std::cout << "Rational *operator+" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		return (new Rational(_rational + tmp_rat->_rational));
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		return (*tmp_com + this);
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		return (*tmp_fun + this);
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Rational *operator+");
}

Value* Rational::operator-(const Value *rhs) const
{
	std::cout << "Rational *operator-" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		return (new Rational(_rational - tmp_rat->_rational));
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		return (new Complex(_rational - tmp_com->getRational(), 0 - tmp_com->getComplex()));
	}
	// else if (rhs->GetType() == value_type::FUNCTION)
	// {
	// 	const Function	*tmp_fun = static_cast<const Function*>(rhs);
	// 	return (*tmp_fun + this);
	// }
	else
		throw std::runtime_error("COMPUTATION ERROR! Rational *operator-");
}

Value* Rational::operator*(const Value *rhs) const
{
	std::cout << "Rational *operator*" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		return(new Rational(_rational * tmp_rat->_rational));
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		return (*tmp_com * this);
	}
	else if (rhs->GetType() == value_type::MATRIX)
	{
		const Matrix	*tmp_mat = static_cast<const Matrix*>(rhs);
		return (*tmp_mat * this);
	}	
	else
		throw std::runtime_error("COMPUTATION ERROR! Rational *operator*");
}

Value* Rational::operator/(const Value *rhs) const
{
	std::cout << "Rational *operator/" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		if (tmp_rat->_rational == 0)
			throw std::runtime_error("COMPUTATION ERROR! Rational *operator/ : zero division");
		return(new Rational(_rational / tmp_rat->_rational));
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		double denominator = tmp_com->getRational() * tmp_com->getRational() + \
							 tmp_com->getComplex() *  tmp_com->getComplex();
		double real = (_rational * tmp_com->getRational()) / denominator;
		double image = (-_rational * tmp_com->getComplex()) / denominator;
		if (image == 0)
			return new Rational(real);
		return new Complex (real, image);
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Rational *operator/");
}

Value* Rational::operator%(const Value *rhs) const
{
	std::cout << "Rational *operator%" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		if (tmp_rat->_rational == 0)
			throw std::runtime_error("COMPUTATION ERROR! Rational *operator% : zero division");
		return(new Rational(_rational - static_cast<int>(_rational / tmp_rat->_rational) * tmp_rat->_rational));
	}
	throw std::runtime_error("ERROR!!! Rational operator%");
}

Value* Rational::operator^(const Value *rhs) const
{
	std::cout << "Rational *operator^" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		double tmp = 1;
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		if (tmp_rat->_rational < 0)
			throw std::runtime_error("COMPUTATION ERROR! Rational *operator^ : pow < 0");
		if (tmp_rat->_rational != static_cast<int>(tmp_rat->_rational))
			throw std::runtime_error("COMPUTATION ERROR! Rational *operator^ : pow is not int");
		for (int i = tmp_rat->_rational; i > 0; i--)
			tmp *= _rational;
		return(new Rational(tmp));
	}
	else
		throw std::runtime_error("ERROR!!! Rational operator^");
}

Value* Rational::matrix_miltiple(const Value *rhs) const
{
	throw std::runtime_error("ERROR!!! Rational matrix_miltiple");
}
