#include "../include/Lexer.hpp"

Lexer::Lexer(std::string const &input, std::map<std::string, Value*> const &val)
{
	std::string prev = "";
	for (auto const &lexem : _preparation_token(input))
	{
		if ((lexem == "-" || lexem == "+") && \
				(prev == "" || prev == "("))
			_expr.push_back(Token("0"));
		_expr.push_back(Token(lexem));
		
		if (_expr.back().getType() == token_type::VARIABLE && \
				val.find(lexem) != val.end() && \
				val.find(lexem)->second->GetType() == value_type::FUNCTION)
		{
			_expr.back().setType(token_type::FUNCTION);
			_expr.back().updateRang();
		}
		
		if (_type == lexer_type::POLINOM && \
				_expr.back().getType() == token_type::VARIABLE && \
				val.find(lexem) == val.end())
		{
			if (_func_unknown == "")
				_func_unknown = lexem;
			if (_func_unknown != lexem)
				throw std::runtime_error("PARSE ERROR! POLINOM more then 0ne unknown");
		}

		prev = lexem;
	}
	if (_type == lexer_type::MATRIX)
		_check_matrix();
	else
		_check_expr();
	print();
}

Lexer::~Lexer() {}

//private
std::vector<std::string> Lexer::_preparation_token(std::string const &input)
{
	size_t						equal_pos = input.find("=");
	if (equal_pos == std::string::npos)
		throw std::runtime_error("PARSE ERROR! No EQUAL");

	std::vector<std::string>	left_tokens = _split_input(input.substr(0, equal_pos));
	std::vector<std::string>	right_tokens = _split_input(input.substr(++equal_pos));

	if (left_tokens.size() == 0)
		throw std::runtime_error("PARSE ERROR! No LEFT part");
	if (right_tokens.size() == 0)
		throw std::runtime_error("PARSE ERROR! No RIGHT part");

	if (right_tokens.back() == "?" && right_tokens.size() > 1)
	{
		_type = lexer_type::POLINOM;
		return _right_to_left_polinom(left_tokens, right_tokens);
	}
	else if (right_tokens.back() == "?" && right_tokens.size() == 1)
	{
		_type = lexer_type::SOLVE;
		return left_tokens;
	}
	else if (left_tokens.size() == 1 && \
			_is_str(left_tokens.front()))
	{
		if (left_tokens.front() == "i")
			throw std::runtime_error("PARSE ERROR! Forbidden unknown name 'i'");
		if (right_tokens.front() == "[")
			_type = lexer_type::MATRIX;
		else
			_type = lexer_type::RAT_COM_MAT;
		_var_name = left_tokens.front();
		return right_tokens;
	}
	else if (left_tokens.size() == 4 && \
			_is_str(left_tokens[0]) && \
			left_tokens[1] == "(" && \
			_is_str(left_tokens[2]) && \
			left_tokens[3] == ")")
	{
		if (left_tokens[0] == "i")
			throw std::runtime_error("PARSE ERROR! Forbidden function name 'i'");
		if (left_tokens[2] == "i")
			throw std::runtime_error("PARSE ERROR! Forbidden unknown name 'i'");
		if (left_tokens[0] == left_tokens[2])
			throw std::runtime_error("PARSE ERROR! Function name and unknown name are same");
		_type = lexer_type::FUNCTION;
		_var_name = left_tokens.front();
		_func_unknown = left_tokens[2];
		return right_tokens;
	}
	else
		throw std::runtime_error("PARSE ERROR! Unknown type of input");
}

std::vector<std::string> Lexer::_split_input(std::string const &input) const
{
	std::vector<std::string>	tmp_vector;
	std::string					tmp_lexem;
	std::string					tmp_str = _separate_digit_and_alpha(input);

	for (int i = 0, len = tmp_str.size(); i < len; i++)
	{
		if (_is_separate_symbol(tmp_str[i]))
		{
			if (!(tmp_lexem.empty()))
			{
				tmp_vector.push_back(tmp_lexem);
				tmp_lexem.clear();
			}
			if (!isspace(tmp_str[i]))
			{
				tmp_lexem += tmp_str[i];
				if (tmp_str[i] == '*' && i != len - 1 && tmp_str[i + 1] == '*')
					tmp_lexem += tmp_str[++i];
				tmp_vector.push_back(tmp_lexem);
				tmp_lexem.clear();
			}
			continue;
		}
		tmp_lexem += tmp_str[i];
	}
	if (!(tmp_lexem.empty()))
		tmp_vector.push_back(tmp_lexem);
	return tmp_vector;
}

std::string Lexer::_separate_digit_and_alpha(std::string const &input) const
{	// 2x -> 2 *x && x2 -> x * 2
	std::string tmp = input;
	for(int i = 0; i < tmp.size() - 1; i++)
		if ((isdigit(tmp[i]) && isalpha(tmp[i + 1])) || \
				(isdigit(tmp[i + 1]) && isalpha(tmp[i])))
			tmp.insert(i + 1, "*");
	return tmp;
}

bool Lexer::_is_separate_symbol(char const &symbol) const
{
	return	symbol == '+' || symbol == '-' || \
			symbol == '*' || symbol == '/' || symbol == '%' || \
			symbol == '^' || \
			symbol == '(' || symbol == ')' || \
			symbol == '[' || symbol == ']' || \
			symbol == ',' || symbol == ';' || \
			symbol == '?' || \
			isspace(symbol);
}

bool Lexer::_is_str(std::string const &input) const
{
	for (const auto &symbol : input)
		if (!isalpha(symbol))
			return false;
	return true;
}

std::vector<std::string> Lexer::_right_to_left_polinom(std::vector<std::string> &left, \
														std::vector<std::string> const &right)
{
	int bracet = 0;
	for (int i = 0, len = right.size(); i < len - 1; i++)
	{
		if (i == 0 && right[i] != "-")
		{
			left.push_back("-");
			if (right[i] == "+")
				continue;
		}
		else if ((right[i] == "+" || right[i] == "-") && \
				(right[i - 1] == "+" || right[i - 1] == "-"))
			throw std::runtime_error("PARSE ERROR! Double sign in RIGHT part");

		if (bracet == 0 && right[i] == "-")
			left.push_back("+");
		else if (bracet == 0 && right[i] == "+")
			left.push_back("-");
		else
		{
			left.push_back(right[i]);
			if (right[i] == "(")
				bracet++;
			else if (right[i] == ")")
				bracet--;
		}
	}
	return left;
}

void Lexer::_print() const
{
	std::vector<std::string>	type_print = \
		{"Solve", "Polinom", \
		"Function", "Matrix", \
		"Rational or Complex or Matrix"};
	std::cout << "\033[94m";
	std::cout << "LEXER: " << std::endl;
	std::cout << "\t Type  :\t" << type_print[(int)_type] <<std::endl;
	if (!_var_name.empty())
		std::cout << "\t Name  :\t" << _var_name <<std::endl;
	if (!_func_unknown.empty())
		std::cout << "\t Unknown :\t" << _func_unknown <<std::endl;	
	std::cout << "\t Token :\t";
	for (const auto &symbol : _expr)
		std::cout << symbol.getLexem() << " ";
	std::cout <<  std::endl;
	std::cout << "\033[0m";
}

void  Lexer::_check_matrix() const
{
	if (_expr.size() < 5)
		throw std::runtime_error("PARSE MATRIX ERROR! _expr.size() < 5");
	if (_expr[0].getLexem() != "[" || _expr[1].getLexem() != "[")
		throw std::runtime_error("PARSE MATRIX ERROR! begin SQUARE_BRACET_OPEN");
	if (_expr[_expr.size() - 1].getLexem() != "]" || _expr[_expr.size() - 2].getLexem() != "]")
		throw std::runtime_error("PARSE MATRIX ERROR! end SQUARE_BRACET_CLOSE");

	int	tmp_col = 0;
	int	check_col = 0;
	int	square = 0;
	for (int i = 1, len = _expr.size() - 1; i < len; i++)
	{
		std::string	lex_i = _expr[i].getLexem();
		std::string	lex_next = _expr[i + 1].getLexem();
		token_type	tok_i = _expr[i].getType();
		token_type	tok_next = _expr[i + 1].getType();
		if (lex_i == "[")
		{
			if (square == 1 || \
			!(lex_next == "+" || lex_next == "-" || _expr[i + 1].getType() == token_type::DIGIT))
				throw std::runtime_error("PARSE MATRIX ERROR! near '['");
			square++;
		}
		else if (lex_i == "]")
		{
			if (square == 0 || \
			!(lex_next == ";" || lex_next == "]"))
				throw std::runtime_error("PARSE MATRIX ERROR! wrong near '['");
			square--;
			if (check_col == 0)
				check_col = tmp_col;
			if (check_col != tmp_col)
				throw std::runtime_error("PARSE MATRIX ERROR! wrong column number");
			tmp_col = 0;
		}
		else if (lex_i == ";")
		{
			if (!(lex_next == "["))
				throw std::runtime_error("PARSE MATRIX ERROR! wrong near ';'");
		}
		else if (lex_i == ",")
		{
			if (!(lex_next == "+" || lex_next == "-" || tok_next == token_type::DIGIT))
				throw std::runtime_error("PARSE MATRIX ERROR! wrong near ','");
		}
		else if (lex_i == "+" || lex_i == "-")
		{
			if (!(tok_next == token_type::DIGIT))
				throw std::runtime_error("PARSE MATRIX ERROR! wrong near '+' or '-'");
		}
		else if (tok_i == token_type::DIGIT)
		{
			if (!(lex_next == "]" || lex_next == ","))
				throw std::runtime_error("PARSE MATRIX ERROR! wrong near DIGIT");
			tmp_col++;
		}
		else
			throw std::runtime_error("PARSE MATRIX ERROR! wrong token");
	}
	if (square != 0)
		throw std::runtime_error("PARSE MATRIX ERROR! wrong square");
}

void Lexer::_check_expr() const
{
	if (_expr[0].getType() == token_type::OPERATION)
		throw std::runtime_error("PARSE ERROR! incorrect syntax: Wrong first symbol");

	int	len = _expr.size() - 1;
	if (!(_expr[len].getType() == token_type::DIGIT || \
			_expr[len].getType() == token_type::COMPLEX || \
			_expr[len].getType() == token_type::VARIABLE || \
			_expr[len].getLexem() == ")"))
		throw std::runtime_error("PARSE ERROR! incorrect syntax: Wrong last symbol");

	int	bracet = 0;
	for (int i = 0; i <= len; i++)
	{
		std::string	lex_i = _expr[i].getLexem();
		token_type	tok_i = _expr[i].getType();

		if (lex_i == "(")
			bracet++;
		else if (lex_i == ")")
			bracet--;

		if (i == len)
			continue;

		std::string	lex_next = _expr[i + 1].getLexem();
		token_type	tok_next = _expr[i + 1].getType();

		if (tok_i == token_type::MATRIX_PARSE)
			throw std::runtime_error("PARSE ERROR! incorrect syntax: matrix simbol in expression");
		else if (tok_i == token_type::OPERATION && \
				tok_next == token_type::OPERATION)
			throw std::runtime_error("PARSE ERROR! incorrect syntax: double operation");
		else if (tok_i == token_type::OPERATION && \
				lex_next == ")")
			throw std::runtime_error("PARSE ERROR! incorrect syntax: operation + ')'");
		else if (tok_i == token_type::BRACET && \
				tok_next ==  token_type::BRACET && 
				lex_i != lex_next)
			throw std::runtime_error("PARSE ERROR! incorrect syntax:double wrong bracet");
		else if (lex_i == "(" && \
				tok_next ==  token_type::OPERATION)
			throw std::runtime_error("PARSE ERROR! incorrect syntax: '(' + operation");
		else if (lex_i == ")" && \
				tok_next !=  token_type::OPERATION)
			throw std::runtime_error("PARSE ERROR! incorrect syntax: ')' + var/dig/com/func");
		else if (tok_i == token_type::FUNCTION && \
				lex_next != "(")
			throw std::runtime_error("PARSE ERROR! incorrect syntax: functioan");
		else if ((tok_i == token_type::VARIABLE || \
				tok_i == token_type::DIGIT || \
				tok_i == token_type::COMPLEX) && \
				!(tok_next == token_type::OPERATION || \
				lex_next == ")"))
			throw std::runtime_error("PARSE ERROR! incorrect syntax: wrong symbol after variable or digit or complex");
	}
	if (bracet)
		throw std::runtime_error("PARSE ERROR! wrong number bracet");
}
