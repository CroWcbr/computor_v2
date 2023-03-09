#pragma once

# include "main_library.hpp"
# include <map>
# include <vector>
# include <string>
# include "enum.hpp"
# include <iostream>
# include <sstream>
# include <fstream>

extern bool is_debug;

class Token;
class Value;

class Lexer
{
private:
	lexer_type								_type;
	std::string								_var_name;
	std::string								_func_unknown;
	std::vector<Token>						_expr;
	std::map<std::string, Value*> const		&_val;

private:
	std::vector<std::string>	_preparation_token(std::string const &input);
	std::vector<std::string>	_split(std::string const &str, \
										const char &delim);
	std::vector<std::string>	_split_input(std::string const &input) const;
	std::string					_separate_digit_and_alpha(std::string const &input) const;
	bool						_is_separate_symbol(char const &symbol) const;
	bool						_is_str(std::string const &input) const;
	bool 						_is_forbidden_name(std::string const &lexeme) const;
	std::vector<std::string>	_right_to_left_polinom(std::vector<std::string> &left, \
														std::vector<std::string> const &right);

	void						_tokenization(std::vector<std::string> const &input_to_vector);

	void						_check_matrix() const;
	void						_check_expr() const;
	void						_check_command() const;
	bool						_check_solve() const;

	void						_print() const;
	void						_print_check_token() const;

public:
	Lexer() = delete;
	Lexer(Lexer const &copy) = delete;
	Lexer &operator=(Lexer const &copy) = delete;

	Lexer(std::string const &input, \
			std::map<std::string, Value*> const &val);
	~Lexer();

	lexer_type const			&getType() const		{ return _type; }
	std::string const			&getVarName() const		{ return _var_name; }
	std::string const			&getFuncUnknown() const	{ return _func_unknown; }
	std::vector<Token> const	&getTokens() const		{ return _expr; }

	void						print() const			{ _print(); }
};
