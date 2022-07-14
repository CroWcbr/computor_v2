#include "../include/Computor_v2.hpp"

Computor_v2::Computor_v2()
{}

Computor_v2::~Computor_v2() 
{
	for (auto &symbol : _value_map)
		delete symbol.second;
}

Value *Computor_v2::_new_MATRIX(Lexer const &lex)
{
	return new Matrix(lex);
}

Value *Computor_v2::_new_POLINOM(Lexer const &lex)
{
	std::cout << "POLINOM!!!" << std::endl;
	Value *tmp = _new_FUNCTION_POLINOM(lex);
	const Function	*tmp_fun = static_cast<const Function*>(tmp);
	Computor_v1 polinom(tmp_fun->getFunc());
	tmp->print();
	return tmp;
}

Value *Computor_v2::_new_RAT_COM_MAT(Lexer const &lex)
{
	Value	*tmp;
	Computation result(lex.getTokens(), _value_map);
	tmp = result.getValue();
	tmp->setName(lex.getVarName());
	return tmp;
}

Value *Computor_v2::_new_FUNCTION_POLINOM(Lexer const &lex)
{
	std::vector<Token> tmp_expr = lex.getTokens();
	std::string	tmp_unknown = lex.getFuncUnknown();

	std::map<std::string, Value*> tmp_val = _value_map;
	
	Value	*tttt = new Function(tmp_unknown);
	tmp_val["_f"] = tttt;
	for (int i = 0; i < tmp_expr.size(); )
	{
		if (tmp_expr[i].getLexem() == tmp_unknown)
		{
			tmp_expr.insert(tmp_expr.begin() + i++, Token("_f", token_type::FUNCTION));
			tmp_expr.insert(tmp_expr.begin() + i++, Token("(", token_type::BRACET));
			tmp_expr.insert(tmp_expr.begin() + ++i, Token(")", token_type::BRACET));
		}
		i++;
	}

	for (int i = 0; i < tmp_expr.size(); i++)
		std::cout << tmp_expr[i].getLexem() << " ";
	std::cout << std::endl;

	Value	*tmppp;
	try
	{
		Computation result(tmp_expr, tmp_val);
		tmppp = result.getValue();
	}
	catch(const std::exception& e)
	{
		delete tttt;
		throw std::runtime_error(e.what());
	}
	
	tmppp->setName(lex.getVarName());
	tmppp->print();

	delete tttt;
	Value	*tmp = tmppp;

	if (tmp->GetType() != value_type::FUNCTION)
	{
		Value *tmp2 = tmp;
		tmp = new Function(lex, tmp);
		delete tmp2;
	}
	return tmp;
}

Value *Computor_v2::_new_FUNCTION(Lexer const &lex)
{
	Value *tmp = _new_FUNCTION_POLINOM(lex);

	const Function	*tmp_fun = static_cast<const Function*>(tmp);

	for (auto &tok : tmp_fun->getFunc())
		if (tok.getType() == token_type::VARIABLE && tok.getLexem() != lex.getFuncUnknown())
	{
		delete tmp;
		throw std::runtime_error("COMPUTATION ERROR! Wrong Function unknown");
	}

	return tmp;
}

Value *Computor_v2::_new_SOLVE(Lexer const &lex)
{
	Value	*tmp;
	Computation result(lex.getTokens(), _value_map);
	tmp = result.getValue();
	return tmp;
}

void Computor_v2::_add_value_map(Lexer const &lex, Value *tmp)
{
	if (lex.getType() == lexer_type::MATRIX || \
		lex.getType() == lexer_type::RAT_COM_MAT || \
		lex.getType() == lexer_type::FUNCTION)
	{
		if (_value_map.find(lex.getVarName()) != _value_map.end())
			delete _value_map[lex.getVarName()];
		_value_map[lex.getVarName()] = tmp;
		_print_value_map();
	}
	else
	{
		if (lex.getType() == lexer_type::SOLVE)
			tmp->print();
		delete tmp;
	}
}

void Computor_v2::analysis(std::string input)
{
	Value	*tmp = NULL;
	try
	{
		Lexer lex(input, _value_map);

		if (lex.getType() == lexer_type::MATRIX)
			tmp = _new_MATRIX(lex);
		else if (lex.getType() == lexer_type::POLINOM)
			tmp = _new_POLINOM(lex);
		else if (lex.getType() == lexer_type::RAT_COM_MAT)
			tmp = _new_RAT_COM_MAT(lex);
		else if (lex.getType() == lexer_type::FUNCTION)
			tmp = _new_FUNCTION(lex);
		else if (lex.getType() == lexer_type::SOLVE)
			tmp = _new_SOLVE(lex);
		else
			throw std::runtime_error("NO ANY ELSE POSSIBLE in lexer_type");

		_add_value_map(lex, tmp);
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		delete tmp;
	}
}

void Computor_v2::_print_value_map() const
{
	std::vector<std::string>	value_type_print = \
		{"RATIONAL",
		"COMPLEX",
		"MATRIX",
		"FUNCTION"};

	std::cout << "\033[92m";
	std::cout << "VALUE_MAP: " << _value_map.size() << std::endl;
	for (auto &symbol : _value_map)
	{
		std::cout << "  " << symbol.second->GetName() << std::endl;
		std::cout << "  " << symbol.first << " : " << value_type_print[(int)symbol.second->GetType()] << std::endl;
		symbol.second->print();
	}
	std::cout << "\033[0m";
}
