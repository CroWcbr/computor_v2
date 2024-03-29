#include "../include/Rational.hpp"

Rational::Rational(double const real):Value(value_type::RATIONAL, "_tmp") { _real = real; }

Rational::~Rational() {};

double const &Rational::getReal() const { return _real; }

void Rational::print() const { std::cout << "\t" << to_string() << std::endl; }

std::string Rational::to_string() const 
{
	std::string tmp;
	for (auto &tok : to_token())
		tmp.append(tok.getLexem() + " ");
	tmp.pop_back();
	return tmp;
}

Value* Rational::clone() const { return new Rational(_real); }

std::vector<Token> Rational::to_token() const
{
	std::vector<Token> tmp;

	double tmp_real = _real;
	if (tmp_real < 0)
	{	
		tmp.push_back(Token("-", token_type::OPERATION));
		tmp_real *= -1;
	}
	tmp.push_back(Token(std::to_string(tmp_real), token_type::DIGIT));
	return tmp;
}

bool Rational::getSimple() const { return true; }

Value* Rational::operator+(const Value *rhs) const
{
	if (is_debug)
		std::cout << "Rational *operator+" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		return (new Rational(_real + tmp_rat->getReal()));
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
	else if (rhs->GetType() == value_type::MATRIX)
	{
		const Matrix	*tmp_mat = static_cast<const Matrix*>(rhs);
		return (*tmp_mat + this);
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Rational *operator+");
}

Value* Rational::operator-(const Value *rhs) const
{
	if (is_debug)
		std::cout << "Rational *operator-" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		return (new Rational(_real - tmp_rat->getReal()));
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		return (new Complex(_real - tmp_com->getReal(), 0 - tmp_com->getImage()));
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
	else if (rhs->GetType() == value_type::MATRIX)
	{
		const Matrix	*tmp_mat = static_cast<const Matrix*>(rhs);
		Rational		*tmp_rat_minus = new Rational(-1);
		Value			*tmp_val_minus = NULL;
		Value			*tmp_val = NULL;
		tmp_val_minus = *tmp_mat * tmp_rat_minus;
		tmp_val = *tmp_val_minus + this;
		delete tmp_rat_minus;	
		delete tmp_val_minus;
		return (tmp_val);
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Rational *operator-");
}

Value* Rational::operator*(const Value *rhs) const
{
	if (is_debug)
		std::cout << "Rational *operator*" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		return(new Rational(_real * tmp_rat->getReal()));
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
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		return (*tmp_fun * this);
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Rational *operator*");
}

Value* Rational::operator/(const Value *rhs) const
{
	if (is_debug)
		std::cout << "Rational *operator/" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		if (tmp_rat->getReal() == 0)
			throw std::runtime_error("COMPUTATION ERROR! Rational *operator/ : zero division");
		return(new Rational(_real / tmp_rat->getReal()));
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		double denominator = tmp_com->getReal() * tmp_com->getReal() + \
							 tmp_com->getImage() *  tmp_com->getImage();
		double real = (_real * tmp_com->getReal()) / denominator;
		double image = (-_real * tmp_com->getImage()) / denominator;
		if (image == 0)
			return new Rational(real);
		return new Complex (real, image);
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		std::map<int, double> tmp_map;
		tmp_map[0] = _real;
		Function	*new_func = new Function(tmp_fun->getUnknown(), tmp_map);
		Value		*tmp_val = NULL;
		try
		{
			tmp_val = *new_func / tmp_fun;
			delete new_func;
		}
		catch(const std::exception& e)
		{
			delete new_func;	
			throw std::runtime_error(e.what());
		}
		return tmp_val;
	}
	else if (rhs->GetType() == value_type::MATRIX)
	{
		const Matrix	*tmp_mat = static_cast<const Matrix*>(rhs);
		Matrix			*tmp_new_mat = new Matrix(*tmp_mat);
		Rational		*tmp_rat_minus = new Rational(-1);
		Value	*tmp_val;
		try
		{
			tmp_val = *tmp_new_mat ^ tmp_rat_minus;
			delete tmp_new_mat;
			delete tmp_rat_minus;
		}
		catch(const std::exception& e)
		{
			delete tmp_new_mat;
			delete tmp_rat_minus;
			throw std::runtime_error(e.what());
		}
		Value	*result = *tmp_val * this;
		delete tmp_val;
		return (result);
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Rational *operator/");
}

Value* Rational::operator%(const Value *rhs) const
{
	if (is_debug)
		std::cout << "Rational *operator%" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		if (tmp_rat->getReal() == 0)
			throw std::runtime_error("COMPUTATION ERROR! Rational *operator% : zero division");
		return(new Rational(_real - static_cast<int>(_real / tmp_rat->getReal()) * tmp_rat->getReal()));
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		std::map<int, double> tmp_map;
		tmp_map[0] = _real;
		Function	*new_func = new Function(tmp_fun->getUnknown(), tmp_map);
		Value		*tmp_val = NULL;
		try
		{
			tmp_val = *new_func % tmp_fun;
			delete new_func;
		}
		catch(const std::exception& e)
		{
			delete new_func;	
			throw std::runtime_error(e.what());
		}
		return tmp_val;
	}
	else if (rhs->GetType() == value_type::MATRIX)
	{
		throw std::runtime_error("ERROR!!! Rational operator%% Matrix - don't realized");
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		throw std::runtime_error("ERROR!!! Rational operator%% Complex - don't realized");
	}
	else
		throw std::runtime_error("ERROR!!! Rational operator%");
}

Value* Rational::operator^(const Value *rhs) const
{
	if (is_debug)
		std::cout << "Rational *operator^" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		double tmp = 1;
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		if (tmp_rat->getReal() != static_cast<int>(tmp_rat->getReal()))
		{
			Value *tmp_ln = ft_ln(this);
			Value *tmp_xy = tmp_rat->operator*(tmp_ln);
			delete tmp_ln;
			Value *tmp_exp = ft_exp(tmp_xy);
			delete tmp_xy;
			return	tmp_exp;
		}
		else if (tmp_rat->getReal() < 0)
		{
			for (int i = tmp_rat->getReal(); i < 0; i++)
				tmp *= _real;
			return(new Rational(1/tmp));
		}
		else
		{
			for (int i = tmp_rat->getReal(); i > 0; i--)
				tmp *= _real;
			return(new Rational(tmp));
		}
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		std::map<int, double> tmp_map;
		tmp_map[0] = _real;
		Function	*new_func = new Function(tmp_fun->getUnknown(), tmp_map);
		Value		*tmp_val = NULL;
		try
		{
			tmp_val = *new_func ^ tmp_fun;
			delete new_func;
		}
		catch(const std::exception& e)
		{
			delete new_func;	
			throw std::runtime_error(e.what());
		}
		return tmp_val;
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		throw std::runtime_error("ERROR!!! Rational operator^ Complex - don't realized");
	}
	else if (rhs->GetType() == value_type::MATRIX)
	{
		throw std::runtime_error("ERROR!!! Rational operator^ Matrix - don't realized");
	}
	else
		throw std::runtime_error("ERROR!!! Rational operator^");
}

Value* Rational::matrix_miltiple(const Value *rhs) const
{
	(void)rhs;
	if (is_debug)
		std::cout << "Rational *matrix_miltiple" << std::endl;
	throw std::runtime_error("COMPUTATION ERROR! Rational *matrix_miltiple");
}
