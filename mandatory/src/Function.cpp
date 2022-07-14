#include "../include/Function.hpp"

Function::Function(Lexer const &lex):Value(value_type::FUNCTION, lex.getVarName())
{
	_func = lex.getTokens();
	_unknown = lex.getFuncUnknown();
};

// Function::Function(Lexer const &lex, std::map<std::string, Value*> val):Value(value_type::FUNCTION, lex.getVarName())
// {
// 	_func = lex.getTokens();
// 	_unknown = lex.getFuncUnknown();
// };

Function::Function(double rat):Value(value_type::FUNCTION, "tmp")
{
	std::cout << "9999!!!!!!!!" << std::endl;
	//_rational = rat;
};

Function::Function(std::string const &x):Value(value_type::FUNCTION, "tmp")
{
	_unknown = x;
	_func.push_back(Token(x));
};

Function::Function(std::vector<Token> const &func, std::string const &unknown):Value(value_type::FUNCTION, "tmp")
{
	_unknown = unknown;
	_func = func;
};

Function::Function(Lexer const &lex, const Value *val):Value(value_type::FUNCTION, "tmp")
{
	_unknown = lex.getFuncUnknown();
	if (val->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(val);
		double			tmp = tmp_rat->getRational();
		if (tmp < 0)
		{
			_func.push_back(Token("0", token_type::DIGIT));
			_func.push_back(Token("-", token_type::OPERATION));
			tmp *= -1;
		}
		_func.push_back(Token(std::to_string(tmp), token_type::DIGIT));
	}
	else if (val->GetType() == value_type::COMPLEX)
	{
		const Complex	*tmp_com = static_cast<const Complex*>(val);
		double			real = tmp_com->getRational();
		double			image = tmp_com->getComplex();
		if (real != 0)
		{
			if (real < 0)
			{
				_func.push_back(Token("0", token_type::DIGIT));
				_func.push_back(Token("-", token_type::OPERATION));
				real *= -1;
			}
			_func.push_back(Token(std::to_string(real), token_type::DIGIT));
			if (image < 0)
			{
				_func.push_back(Token("-", token_type::OPERATION));
				image *= -1;
			}
			else 
				_func.push_back(Token("+", token_type::OPERATION));
		}
		else
		{
			if (image < 0)
			{
				_func.push_back(Token("0", token_type::DIGIT));
				_func.push_back(Token("-", token_type::OPERATION));
				image *= -1;
			}
		}
		_func.push_back(Token(std::to_string(image), token_type::DIGIT));
		_func.push_back(Token("*", token_type::OPERATION));
		_func.push_back(Token("i", token_type::COMPLEX));
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Function make matrix");
}

Function::~Function() {};

Function::Function(const Function &other):Value(value_type::FUNCTION, "tmp")
{
	*this = other;
}

Function &Function::operator=(const Function &other)
{
	if (this == &other)
		return *this;
	_unknown = other._unknown;
	_func = other._func;
	return *this;
}

void Function::print() const 
{
	std::cout << "\t";
	for (auto &tok : _func)
		std::cout << " " << tok.getLexem() << " ";
	std::cout << std::endl;
}

std::string Function::to_string() const 
{
	std::string tmp;
	for (auto &tok : _func)
		tmp+= tok.getLexem() + " ";
	return tmp;
}

Value* Function::clone() const
{
	Function *tmp = new Function(10);
	tmp->_unknown = _unknown;
	tmp->_func = _func;
	return tmp;
}

std::vector<Token> Function::_rational_to_token(double rat) const
{
	std::vector<Token>	tmp_tok;

	if (rat < 0)
	{
		tmp_tok.push_back(Token("0", token_type::DIGIT));
		tmp_tok.push_back(Token("-", token_type::OPERATION));
		rat *= -1;
	}
	tmp_tok.push_back(Token(std::to_string(rat), token_type::DIGIT));
	return tmp_tok;
}

std::vector<Token> Function::_complex_to_token(double real, double image) const
{
	std::vector<Token>	tmp_tok;

	if (real != 0)
	{
		if (real < 0)
		{
			tmp_tok.push_back(Token("0", token_type::DIGIT));
			tmp_tok.push_back(Token("-", token_type::OPERATION));
			real *= -1;
		}
		tmp_tok.push_back(Token(std::to_string(real), token_type::DIGIT));
	}
	if (image < 0)
	{
		if (real == 0)
			tmp_tok.push_back(Token("0", token_type::DIGIT));
		tmp_tok.push_back(Token("-", token_type::OPERATION));
		image *= -1;
	}
	else 
		tmp_tok.push_back(Token("+", token_type::OPERATION));
	tmp_tok.push_back(Token(std::to_string(image), token_type::DIGIT));
	tmp_tok.push_back(Token("*", token_type::OPERATION));
	tmp_tok.push_back(Token("i", token_type::COMPLEX));
	return tmp_tok;
}

Value* Function::operator+(const Value *rhs) const
{
	std::cout << "Function *operator+" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		Function *tmp_new = new Function(*this);
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		tmp_new->_func.push_back(Token("+", token_type::OPERATION));
		for (auto &tok :_rational_to_token(tmp_rat->getRational()))
			tmp_new->_func.push_back(tok);
		return tmp_new;
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		Function *tmp_new = new Function(*this);
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		tmp_new->_func.push_back(Token("+", token_type::OPERATION));
		for (auto &tok :_complex_to_token(tmp_com->getRational(), tmp_com->getComplex()))
			tmp_new->_func.push_back(tok);
		return tmp_new;
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		Function *tmp_new = new Function(*this);
		tmp_new->_func.push_back(Token("+", token_type::OPERATION));
		for (auto &tok : tmp_fun->getFunc())
			tmp_new->_func.push_back(tok);
		return tmp_new;
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Function *operator+");
}

Value* Function::operator-(const Value *rhs) const
{
	std::cout << "Function *operator-" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		Function *tmp_new = new Function(*this);
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		tmp_new->_func.push_back(Token("-", token_type::OPERATION));
		for (auto &tok :_rational_to_token(tmp_rat->getRational()))
		{
			if (tok.getLexem() == "-")
				tmp_new->_func.push_back(Token("+", token_type::OPERATION));
			else if (tok.getLexem() == "+")
				tmp_new->_func.push_back(Token("-", token_type::OPERATION));
			else
				tmp_new->_func.push_back(tok);
		}
		return tmp_new;
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		Function *tmp_new = new Function(*this);
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		tmp_new->_func.push_back(Token("-", token_type::OPERATION));
		for (auto &tok :_complex_to_token(tmp_com->getRational(), tmp_com->getComplex()))
		{
			if (tok.getLexem() == "-")
				tmp_new->_func.push_back(Token("+", token_type::OPERATION));
			else if (tok.getLexem() == "+")
				tmp_new->_func.push_back(Token("-", token_type::OPERATION));
			else
				tmp_new->_func.push_back(tok);
		}
		return tmp_new;
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		Function *tmp_new = new Function(*this);
		tmp_new->_func.push_back(Token("-", token_type::OPERATION));
		int bracet = 0;
		for (auto &tok : tmp_fun->getFunc())
		{
			if (tok.getLexem() == "(")
				bracet++;
			else if (tok.getLexem() == ")")
				bracet--;
			
			if (tok.getLexem() == "-" && bracet == 0)
				tmp_new->_func.push_back(Token("+", token_type::OPERATION));
			else if (tok.getLexem() == "+" && bracet == 0)
				tmp_new->_func.push_back(Token("-", token_type::OPERATION));
			else
				tmp_new->_func.push_back(tok);
		}
		return tmp_new;
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Function *operator-");
}

Value* Function::operator*(const Value *rhs) const
{
	std::cout << "Function *operator*" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		Function *tmp_new = new Function(*this);
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		tmp_new->_func.insert(tmp_new->_func.begin(),Token("(", token_type::OPERATION));
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		tmp_new->_func.push_back(Token("*", token_type::OPERATION));
		tmp_new->_func.push_back(Token("(", token_type::OPERATION));
		for (auto &tok :_rational_to_token(tmp_rat->getRational()))
			tmp_new->_func.push_back(tok);
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		return tmp_new;
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		Function *tmp_new = new Function(*this);
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		tmp_new->_func.insert(tmp_new->_func.begin(),Token("(", token_type::OPERATION));
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		tmp_new->_func.push_back(Token("*", token_type::OPERATION));
		tmp_new->_func.push_back(Token("(", token_type::OPERATION));
		for (auto &tok :_complex_to_token(tmp_com->getRational(), tmp_com->getComplex()))
			tmp_new->_func.push_back(tok);
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		return tmp_new;
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		Function *tmp_new = new Function(*this);
		tmp_new->_func.push_back(Token("-", token_type::OPERATION));
		tmp_new->_func.insert(tmp_new->_func.begin(),Token("(", token_type::OPERATION));
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		tmp_new->_func.push_back(Token("*", token_type::OPERATION));
		tmp_new->_func.push_back(Token("(", token_type::OPERATION));
		for (auto &tok : tmp_fun->getFunc())
			tmp_new->_func.push_back(tok);
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		return tmp_new;
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Function *operator*");
}

Value* Function::operator/(const Value *rhs) const
{
	std::cout << "Function *operator/" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		Function *tmp_new = new Function(*this);
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		tmp_new->_func.insert(tmp_new->_func.begin(),Token("(", token_type::OPERATION));
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		tmp_new->_func.push_back(Token("/", token_type::OPERATION));
		tmp_new->_func.push_back(Token("(", token_type::OPERATION));
		for (auto &tok :_rational_to_token(tmp_rat->getRational()))
			tmp_new->_func.push_back(tok);
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		return tmp_new;
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		Function *tmp_new = new Function(*this);
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		tmp_new->_func.insert(tmp_new->_func.begin(),Token("(", token_type::OPERATION));
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		tmp_new->_func.push_back(Token("/", token_type::OPERATION));
		tmp_new->_func.push_back(Token("(", token_type::OPERATION));
		for (auto &tok :_complex_to_token(tmp_com->getRational(), tmp_com->getComplex()))
			tmp_new->_func.push_back(tok);
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		return tmp_new;
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		Function *tmp_new = new Function(*this);
		tmp_new->_func.push_back(Token("-", token_type::OPERATION));
		tmp_new->_func.insert(tmp_new->_func.begin(),Token("(", token_type::OPERATION));
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		tmp_new->_func.push_back(Token("/", token_type::OPERATION));
		tmp_new->_func.push_back(Token("(", token_type::OPERATION));
		for (auto &tok : tmp_fun->getFunc())
			tmp_new->_func.push_back(tok);
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		return tmp_new;
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Function *operator/");
}

Value* Function::operator%(const Value *rhs) const
{
	std::cout << "Function *operator%" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		Function *tmp_new = new Function(*this);
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		tmp_new->_func.insert(tmp_new->_func.begin(),Token("(", token_type::OPERATION));
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		tmp_new->_func.push_back(Token("%", token_type::OPERATION));
		tmp_new->_func.push_back(Token("(", token_type::OPERATION));
		for (auto &tok :_rational_to_token(tmp_rat->getRational()))
			tmp_new->_func.push_back(tok);
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		return tmp_new;
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		Function *tmp_new = new Function(*this);
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		tmp_new->_func.insert(tmp_new->_func.begin(),Token("(", token_type::OPERATION));
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		tmp_new->_func.push_back(Token("%", token_type::OPERATION));
		tmp_new->_func.push_back(Token("(", token_type::OPERATION));
		for (auto &tok :_complex_to_token(tmp_com->getRational(), tmp_com->getComplex()))
			tmp_new->_func.push_back(tok);
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		return tmp_new;
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		Function *tmp_new = new Function(*this);
		tmp_new->_func.push_back(Token("-", token_type::OPERATION));
		tmp_new->_func.insert(tmp_new->_func.begin(),Token("(", token_type::OPERATION));
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		tmp_new->_func.push_back(Token("%", token_type::OPERATION));
		tmp_new->_func.push_back(Token("(", token_type::OPERATION));
		for (auto &tok : tmp_fun->getFunc())
			tmp_new->_func.push_back(tok);
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		return tmp_new;
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Function *operator%");
}

Value* Function::operator^(const Value *rhs) const
{
	std::cout << "Function *operator^" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		Function *tmp_new = new Function(*this);
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		tmp_new->_func.insert(tmp_new->_func.begin(),Token("(", token_type::OPERATION));
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		tmp_new->_func.push_back(Token("^", token_type::OPERATION));
		tmp_new->_func.push_back(Token("(", token_type::OPERATION));
		for (auto &tok :_rational_to_token(tmp_rat->getRational()))
			tmp_new->_func.push_back(tok);
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		return tmp_new;
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		Function *tmp_new = new Function(*this);
		const Complex	*tmp_com = static_cast<const Complex*>(rhs);
		tmp_new->_func.insert(tmp_new->_func.begin(),Token("(", token_type::OPERATION));
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		tmp_new->_func.push_back(Token("^", token_type::OPERATION));
		tmp_new->_func.push_back(Token("(", token_type::OPERATION));
		for (auto &tok :_complex_to_token(tmp_com->getRational(), tmp_com->getComplex()))
			tmp_new->_func.push_back(tok);
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		return tmp_new;
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		Function *tmp_new = new Function(*this);
		tmp_new->_func.push_back(Token("-", token_type::OPERATION));
		tmp_new->_func.insert(tmp_new->_func.begin(),Token("(", token_type::OPERATION));
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		tmp_new->_func.push_back(Token("^", token_type::OPERATION));
		tmp_new->_func.push_back(Token("(", token_type::OPERATION));
		for (auto &tok : tmp_fun->getFunc())
			tmp_new->_func.push_back(tok);
		tmp_new->_func.push_back(Token(")", token_type::OPERATION));
		return tmp_new;
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Function *operator^");
}

Value* Function::matrix_miltiple(const Value *rhs) const
{
	throw std::runtime_error("ERROR!!! Function matrix_miltiple");
}
