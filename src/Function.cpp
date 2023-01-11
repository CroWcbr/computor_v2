#include "../include/Function.hpp"

Function::Function(std::string const &unknown):Value(value_type::FUNCTION, "_tmp")
{
	_unknown = unknown;
	_func.push_back(Token(_unknown, token_type::VARIABLE));
	_map[1] = 1;
	_simple = true;
}

Function::Function(Lexer const &lex, Value const *val):Value(value_type::FUNCTION, lex.getVarName())
{
	_unknown = lex.getFuncUnknown();
	if (val->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(val);
		_func = tmp_rat->to_token();
		_map[0] = tmp_rat->getReal();
		_simple = true;
	}
	else if (val->GetType() == value_type::COMPLEX)
	{
		const Complex	*tmp_com = static_cast<const Complex*>(val);
		_func = tmp_com->to_token();
		_map.clear();
		_simple = false;
	}
	else if (val->GetType() == value_type::MATRIX)
		throw std::runtime_error("COMPUTATION ERROR! Function make matrix");
}

Function::Function(std::string const &unknown, std::map<int, double> const &tok):Value(value_type::FUNCTION, "_tmp")
{
	_unknown = unknown;
	_simple = true;
	_map = tok;
	for (auto &m : _map)
	{
		if (m.second == 0)
			continue;
		double tmp = m.second;
		if (tmp < 0)
		{
			_func.push_back(Token("-", token_type::OPERATION));
			tmp *= -1;
		}
		else if (_func.size() > 0)
			_func.push_back(Token("+", token_type::OPERATION));
		_func.push_back(Token(std::to_string(tmp), token_type::DIGIT));
		if (m.first == 0)
			continue;
		_func.push_back(Token("*", token_type::OPERATION));
		_func.push_back(Token(_unknown, token_type::VARIABLE));
		if (m.first == 1)
			continue;
		_func.push_back(Token("^", token_type::OPERATION));
		if (m.first < 0)
		{
			_func.push_back(Token("(", token_type::OPERATION));
			_func.push_back(Token("-", token_type::OPERATION));
			_func.push_back(Token(std::to_string(-m.first), token_type::DIGIT));
			_func.push_back(Token(")", token_type::OPERATION));
		}
		else
			_func.push_back(Token(std::to_string(m.first), token_type::DIGIT));
	}
}

Function::Function(const Function &other):Value(other.GetType(), other.GetName()) { *this = other; }

Function &Function::operator=(const Function &other)
{
	if (this == &other)
		return *this;
	_unknown = other._unknown;
	_func = other._func;
	_map = other._map;
	_simple = other._simple;
	return *this;
}

Function::~Function() {}

std::string const &Function::getUnknown() const { return _unknown; }
std::vector<Token> const &Function::getFunc() const { return _func; }
std::map<int, double> const &Function::getMap() const { return _map; }
bool Function::getSimple() const { return _simple; }

void Function::print() const
{	
	std::cout << "\t" << to_string() << std::endl;
	std::cout << "\t_simple :" << _simple << std::endl;
	for (auto &m : _map)
		std::cout << "\t" << m.first << " : " << m.second << std::endl;
}

std::string Function::to_string() const 
{
	std::string	tmp;
	for (auto &tok : _func)
		tmp += tok.getLexem() + " ";
	return tmp;
}

Value* Function::clone() const { return new Function(*this); }

std::vector<Token> Function::to_token() const { return _func; }

Value* Function::operator+(const Value *rhs) const
{
	std::cout << "Function *operator+" << std::endl;
	if (getSimple() == true && \
		rhs->getSimple() == true && \
		(rhs->GetType() == value_type::RATIONAL || \
		(rhs->GetType() == value_type::FUNCTION && \
		getUnknown() == static_cast<const Function*>(rhs)->getUnknown())))
	{
		std::map<int, double> tmp_first = _map;
		std::map<int, double> tmp_second;
		if (rhs->GetType() == value_type::RATIONAL)
			tmp_second[0] = static_cast<const Rational*>(rhs)->getReal();
		else
			tmp_second = static_cast<const Function*>(rhs)->getMap();
		
		for (auto &m : tmp_second)
		{
			if (tmp_first.find(m.first) == tmp_first.end())
				tmp_first[m.first] = m.second;
			else
				tmp_first[m.first] += m.second;
		}

		if (tmp_first.size() == 1 && tmp_first.find(0) != tmp_first.end())
			return new Rational(tmp_first[0]);
		return new Function(_unknown, tmp_first);
	}
	else
	{
		if (rhs->GetType() == value_type::MATRIX)
			throw std::runtime_error("COMPUTATION ERROR! Function *operator+");
		Function *tmp_new = new Function(*this);
		tmp_new->_simple = false;
		tmp_new->_map.clear();
		std::vector<Token> tmp_token = rhs->to_token();
		if (tmp_token.front().getLexem() != "-")
			tmp_new->_func.push_back(Token("+", token_type::OPERATION));
		tmp_new->_func.insert(tmp_new->_func.end(), tmp_token.begin(), tmp_token.end());
		return tmp_new;
	}
}

Value* Function::operator-(const Value *rhs) const
{
	std::cout << "Function *operator-" << std::endl;
	if (getSimple() == true && \
		rhs->getSimple() == true && \
		(rhs->GetType() == value_type::RATIONAL || \
		(rhs->GetType() == value_type::FUNCTION && \
		getUnknown() == static_cast<const Function*>(rhs)->getUnknown())))
	{
		std::map<int, double> tmp_first = _map;
		std::map<int, double> tmp_second;
		if (rhs->GetType() == value_type::RATIONAL)
			tmp_second[0] = static_cast<const Rational*>(rhs)->getReal();
		else
			tmp_second = static_cast<const Function*>(rhs)->getMap();
		
		for (auto &m : tmp_second)
		{
			if (tmp_first.find(m.first) == tmp_first.end())
				tmp_first[m.first] = -m.second;
			else
				tmp_first[m.first] -= m.second;
		}

		if (tmp_first.size() == 1 && tmp_first.find(0) != tmp_first.end())
			return new Rational(tmp_first[0]);
		return new Function(_unknown, tmp_first);
	}
	else
	{
		if (rhs->GetType() == value_type::MATRIX)
			throw std::runtime_error("COMPUTATION ERROR! Function *operator-");
		Function *tmp_new = new Function(*this);
		tmp_new->_simple = false;
		tmp_new->_map.clear();
		std::vector<Token> tmp_token = rhs->to_token();
		tmp_new->_func.push_back(Token("-", token_type::OPERATION));
		tmp_new->_func.push_back(Token("(", token_type::BRACET));
		tmp_new->_func.insert(tmp_new->_func.end(), tmp_token.begin(), tmp_token.end());
		tmp_new->_func.push_back(Token(")", token_type::BRACET));
		return tmp_new;
	}
}

Value* Function::operator*(const Value *rhs) const
{
	std::cout << "Function *operator*" << std::endl;
	if (getSimple() == true && \
		rhs->getSimple() == true && \
		(rhs->GetType() == value_type::RATIONAL || \
		(rhs->GetType() == value_type::FUNCTION && \
		getUnknown() == static_cast<const Function*>(rhs)->getUnknown())))
	{
		std::map<int, double> tmp_first = _map;
		std::map<int, double> tmp_second;
		if (rhs->GetType() == value_type::RATIONAL)
			tmp_second[0] = static_cast<const Rational*>(rhs)->getReal();
		else
			tmp_second = static_cast<const Function*>(rhs)->getMap();
		
		std::map<int, double> tmp_answer;
		for (auto &m1 : tmp_first)
		{
			for (auto &m2 : tmp_second)
			{
				if (tmp_answer.find(m1.first + m2.first) == tmp_answer.end())
					tmp_answer[m1.first + m2.first] = m1.second * m2.second;
				else
					tmp_answer[m1.first + m2.first] += m1.second * m2.second;
			}
		}

		if (tmp_first.size() == 1 && tmp_first.find(0) != tmp_first.end())
			return new Rational(tmp_first[0]);
		return new Function(_unknown, tmp_answer);
	}
	else
	{
		if (rhs->GetType() == value_type::MATRIX)
			throw std::runtime_error("COMPUTATION ERROR! Function *operator*");
		Function *tmp_new = new Function(*this);
		tmp_new->_simple = false;
		tmp_new->_map.clear();
		std::vector<Token> tmp_token = rhs->to_token();
		tmp_new->_func.insert(tmp_new->_func.begin(), Token("(", token_type::BRACET));
		tmp_new->_func.push_back(Token(")", token_type::BRACET));
		tmp_new->_func.push_back(Token("*", token_type::OPERATION));
		tmp_new->_func.push_back(Token("(", token_type::BRACET));
		tmp_new->_func.insert(tmp_new->_func.end(), tmp_token.begin(), tmp_token.end());
		tmp_new->_func.push_back(Token(")", token_type::BRACET));
		return tmp_new;
	}
}

Value* Function::operator/(const Value *rhs) const
{
	std::cout << "Function *operator/" << std::endl;
	if (getSimple() == true && \
		rhs->getSimple() == true && \
			(rhs->GetType() == value_type::RATIONAL || \
				(rhs->GetType() == value_type::FUNCTION && \
					(getUnknown() == static_cast<const Function*>(rhs)->getUnknown() && \
						(static_cast<const Function*>(rhs)->_map.size() == 1) && 
							static_cast<const Function*>(rhs)->_map.find(0) != static_cast<const Function*>(rhs)->_map.end()))))
	{
		std::map<int, double> tmp_first = _map;
		std::map<int, double> tmp_second;
		if (rhs->GetType() == value_type::RATIONAL)
			tmp_second[0] = static_cast<const Rational*>(rhs)->getReal();
		else
			tmp_second = static_cast<const Function*>(rhs)->getMap();
		
		double delim = tmp_second[0];
		if (delim == 0)
			throw std::runtime_error("COMPUTATION ERROR! Function *operator/ : zero division");
		for (auto &m : tmp_first)
			tmp_first[m.first] = m.second / delim;

		if (tmp_first.size() == 1 && tmp_first.find(0) != tmp_first.end())
			return new Rational(tmp_first[0]);
		return new Function(_unknown, tmp_first);
	}
	else
	{
		if (rhs->GetType() == value_type::MATRIX)
			throw std::runtime_error("COMPUTATION ERROR! Function *operator/");
		Function *tmp_new = new Function(*this);
		tmp_new->_simple = false;
		tmp_new->_map.clear();
		std::vector<Token> tmp_token = rhs->to_token();
		tmp_new->_func.insert(tmp_new->_func.begin(), Token("(", token_type::BRACET));
		tmp_new->_func.push_back(Token(")", token_type::BRACET));
		tmp_new->_func.push_back(Token("/", token_type::OPERATION));
		tmp_new->_func.push_back(Token("(", token_type::BRACET));
		tmp_new->_func.insert(tmp_new->_func.end(), tmp_token.begin(), tmp_token.end());
		tmp_new->_func.push_back(Token(")", token_type::BRACET));
		return tmp_new;
	}
}

Value* Function::operator%(const Value *rhs) const
{
	std::cout << "Function *operator%" << std::endl;
	if (getSimple() == true && \
		rhs->getSimple() == true && \
			(rhs->GetType() == value_type::RATIONAL || \
				(rhs->GetType() == value_type::FUNCTION && \
					(getUnknown() == static_cast<const Function*>(rhs)->getUnknown() && \
						(static_cast<const Function*>(rhs)->_map.size() == 1) && 
							static_cast<const Function*>(rhs)->_map.find(0) != static_cast<const Function*>(rhs)->_map.end()))))
	{
		std::map<int, double> tmp_first = _map;
		std::map<int, double> tmp_second;
		if (rhs->GetType() == value_type::RATIONAL)
			tmp_second[0] = static_cast<const Rational*>(rhs)->getReal();
		else
			tmp_second = static_cast<const Function*>(rhs)->getMap();
		
		double delim = tmp_second[0];
		if (delim == 0)
			throw std::runtime_error("COMPUTATION ERROR! Function *operator% : zero division");
		for (auto &m : tmp_first)
			tmp_first[m.first] = m.second - static_cast<int>(m.second / delim) * delim;

		if (tmp_first.size() == 1 && tmp_first.find(0) != tmp_first.end())
			return new Rational(tmp_first[0]);
		return new Function(_unknown, tmp_first);
	}
	else
	{
		if (rhs->GetType() == value_type::MATRIX)
			throw std::runtime_error("COMPUTATION ERROR! Function *operator%");
		Function *tmp_new = new Function(*this);
		tmp_new->_simple = false;
		tmp_new->_map.clear();
		std::vector<Token> tmp_token = rhs->to_token();
		tmp_new->_func.insert(tmp_new->_func.begin(), Token("(", token_type::BRACET));
		tmp_new->_func.push_back(Token(")", token_type::BRACET));
		tmp_new->_func.push_back(Token("%", token_type::OPERATION));
		tmp_new->_func.push_back(Token("(", token_type::BRACET));
		tmp_new->_func.insert(tmp_new->_func.end(), tmp_token.begin(), tmp_token.end());
		tmp_new->_func.push_back(Token(")", token_type::BRACET));
		return tmp_new;
	}
}

Value* Function::operator^(const Value *rhs) const
{
	std::cout << "Function *operator^" << std::endl;
	if (getSimple() == true && \
		rhs->getSimple() == true && \
			(rhs->GetType() == value_type::RATIONAL || \
				(rhs->GetType() == value_type::FUNCTION && \
					(getUnknown() == static_cast<const Function*>(rhs)->getUnknown() && \
						(static_cast<const Function*>(rhs)->_map.size() == 1) && 
							static_cast<const Function*>(rhs)->_map.find(0) != static_cast<const Function*>(rhs)->_map.end()))))
	{
		std::map<int, double> tmp_first = _map;
		std::map<int, double> tmp_second;
		if (rhs->GetType() == value_type::RATIONAL)
			tmp_second[0] = static_cast<const Rational*>(rhs)->getReal();
		else
			tmp_second = static_cast<const Function*>(rhs)->getMap();
		
		double pow = tmp_second[0];
		if (pow < 0)
			throw std::runtime_error("COMPUTATION ERROR! Matrix *operator^ : pow < 0");
		if (pow != static_cast<int>(pow))
			throw std::runtime_error("COMPUTATION ERROR! Matrix *operator^ : pow is not int");

		if (pow == 0)
			return new Rational(1);
		
		Value *tmp = new Function(*this);
		for (int i = pow; i > 1; i--)
		{
			Value *tmp_save = tmp;
			tmp = *this * tmp_save;
			delete tmp_save;
		}

		return tmp;
	}
	else
	{
		if (rhs->GetType() == value_type::MATRIX)
			throw std::runtime_error("COMPUTATION ERROR! Function *operator^");
		Function *tmp_new = new Function(*this);
		tmp_new->_simple = false;
		tmp_new->_map.clear();
		std::vector<Token> tmp_token = rhs->to_token();
		tmp_new->_func.insert(tmp_new->_func.begin(), Token("(", token_type::BRACET));
		tmp_new->_func.push_back(Token(")", token_type::BRACET));
		tmp_new->_func.push_back(Token("^", token_type::OPERATION));
		tmp_new->_func.push_back(Token("(", token_type::BRACET));
		tmp_new->_func.insert(tmp_new->_func.end(), tmp_token.begin(), tmp_token.end());
		tmp_new->_func.push_back(Token(")", token_type::BRACET));
		return tmp_new;
	}
}

Value* Function::matrix_miltiple(const Value *rhs) const
{
	(void)rhs;
	std::cout << "Function *matrix_miltiple" << std::endl;
	throw std::runtime_error("COMPUTATION ERROR! Function *matrix_miltiple");
}
