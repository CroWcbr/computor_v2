#pragma once

# include <iostream>
# include <sstream>
# include <algorithm>
# include <signal.h>
# include <fstream>

# include <string>
# include <vector>
# include <map>
# include <list>
# include <stack>

# include "Computor_v2.hpp"
# include "enum.hpp"
# include "Token.hpp"
# include "Lexer.hpp"
# include "Value.hpp"
# include "Rational.hpp"
# include "Complex.hpp"
# include "Function.hpp"
# include "Matrix.hpp"
# include "Computation.hpp"
# include "math_function.hpp"
# include "Computor_v1.hpp"

#include <SFML/Graphics.hpp>

void draw(std::vector<double> &x, std::vector<double> &y);

extern bool is_radian;
extern bool is_debug;
