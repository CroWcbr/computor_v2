#pragma once

# include <string>
# include <vector>
# include <map>
# include <iostream>
# include <algorithm>
# include <signal.h>

# include "Token.hpp"
# include "Lexer.hpp"
# include "Value.hpp"
# include "Rational.hpp"
# include "Complex.hpp"
# include "Function.hpp"
# include "Matrix.hpp"
# include "Computation.hpp"
# include "Computor_v1.hpp"

class Computor_v2
{
private:
	std::map<std::string, Value*> _value_map;

	void			_print_value_map() const;

	Value			*_new_MATRIX(Lexer const &lex);
	Value			*_new_RAT_COM_MAT(Lexer const &lex);
	Value			*_new_FUNCTION(Lexer const &lex);
	Value			*_new_SOLVE(Lexer const &lex);
	Value			*_new_FUNCTION_POLINOM(Lexer const &lex);
	Value			*_new_POLINOM(Lexer const &lex);

	void			_add_value_map(Lexer const &lex, Value *tmp);
public:
	Computor_v2();
	~Computor_v2();
	Computor_v2(Computor_v2 const &copy) = delete;
	Computor_v2 &operator=(Computor_v2 const &copy) = delete;

	void			analysis(std::string input);
};
