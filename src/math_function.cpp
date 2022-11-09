#include "../include/math_function.hpp"

static double _ft_abs_rat(double const tmp) { return tmp < 0 ? -1 * tmp : tmp; }

static bool _ft_is_zero(double const tmp) { return _ft_abs_rat(tmp) < EPS ? true : false; }

static double _ft_sin_rat(double const x)
{
	double	answer = 0;
	double	an = x;

	for (int n = 2; _ft_abs_rat(an) > EPS; n++)
	{
		answer += an;
		an *= -x * x / (2.0 * n - 1.0) / (2.0 * n - 2.0);
	}
	if (_ft_is_zero(answer))
		answer = 0;
	return answer;
}

static double _ft_cos_rat(double const x)
{
	double	answer = 0;
	double	an = 1;

	for (int n = 1; _ft_abs_rat(an) > EPS; n++)
	{
		answer += an;
		an *= -x * x / (2.0 * n - 1.0) / (2.0 * n);
	}
	if (_ft_is_zero(answer))
		answer = 0;
	return answer;
}

Value *ft_sin(const Value *rhs)
{
	if (rhs->GetType() == value_type::RATIONAL)
	{
		double x = static_cast<const Rational*>(rhs)->getReal();	
		if (is_radian == false)
			x *= PI / 180;
		return new Rational(_ft_sin_rat(x));
	}
	else
		throw std::runtime_error("invalid type for SIN");
}

Value *ft_cos(const Value *rhs)
{
	if (rhs->GetType() == value_type::RATIONAL)
	{
		double x = static_cast<const Rational*>(rhs)->getReal();
		if (is_radian == false)
			x *= PI / 180;
		return new Rational(_ft_cos_rat(x));
	}
	else
		throw std::runtime_error("invalid type for COS");
}

Value *ft_tan(const Value *rhs)
{
	if (rhs->GetType() == value_type::RATIONAL)
	{
		double x = static_cast<const Rational*>(rhs)->getReal();
		if (is_radian == false)
			x *= PI / 180;
		
		double numerator = _ft_sin_rat(x);
		double denominator = _ft_cos_rat(x);
		if (denominator == 0)
			throw std::runtime_error("TAN is not define");
		return new Rational(numerator / denominator);
	}
	else
		throw std::runtime_error("invalid type for TAN");
}

Value *ft_ctg(const Value *rhs)
{
	if (rhs->GetType() == value_type::RATIONAL)
	{
		double x = static_cast<const Rational*>(rhs)->getReal();
		if (is_radian == false)
			x *= PI / 180;
		
		double numerator = _ft_cos_rat(x);
		double denominator = _ft_sin_rat(x);
		if (denominator == 0)
			throw std::runtime_error("CTG is not define");
		return new Rational(numerator / denominator);
	}
	else
		throw std::runtime_error("invalid type for CTG");
}

double _ft_sqrt_rat(double x)
{
	if (x == 0)
		return 0;
	else if (x < 0)
		throw std::runtime_error("ERROR :  SQRT < 0");
	double multi_answer = 1;
	while (x > 1)
	{
		multi_answer *= 10;
		x /= 100;
	}
	x = x - 1;
	double an = 1;
	double	answer = 1;
	for(int n = 1; _ft_abs_rat(an) > EPS; n++)
	{
		an *= (-1.0) * (2 * n - 1) * 2 * n * x / (n * n * 4);
		answer += an / (1.0 - 2 * n);
	}
	return answer * multi_answer;
}

Value *ft_sqrt(const Value *rhs)
{
	if (rhs->GetType() == value_type::RATIONAL)
	{
		double x = static_cast<const Rational*>(rhs)->getReal();
		return new Rational(_ft_sqrt_rat(x));
	}
	else
		throw std::runtime_error("invalid type for SQRT");
}

static double _ft_ln_rat(double x)
{
	int add_answer = 0;
	if (x > 2)
	{
		while( x > 2.0)
		{ 
			x /= 2.0;
			add_answer++;
		}
	}
	else if (x < 1)
	{
		while( x < 1.0)
		{ 
			x *= 2.0;
			add_answer--;
		}
	}
	x -= 1.0;
	double answer = 0;
	double an = x;
	for(int n = 2; _ft_abs_rat(an) > EPS; n++)
	{
		answer += an;
		an *= -x * (n - 1) / n;
	}
	return answer + add_answer * M_LN2;
}

Value *ft_ln(const Value *rhs)
{
	if (rhs->GetType() == value_type::RATIONAL)
	{
		double x = static_cast<const Rational*>(rhs)->getReal();
		if (x <= 0)
			throw std::runtime_error("ERROR : ln < 0");
		return new Rational(_ft_ln_rat(x));
	}
	else
		throw std::runtime_error("invalid type for LN");
}

Value *ft_log(const Value *rhs)
{
	if (rhs->GetType() == value_type::RATIONAL)
	{
		double x = static_cast<const Rational*>(rhs)->getReal();
		if (x <= 0)
			throw std::runtime_error("ERROR : log < 0");
		return new Rational(_ft_ln_rat(x)/_ft_ln_rat(10));
	}
	else
		throw std::runtime_error("invalid type for LOG");
}

Value *ft_abs(const Value *rhs)
{
	if (rhs->GetType() == value_type::RATIONAL)
		return new Rational(_ft_abs_rat(static_cast<const Rational*>(rhs)->getReal()));
	else
		throw std::runtime_error("invalid type for ABS");
}

Value *ft_exp(const Value *rhs)
{
	if (rhs->GetType() == value_type::RATIONAL)
	{
		double x = static_cast<const Rational*>(rhs)->getReal();
		double answer = 0;
		double an = 1;

		for(int n = 1; _ft_abs_rat(an) > EPS; n++)
		{
			answer += an;
			an *= x / n;
		}
		return new Rational(answer);
	}
	else
		throw std::runtime_error("invalid type for ABS");
}

Value *ft_norm(const Value *rhs)
{
	if (rhs->GetType() == value_type::RATIONAL)
	{
		double x = static_cast<const Rational*>(rhs)->getReal();
		return (new Rational(_ft_abs_rat(x)));
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		double real = tmp_com->getReal();
		double imag = tmp_com->getImage();
		return (new Rational(_ft_sqrt_rat(real * real + imag * imag)));
	}
	else if (rhs->GetType() == value_type::MATRIX)
	{
		const Matrix	*tmp_mat = static_cast<const Matrix*>(rhs);
		double sum = 0;
		for (auto const &m : tmp_mat->getMat())
			sum += m * m;
		return (new Rational(_ft_sqrt_rat(sum)));
	}
	else
		throw std::runtime_error("invalid type for ABS");
}
