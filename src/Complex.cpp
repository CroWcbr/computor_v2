#include "../include/Complex.hpp"

Complex::Complex(double const real, double const imag):Value(value_type::COMPLEX, "_tmp")
{
	_real = real;
	_imag = imag;
};

Complex::~Complex() {};

double const &Complex::getReal() const { return _real; }
double const &Complex::getImage() const { return _imag; }

void Complex::print() const { std::cout << "\t" << to_string() << std::endl; }

std::string Complex::to_string() const 
{
	std::string	tmp;
	for (auto &tok : to_token())
		tmp.append(tok.getLexem() + " ");
	tmp.pop_back();
	return tmp; 
}

std::vector<Token> Complex::to_token() const
{
	std::vector<Token> tmp;

	double tmp_real = _real;
	double tmp_imag = _imag;
	if (tmp_real < 0)
	{
		tmp.push_back(Token("-", token_type::OPERATION));
		tmp_real *= -1;
	}

	if (tmp_real > 0)
		tmp.push_back(Token(std::to_string(tmp_real), token_type::DIGIT));
	
	if (tmp_imag < 0)
	{
		tmp.push_back(Token("-", token_type::OPERATION));
		tmp_imag *= -1;
	}
	else if (tmp_real != 0)
		tmp.push_back(Token("+", token_type::OPERATION));
	
	tmp.push_back(Token(std::to_string(tmp_imag), token_type::DIGIT));
	tmp.push_back(Token("*", token_type::OPERATION));
	tmp.push_back(Token("i", token_type::COMPLEX));
	return tmp;
}

bool Complex::getSimple() const { return false; }

Value* Complex::clone() const {	return new Complex(_real, _imag); }

Value* Complex::operator+(const Value *rhs) const
{
	if (is_debug)
		std::cout << "Complex *operator+" << std::endl;
	double real;
	double image;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		real = _real + tmp_rat->getReal();
		image = _imag;
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		real = _real + tmp_com->getReal();
		image = _imag + tmp_com->getImage();
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		return (*tmp_fun + this);
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Complex *operator+");
	if (image == 0)
		return new Rational(real);
	return new Complex (real, image);
}

Value* Complex::operator-(const Value *rhs) const
{
	if (is_debug)
		std::cout << "Complex *operator-" << std::endl;
	double real;
	double image;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		real = _real - tmp_rat->getReal();
		image = _imag;
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		real = _real - tmp_com->getReal();
		image = _imag - tmp_com->getImage();
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		Rational	*tmp_rat_minus = new Rational(-1);
		Value		*tmp_val_minus = NULL;
		Value		*tmp_val = NULL;
		try
		{
			tmp_val_minus = *tmp_fun * tmp_rat_minus;
			tmp_val = *tmp_val_minus + this;
			delete tmp_rat_minus;	
			delete tmp_val_minus;
		}
		catch(const std::exception& e)
		{
			delete tmp_rat_minus;	
			delete tmp_val_minus;
			throw std::runtime_error(e.what());
		}
		return tmp_val;
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Complex *operator-");
	if (image == 0)
		return new Rational(real);
	return new Complex (real, image);
}

Value* Complex::operator*(const Value *rhs) const
{
	if (is_debug)
		std::cout << "Complex *operator*" << std::endl;
	double real;
	double image;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		real = _real * tmp_rat->getReal();
		image = _imag * tmp_rat->getReal();
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		real = _real * tmp_com->getReal() - _imag * tmp_com->getImage();
		image = _real * tmp_com->getImage() + _imag * tmp_com->getReal();
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		return (*tmp_fun * this);
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Complex *operator*");
	if (image == 0)
		return new Rational(real);
	return new Complex (real, image);
}

Value* Complex::operator/(const Value *rhs) const
{
	if (is_debug)
		std::cout << "Complex *operator/" << std::endl;
	double real;
	double image;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		if (tmp_rat->getReal() == 0)
			throw std::runtime_error("COMPUTATION ERROR! Complex *operator/ : zero division");
		real = _real / tmp_rat->getReal();
		image = _imag / tmp_rat->getReal();
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		double denominator = tmp_com->getReal() * tmp_com->getReal() + \
							 tmp_com->getImage() *  tmp_com->getImage();
		real = (_real * tmp_com->getReal() + _imag * tmp_com->getImage()) / denominator;
		image = (_imag * tmp_com->getReal() - _real * tmp_com->getImage()) / denominator;
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		std::map<int, double> tmp_map;
		tmp_map[0] = 1;
		Function	*new_func = new Function(tmp_fun->getUnknown(), tmp_map);
		Value		*tmp_val = NULL;
		Value		*tmp = NULL;
		try
		{
			tmp_val = *new_func / tmp_fun;
			delete new_func;
			Value *tmp = tmp_val;
			tmp_val = *tmp_val * this;
			delete tmp;
		}
		catch(const std::exception& e)
		{
			delete new_func;
			delete tmp;
			throw std::runtime_error(e.what());
		}
		return tmp_val;
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Complex *operator/");
	if (image == 0)
		return new Rational(real);
	return new Complex (real, image);
}

Value* Complex::operator%(const Value *rhs) const
{
	(void)rhs;
	if (is_debug)
		std::cout << "Complex *operator%" << std::endl;
	throw std::runtime_error("COMPUTATION ERROR! Complex *operator%");
}

Value* Complex::operator^(const Value *rhs) const
{
	if (is_debug)
		std::cout << "Complex *operator^" << std::endl;
	double real = _real;
	double image = _imag;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		if (tmp_rat->getReal() < 0)
			throw std::runtime_error("COMPUTATION ERROR! Complex *operator^ : pow < 0");
		if (tmp_rat->getReal() != static_cast<int>(tmp_rat->getReal()))
			throw std::runtime_error("COMPUTATION ERROR! Complex *operator^ : pow is not int");
		for (int i = tmp_rat->getReal(); i > 0; i--)
		{
			double tmp_real = real;
			double tmp_image = image;
			real = tmp_real * _real - tmp_image * _imag;
			image = tmp_image * _real + tmp_real * _imag;
		}
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		std::map<int, double> tmp_map;
		tmp_map[0] = 1;
		Function	*new_func = new Function(tmp_fun->getUnknown(), tmp_map);
		Value		*tmp_val = NULL;
		Value		*tmp = NULL;
		try
		{
			tmp_val = *new_func * this;
			delete new_func;
			Value *tmp = tmp_val;
			tmp_val = *tmp_val ^ tmp_fun;
			delete tmp;
		}
		catch(const std::exception& e)
		{
			delete new_func;
			delete tmp;
			throw std::runtime_error(e.what());
		}
		return tmp_val;
	}
	else
		throw std::runtime_error("ERROR!!! Complex operator^");
	if (image == 0)
		return new Rational(real);
	return new Complex (real, image);
}

Value* Complex::matrix_miltiple(const Value *rhs) const
{
	(void)rhs;
	if (is_debug)
		std::cout << "Complex *matrix_miltiple" << std::endl;
	throw std::runtime_error("COMPUTATION ERROR! Complex *matrix_miltiple");
}
