#pragma once

# include "main_library.hpp"

class Value;

class Matrix: public Value
{
private:
	int						_row;
	int						_col;
	std::vector<double>		_mat;

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
