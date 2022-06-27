#pragma once

# include <string>
# include <vector>
# include <map>
# include <iostream>
# include <algorithm>
# include <signal.h>

# include "Token.hpp"
# include "Lexer.hpp"
# include "Parser.hpp"
// # include "Value.hpp"
// # include "Variable.hpp"
// # include "Function.hpp"

class Computor_v2
{
private:
//	std::vector<Token> _tokens;
//	std::vector<History>	history;
//	std::map<std::string, Value*> _value_map;

private:
	Computor_v2(Computor_v2 const &copy);
	Computor_v2 &operator=(Computor_v2 const &copy);

public:
	Computor_v2();
	~Computor_v2();

	void			analysis(std::string input);
};
