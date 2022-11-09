#include "../include/Computor_v2.hpp"

Computor_v2::Computor_v2() {}

Computor_v2::~Computor_v2() { clear_all(); }

void Computor_v2::clear_all()
{
	for (auto &symbol : _value_map)
		delete symbol.second;
}

void Computor_v2::analysis(std::string input)
{
	Value	*tmp = NULL;
	try
	{
		Lexer lex(input, _value_map);

		if (lex.getType() == lexer_type::COMMAND)
			_make_command(lex);
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
		_add_value_map(lex, tmp);

		if (lex.getType() == lexer_type::MATRIX || \
				lex.getType() == lexer_type::RAT_COM_MAT || \
				lex.getType() == lexer_type::FUNCTION)
			_add_history(input, tmp->to_string());
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		delete tmp;
	}
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
		std::cout << "RESULT : ";
		tmp->print();
	}
	else
	{
		if (lex.getType() == lexer_type::SOLVE)
		{
			std::cout << "SOLVE : ";
			tmp->print();
		}
		if (lex.getType() == lexer_type::POLINOM)
		{
			std::cout << "POLINOM : ";
			if (tmp->getSimple() == 0)
				throw std::runtime_error("Function is not simple : CANNOT be SOLVED");
			Computor_v1 pol(tmp);
			std::cout << pol.getMSG() << std::endl;
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
		std::cout << "  " << symbol.second->GetName() << std::endl;
		std::cout << "  " << symbol.first << " : " << value_type_print[(int)symbol.second->GetType()] << std::endl;
		symbol.second->print();
		// for (auto &s : symbol.second->to_token())
		// {
		// 	std::cout << s.getLexem() << " : " << (int)s.getType() << " : " << s.getRang() << std::endl;
		// }
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
	// std::cout << "Function curve display" << std::endl;
	std::cout << "#Added usual functions:" << std::endl;
	std::cout << "\t- exponential" << std::endl;
	std::cout << "\t- square root" << std::endl;
	std::cout << "\t- sine / cosine / tangent / cotangent" << std::endl;
	std::cout << "\t- ln / log" << std::endl;
	std::cout << "\t- absolute value" << std::endl;
	std::cout << "#Radian computation for angles" << std::endl;
	std::cout << "#Function Composition" << std::endl;
	std::cout << "#Norm computation" << std::endl;
	std::cout << "#Display of the list of stored variables and their values" << std::endl;
	std::cout << "#History of commands with results" << std::endl;
	// std::cout << "Matrix inversion" << std::endl;
	std::cout << "An extension of the matrix computation applied to the vector computation" << std::endl;
}

void Computor_v2::_change_mod()
{
	is_radian = is_radian == false ? true : false;
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
