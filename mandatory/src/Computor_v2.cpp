#include "../include/Computor_v2.hpp"
//--leak-check=full
Computor_v2::Computor_v2() {}

Computor_v2::~Computor_v2() 
{
	// std::cout << "DELETE!!!!!!!" << std::endl;
	// for (auto symbol : _value_map)
	// {
	// 	std::cout << "DELETE!!!!!!! : " << symbol.second << std::endl;
	// 	delete symbol.second;
	// }
}

void Computor_v2::analysis(std::string input)
{
	Lexer lex;

	try
	{
		lex.parsing(input);
		lex.print();
		Parser pars(lex.getTokens());
		pars.print();
		// lex->print();
// 		if (lex->getType() == lexer_type::FUNCTION || \
// 			lex->getType() == lexer_type::MATRIX || \
// 			lex->getType() == lexer_type::VARIABLE)
// 		{
// 					std::cout << "333 : "<< &lex->getTokens() << std::endl;

// 		//	const std::vector<Token*>	*_tok = lex.getTokens();

// 		//	std::cout << "444 : "<< _tok << std::endl;

// const std::vector<Token*>	&_tok = lex->getTokens();

// std::cout << "444 : "<< &_tok << std::endl;

// 			if (lex->getType() == lexer_type::VARIABLE)
// 				test = new Variable(lex->getType(), _tok);
// 			else if (lex->getType() == lexer_type::MATRIX)
// 				;
// 			else
// 				test = new Function(lex->getType(), _tok);
// 		}

// 		_value_map[test->GetName()] = test;

// 		std::cout << "!!!! : " << test << std::endl;
// 		std::cout << "!!!! : " << _value_map.begin()->second << std::endl;
// 		for (auto symbol : _value_map)
// 			std::cout << symbol.first << " : " << symbol.second->GetVal() << std::endl;

// 		// std::cout << test->GetName() << std::endl;
// 		// 	Value *new_val = new Value(pars.getType(), lex.getTokens(), &_value_map);
// 		// 	new_val->printValue();

// 		// 	if (_value_map.find(new_val->getValue()) == _value_map.end())
// 		// 		_value_map[new_val->getValue()] = new_val;
// 		// 	else
// 		// 	{
// 		// 		free(_value_map[new_val->getValue()]);
// 		// 		_value_map[new_val->getValue()] = new_val;
// 		// 	}
// 		// }
// 		// else if (pars.getType() == lexer_type::SOLVE)
// 		// {
// 		//	std::string tmp= lex.getTokens()[0].getLexem();
// 			// if (_value_map.find(tmp) != _value_map.end())
// 			// 	_value_map[tmp].printValue();
// 			// else
// 			// {
// 			// 	std::cout << "NO var" << std::endl;
// 			// }
// 		// }
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
