#pragma once

# include "main_library.hpp"
# include "draw_curve.hpp"
# include <list>
# include <iostream>
# include <sstream>
# include <fstream>
# include "Computor_v1.hpp"
# include "Computation.hpp"

class Lexer;
class Value;

struct History
{ 
	std::string		_input;
	std::string		_result;
};

class Computor_v2
{
private:
	std::list<History>				_history;
	std::map<std::string, Value*>	_value_map;

	Value			*_new_MATRIX(Lexer const &lex);
	Value			*_new_RAT_COM_MAT(Lexer const &lex);
	Value			*_new_SOLVE(Lexer const &lex);
	Value			*_new_FUNCTION(Lexer const &lex);
	Value			*_new_POLINOM(Lexer const &lex);

	void			_add_value_map(Lexer const &lex, Value *tmp, std::string const &input);
	void			_add_history(std::string const &input, std::string const &result);

	void			_make_command(Lexer const &lex);
	void			_print_value_map() const;
	void			_print_history() const;
	void			_print_help() const;
	void			_change_mod();
	void			_make_test() const;
	void			_make_draw() const;
	void			_debug_mod();

public:
	Computor_v2();
	~Computor_v2();
	Computor_v2(Computor_v2 const &copy) = delete;
	Computor_v2 &operator=(Computor_v2 const &copy) = delete;

	void			clear_all();
	void			analysis(std::string const &input);
};
