#include "../include/Computor_v2.hpp"

Computor_v2::Computor_v2() {}

Computor_v2::~Computor_v2() { clear_all(); }

void Computor_v2::clear_all()
{
	for (auto &symbol : _value_map)
		delete symbol.second;
}

void Computor_v2::analysis(std::string const &input)
{
	Value	*tmp = NULL;
	try
	{
		Lexer lex(input, _value_map);

		if (lex.getType() == lexer_type::COMMAND)
		{
			_make_command(lex);
			
		}
		else if (lex.getType() == lexer_type::MATRIX)
			tmp = new Matrix(lex);
		else
		{
			Computation		result(lex.getTokens(), _value_map);
			tmp = result.getValue()->clone();
			tmp->setName(lex.getVarName());
			if (lex.getType() == lexer_type::FUNCTION &&
				tmp->GetType() != value_type::FUNCTION)
			{
				Value *tmp_del = tmp;
				tmp = new Function(lex, tmp);
				delete tmp_del;
			}
		}
		_add_value_map(lex, tmp, input);
	}
	catch(const std::exception& e)
	{
		_add_history(input, e.what());
		std::cout << e.what() << std::endl;
		delete tmp;
	}
}

void Computor_v2::_add_value_map(Lexer const &lex, Value *tmp, std::string const &input)
{
	if (lex.getType() == lexer_type::COMMAND)
		_add_history(input, "Command done");
	else if (lex.getType() == lexer_type::MATRIX || \
		lex.getType() == lexer_type::RAT_COM_MAT || \
		lex.getType() == lexer_type::FUNCTION)
	{
		if (_value_map.find(lex.getVarName()) != _value_map.end())
			delete _value_map[lex.getVarName()];
		_value_map[lex.getVarName()] = tmp;
		std::cout << "RESULT : ";
		tmp->print();
		_add_history(input, tmp->to_string());
	}
	else
	{
		if (lex.getType() == lexer_type::SOLVE)
		{
			std::cout << "SOLVE : ";
			tmp->print();
			_add_history(input, tmp->to_string());
		}
		if (lex.getType() == lexer_type::POLINOM)
		{
			std::cout << "POLINOM : ";
			if (tmp->getSimple() == 0)
				throw std::runtime_error("Polinom function is not simple : CANNOT be SOLVED");
			Computor_v1 pol(tmp);
			std::cout << pol.getMSG() << std::endl;
			_add_history(input, pol.getMSG());
			tmp->print();
		}
		delete tmp;
	}
}

void Computor_v2::_add_history(std::string const &input, std::string const &result)
{
	History tmp;
	tmp._input = input;
	tmp._result = result;
	_history.push_back(tmp);
}

void Computor_v2::_make_command(Lexer const &lex)
{
	if (lex.getVarName() == "show")
		_print_value_map();
	else if (lex.getVarName() == "change_mod")
		_change_mod();
	else if (lex.getVarName() == "history")
		_print_history();
	else if (lex.getVarName() == "help")
		_print_help();
	else if (lex.getVarName() == "test")
		_make_test();
	else if (lex.getVarName() == "draw")
		_make_draw();
	else if (lex.getVarName() == "debug")
		_debug_mod();
	else
		throw std::runtime_error("!!!! Unknown command");
}

void Computor_v2::_print_value_map() const
{
	std::vector<std::string>	value_type_print = \
		{"RATIONAL",
		"COMPLEX",
		"MATRIX",
		"FUNCTION"};

	std::cout << "\033[92m";
	std::cout << "VALUE_MAP : " << _value_map.size() << std::endl;
	for (auto &symbol : _value_map)
	{
		std::cout << "  " << symbol.first << " : " << value_type_print[(int)symbol.second->GetType()] << std::endl;
		symbol.second->print();
	}
	std::cout << "\033[0m";
}

void Computor_v2::_print_history() const
{
	std::cout << "HISTORY : " << _history.size() << std::endl;
	for (auto &h : _history)
	{
		std::cout << "\tINPUT : \t" << h._input << std::endl;
		std::cout << "\tRESULT : \t" << h._result << std::endl;
		std::cout << std::endl;
	}
}

void Computor_v2::_print_help() const
{
	std::cout << "Computor v2 with BONUS" << std::endl;
	std::cout << "This project is the first of a serie to renew your relationship to ";
	std::cout << "mathematics, it will be very useful, essential even, for many more projects." << std::endl;
	std::cout << "Command:" << std::endl;
	std::cout << "\tshow\t\t - display variables" << std::endl;
	std::cout << "\thistory\t\t - display log" << std::endl;
	std::cout << "\thelp\t\t - show this" << std::endl;
	std::cout << "\tchange_mod\t - radians on/off =)" << std::endl;
	std::cout << "\ttest\t\t - start test" << std::endl;
	std::cout << "\tdraw\t\t - draw and then function" << std::endl;
	std::cout << "\tdebug\t\t - debug mode" << std::endl;
	std::cout << "BONUS:" << std::endl;
	std::cout << "\t#Function curve display : draw -> function" << std::endl;
	std::cout << "\t#Added usual functions:" << std::endl;
	std::cout << "\t\t- exponential" << std::endl;
	std::cout << "\t\t- square root" << std::endl;
	std::cout << "\t\t- sine / cosine / tangent / cotangent" << std::endl;
	std::cout << "\t\t- ln / log" << std::endl;
	std::cout << "\t\t- absolute value" << std::endl;
	std::cout << "\t#Radian computation for angles" << std::endl;
	std::cout << "\t#Function Composition" << std::endl;
	std::cout << "\t#Norm computation" << std::endl;
	std::cout << "\t#Display of the list of stored variables and their values" << std::endl;
	std::cout << "\t#History of commands with results" << std::endl;
	std::cout << "\t#Matrix inversion (^(-1))" << std::endl;
	std::cout << "\t#An extension of the matrix computation applied to the vector computation" << std::endl;
}

void Computor_v2::_change_mod()
{
	is_radian = is_radian == false ? true : false;
	if (is_debug)
		std::cout << "is_radian mode ON" << std::endl;
	else
		std::cout << "is_degree mode ON" << std::endl;
}

void Computor_v2::_debug_mod()
{
	is_debug = is_debug == false ? true : false;
	if (is_debug)
		std::cout << "debug mode ON" << std::endl;
	else
		std::cout << "debug mode OFF" << std::endl;
}

void Computor_v2::_make_test() const
{
	std::cout << "input filename to test : ";
	std::string str;
	getline(std::cin, str);
	if (str.empty())
		throw std::runtime_error("No TEST name");

	std::ifstream test_read("./test/" + str);

	if (!test_read.is_open())
		throw std::runtime_error("Wrong TEST name");

	std::string buffer;
	Computor_v2 tmp_comp;
	while (true)
	{
		std::getline(test_read, buffer);
		std::cout << buffer << std::endl;
		std::cout << "\t";
		tmp_comp.analysis(buffer);
		std::getchar();
		if (test_read.eof())
			break ;
	}
	test_read.close();

	std::cout << str << std::endl;
}

void Computor_v2::_make_draw() const
{
	std::cout << "input func name to draw : ";
	std::string str;
	getline(std::cin, str);
	if (str.empty())
		throw std::runtime_error("DRAW ERROR! No FUNC name");
	if (_value_map.find(str) == _value_map.end())
		throw std::runtime_error("DRAW ERROR! No this FUNC");
	if (_value_map.find(str)->second->GetType() != value_type::FUNCTION)
		throw std::runtime_error("DRAW ERROR! it is not FUNC");

	std::vector<double> x;
	std::vector<double> y;

	std::vector<Token>	tmp_token;
	tmp_token.push_back(Token(str, token_type::FUNCTION));
	tmp_token.push_back(Token("(", token_type::BRACET));
	tmp_token.push_back(Token("0", token_type::DIGIT));
	tmp_token.push_back(Token(")", token_type::BRACET));

	try
	{
		for (int i = -500 ; i <= 500; i++)
		{
			tmp_token[2] = Token(std::to_string(i), token_type::DIGIT);
			Computation		result(tmp_token, _value_map);
			const Rational	*rmp_rat = static_cast<const Rational*>(result.getValue());
			x.push_back(i);
			y.push_back(rmp_rat->getReal());
		}	
	}
	catch(const std::exception& e)
	{
		std::cerr << "Function cannot be calculated : " << e.what() << '\n';
		return;
	}
	
	for(size_t i = 0; i < x.size(); i++)
		std::cout << x[i] << "\t" << y[i] << std::endl;
	draw(x, y);
}
