#pragma once

# include <string>
# include <vector>
# include <map>

# include "enum.hpp"
# include "Token.hpp"
# include "Value.hpp"

class Token;
class Value;

class Lexer
{
private:
	lexer_type			_type;
	std::string			_var_name;
	std::string			_func_unknown;
	std::vector<Token>	_expr;

private:
	std::vector<std::string>	_preparation_token(std::string const &input);
	std::vector<std::string>	_split_input(std::string const &input) const;
	std::string					_separate_digit_and_alpha(std::string const &input) const;
	bool						_is_separate_symbol(char const &symbol) const;
	bool						_is_str(std::string const &input) const;
	std::vector<std::string>	_right_to_left_polinom(std::vector<std::string> &left, \
														std::vector<std::string> const &right);

	void						_check_expr();
	void						_check_matrix();

	void						_print();

public:
	Lexer() = delete;
	Lexer(std::string const &input, std::map<std::string, Value*> const &val);
	~Lexer();
	Lexer(Lexer const &copy) = delete;
	Lexer &operator=(Lexer const &copy) = delete;

	lexer_type const			&getType() const		{ return _type; }
	std::string const			&getVarName() const		{ return _var_name; }
	std::string const			&getFuncUnknown() const	{ return _func_unknown; }
	std::vector<Token> const	&getTokens() const		{ return _expr; }

	void						print()					{ _print(); }
};
