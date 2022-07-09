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

class Function: public Value
{
private:
	std::vector<Token>	_func;

public:
	Function();
	Function(Lexer const &lex);
	Function(double rat);
	Function(const Function &other) = delete;
	Function &operator=(const Function &other) = delete;
	virtual ~Function();

	virtual void			print() const;
	virtual std::string		to_string() const;

	virtual Value*			operator+(const Value *rhs) const;
	virtual Value*			operator-(const Value *rhs) const;
	virtual Value*			operator*(const Value *rhs) const;
	virtual Value*			operator/(const Value *rhs) const;
	virtual Value*			operator%(const Value *rhs) const;
	virtual Value*			operator^(const Value *rhs) const;
	virtual Value*			matrix_miltiple(const Value *rhs) const;
};
