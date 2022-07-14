#pragma once

# include <string>
# include <map>

# include "enum.hpp"
# include "Token.hpp"
# include "Lexer.hpp"
# include "Value.hpp"

# include "Rational.hpp"
# include "Complex.hpp"
# include "Matrix.hpp"
# include "Function.hpp"

class Value;

class Matrix: public Value
{
private:
	int						_col;
	int						_row;
	std::vector<double>		_mat;

public:
	Matrix() = delete;
	Matrix(const Matrix &other);
	Matrix &operator=(const Matrix &other);

	Matrix(Lexer const &lex);
	Matrix(double rat);
	virtual ~Matrix();

	virtual void				print() const;
	virtual std::string			to_string() const;
	virtual Value*				clone() const;

	int const					&getCol() const { return _col; }
	int const					&getRow() const { return _row; }
	std::vector<double> const	&getMat() const { return _mat; }	

	virtual Value*				operator+(const Value *rhs) const;
	virtual Value*				operator-(const Value *rhs) const;
	virtual Value*				operator*(const Value *rhs) const;
	virtual Value*				operator/(const Value *rhs) const;
	virtual Value*				operator%(const Value *rhs) const;
	virtual Value*				operator^(const Value *rhs) const;
	virtual Value*				matrix_miltiple(const Value *rhs) const;
};
