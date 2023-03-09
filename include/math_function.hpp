#pragma once

# include "main_library.hpp"

extern bool is_radian;

#define PI		3.14159265358979323846
#define M_LN2	0.69314718055994530942
#define EPS		0.0000001

double			_ft_sqrt_rat(double x);

Value			*ft_sin(const Value *rhs);
Value			*ft_cos(const Value *rhs);
Value			*ft_tan(const Value *rhs);
Value			*ft_ctg(const Value *rhs);
Value			*ft_sqrt(const Value *rhs);
Value			*ft_ln(const Value *rhs);
Value			*ft_log(const Value *rhs);
Value			*ft_abs(const Value *rhs);
Value			*ft_exp(const Value *rhs);
Value			*ft_norm(const Value *rhs);
