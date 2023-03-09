#pragma once

# include "main_library.hpp"
# include <vector>
# include <string>
# include "enum.hpp"

class Value
{
private:
	value_type			_type;
	std::string			_name;

public:
	Value() {}
	Value(value_type const &type, std::string const &name): 
		_type(type),
		_name(name)
	{}
	Value(const Value &other) = delete;
	Value &operator=(const Value &other) = delete;
	virtual ~Value() {};

	value_type const			&GetType() const { return _type; };
	std::string const			&GetName() const { return _name; };

	void						setName(std::string const &name) { _name = name; }
	void						setType(value_type const &type) { _type = type; }

	virtual void				print() const		= 0;
	virtual std::string			to_string() const	= 0;
	virtual Value*				clone() const		= 0;
	virtual std::vector<Token>	to_token() const	= 0;
	virtual bool				getSimple() const	= 0;

	virtual Value*				operator+(const Value *rhs) const = 0;
	virtual Value*				operator-(const Value *rhs) const = 0;
	virtual Value*				operator*(const Value *rhs) const = 0;
	virtual Value*				operator/(const Value *rhs) const = 0;
	virtual Value*				operator%(const Value *rhs) const = 0;
	virtual Value*				operator^(const Value *rhs) const = 0;
	virtual Value*				matrix_miltiple(const Value *rhs) const = 0;
};
