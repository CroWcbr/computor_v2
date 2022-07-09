#include "../include/Computor_v2.hpp"

Computor_v2::Computor_v2()
{}

Computor_v2::~Computor_v2() 
{
	for (auto &symbol : _value_map)
	{
		delete symbol.second;
	}	
}

void Computor_v2::analysis(std::string input)
{
	try
	{
		Lexer lex(input, _value_map);
		lex.print();

		Value *tmp;

		if (lex.getType() == lexer_type::MATRIX)
			tmp = new Matrix(lex);
		else if (lex.getType() == lexer_type::RAT_COM_MAT)
		{
			Computation result(lex.getTokens(), _value_map);
			result.getValue()->setName(lex.getVarName());
			tmp = result.getValue();
		}
		else if (lex.getType() == lexer_type::FUNCTION)
			tmp = new Function(lex);
		else
			throw std::runtime_error("not done yet");

		_value_map[lex.getVarName()] = tmp;

		std::cout << _value_map.size() <<std::endl;
		
			for (auto &symbol : _value_map)
				{
					std::cout << symbol.first << " : " << symbol.second->GetName() << std::endl;
					std::cout << "\t";
					symbol.second->print();
				}

		// Value *tmp = result.


		// if (_value_map.size() == 2)
		// {
		// 	Value *a = new Rational(20);
		// 	Value *b = new Rational(10);

		// 	std::cout << "a : ";
		// 	a->print();
		// 	std::cout << "b : ";
		// 	b->print();
		// 	Value *tmp = (*a) + b;
		// 	std::cout << "1tmp : ";
		// 	tmp->print();

		// 	tmp = (*a) - b;
		// 	std::cout << "2tmp : ";
		// 	tmp->print();

		// 	tmp = (*a) * b;
		// 	std::cout << "3tmp : ";
		// 	tmp->print();

		// 	tmp = (*a) / b;
		// 	std::cout << "4tmp : ";
		// 	tmp->print();

		// 	tmp = (*a) + 5.0;
		// 	std::cout << "5tmp : ";
		// 	tmp->print();
		// }
//		Value val;
		// if (lex.getType() == lexer_type::FUNCTION || \
		// 		lex.getType() == lexer_type::VAR_COM_MAT ||
		// 		lex.getType() == lexer_type::MATRIX)
		// 	val.update(lex, _value_map);
		// else if (lex.getType() == lexer_type::SOLVE)
		// 	;
		// else if (lex.getType() == lexer_type::POLINOM)
		// 	;

		

		// if (lex.getType() == lexer_type::FUNCTION || \
		// 		lex.getType() == lexer_type::VAR_COM_MAT)
		// 	Value val(lex, _value_map);
		// if (lex.getType() == lexer_type::MATRIX)
		// 	tmp =  new Matrix(lex.getType(), lex.getTokens(), _value_map);
		// else if (lex.getType() == lexer_type::VARIABLE)
		// 	tmp = new Variable(lex.getType(), lex.getTokens(), _value_map);
		// else if (lex.getType() == lexer_type::VARIABLE)
		// 	tmp = new Function(lex.getType(), lex.getTokens(), _value_map);
		// else if (lex.getType() == lexer_type::COMPLEX)
		// 	tmp = new Complex(lex.getType(), lex.getTokens(), _value_map);

		// tmp->print();
		// _value_map[tmp->GetName()] = tmp;

		// 		for (auto &symbol : _value_map)
		// 		{
		// 			std::cout << symbol.first << " : " << std::endl;
		// 			std::cout << "\t";
		// 			symbol.second->print();
		// 		}
		


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
		std::cout << e.what() << std::endl;
	}
}
