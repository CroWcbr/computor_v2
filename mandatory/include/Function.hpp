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
	std::string			_unknown;

	std::vector<Token>			_rational_to_token(double rat) const;
	std::vector<Token>			_complex_to_token(double real, \
													double image) const;
public:
	Function();
	Function(Lexer const &lex);
	Function(double rat);
	Function(std::string const &x);
	// Function(Lexer const &lex, std::map<std::string, Value*> val);
	Function(Lexer const &lex, const Value *val);
	Function(std::vector<Token> const &func, std::string const &unknown);
	Function(const Function &other);
	Function &operator=(const Function &other);
	virtual ~Function();

	virtual void				print() const;
	virtual std::string			to_string() const;
	virtual Value*				clone() const;

	std::string const			&getUnknown() const { return _unknown; }
	std::vector<Token> const	&getFunc() const { return _func; }

	virtual Value*				operator+(const Value *rhs) const;
	virtual Value*				operator-(const Value *rhs) const;
	virtual Value*				operator*(const Value *rhs) const;
	virtual Value*				operator/(const Value *rhs) const;
	virtual Value*				operator%(const Value *rhs) const;
	virtual Value*				operator^(const Value *rhs) const;
	virtual Value*				matrix_miltiple(const Value *rhs) const;
};
