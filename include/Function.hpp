#pragma once

# include "main_library.hpp"

class Token;
class Value;


class Function: public Value
{
private:
	std::string				_unknown;

public:
	std::map<int, double>	_map;
	bool					_simple;
	std::vector<Token>		_func;

	Function() = delete;

	Function(std::string const &unknown);
	Function(Lexer const &lex, Value const *val);
	Function(std::string const &unknown, std::map<int, double> const &tok);
	virtual ~Function();
	Function(const Function &other);
	Function &operator=(const Function &other);

	std::string const			&getUnknown() const;
	std::vector<Token> const	&getFunc() const;
	std::map<int, double> const	&getMap() const;

	virtual void				print() const;
	virtual std::string			to_string() const;
	virtual Value*				clone() const;
	virtual std::vector<Token>	to_token() const;
	virtual bool				getSimple() const;

	virtual Value*				operator+(const Value *rhs) const;
	virtual Value*				operator-(const Value *rhs) const;
	virtual Value*				operator*(const Value *rhs) const;
	virtual Value*				operator/(const Value *rhs) const;
	virtual Value*				operator%(const Value *rhs) const;
	virtual Value*				operator^(const Value *rhs) const;
	virtual Value*				matrix_miltiple(const Value *rhs) const;
};
