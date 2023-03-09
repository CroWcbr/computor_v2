#pragma once

# include "main_library.hpp"
# include <string>
# include <vector>

class Value;

class Matrix: public Value
{
private:
	int						_row;
	int						_col;
	std::vector<double>		_mat;

private:
	Matrix						inverse() const;
	bool						is_square() const;
	double						determinant() const;
	Matrix						upper_triangular_matrix_change_znak_when_swap_row(Matrix tmp) const;
	double						ft_abs_double(const double &tmp) const;
	Matrix						cofactor_matrix_T(void) const;
	Matrix						&scl(const double &a);
	Matrix						transpose() const;

public:
	Matrix() = delete;

	Matrix(const Matrix &other);
	Matrix &operator=(const Matrix &other);
	Matrix(Lexer const &lex);
	Matrix(int const row, int const col);
	virtual ~Matrix() {};

	virtual void				print() const;
	virtual std::string			to_string() const;
	virtual Value*				clone() const;
	virtual std::vector<Token>	to_token() const;
	virtual bool				getSimple() const;

	int const					&getCol() const;
	int const					&getRow() const;
	std::vector<double> const	&getMat() const;

	virtual Value*				operator+(const Value *rhs) const;
	virtual Value*				operator-(const Value *rhs) const;
	virtual Value*				operator*(const Value *rhs) const;
	virtual Value*				operator/(const Value *rhs) const;
	virtual Value*				operator%(const Value *rhs) const;
	virtual Value*				operator^(const Value *rhs) const;
	virtual Value*				matrix_miltiple(const Value *rhs) const;


};
