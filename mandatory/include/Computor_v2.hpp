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

class Computor_v2
{
private:
	std::map<std::string, Value*> _value_map;

public:
	Computor_v2();
	~Computor_v2();
	Computor_v2(Computor_v2 const &copy) = delete;
	Computor_v2 &operator=(Computor_v2 const &copy) = delete;

	void			analysis(std::string input);
};
