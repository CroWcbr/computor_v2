#include "../include/Function.hpp"

Function::Function(Lexer const &lex):Value(value_type::FUNCTION, lex.getVarName())
{
//	_rational = std::stod(lex.getTokens()[0].getLexem());
	_func = lex.getTokens();
};

Function::Function(double rat):Value(value_type::FUNCTION, "tmp")
{
	//_rational = rat;
};

Function::~Function() {};

void Function::print() const 
{
	for (auto &tok : _func)
		std::cout << tok.getLexem() << " ";
	std::cout << std::endl;
}

std::string Function::to_string() const 
{
	std::string tmp;
	for (auto &tok : _func)
		tmp+= tok.getLexem() + " ";
	return tmp;
}

Value* Function::operator+(const Value *rhs) const
{
	std::cout << "Function *operator+" << std::endl;
	// if (rhs->GetType() == value_type::RATIONAL)
	// {
	// 	const Function	*r_var = static_cast<const Function*>(rhs);
	// 	return(new Function(_rational + r_var->_rational));
	// }
	// else if (rhs->GetType() == value_type::COMPLEX)
	// {
	// 	const Complex	*c_var = static_cast<const Complex*>(rhs);
	// 	return (*c_var + this);
	// }
	// else
		throw std::runtime_error("COMPUTATION ERROR! Function *operator+");
}

Value* Function::operator-(const Value *rhs) const
{
	std::cout << "Function *operator-" << std::endl;
	// if (rhs->GetType() == value_type::RATIONAL)
	// {
	// 	const Function	*r_var = static_cast<const Function*>(rhs);
	// 	return(new Function(_rational - r_var->_rational));
	// }
	// else
		throw std::runtime_error("COMPUTATION ERROR! Function *operator-");
}

Value* Function::operator*(const Value *rhs) const
{
	std::cout << "Function *operator*" << std::endl;
	// if (rhs->GetType() == value_type::RATIONAL)
	// {
	// 	const Function	*r_var = static_cast<const Function*>(rhs);
	// 	return(new Function(_rational * r_var->_rational));
	// }
	// else
		throw std::runtime_error("COMPUTATION ERROR! Function *operator*");
}

Value* Function::operator/(const Value *rhs) const
{
	// std::cout << "Function *operator/" << std::endl;
	// if (rhs->GetType() == value_type::RATIONAL)
	// {
	// 	const Function	*r_var = static_cast<const Function*>(rhs);
	// 	return(new Function(_rational / r_var->_rational));
	// }
	// else
		throw std::runtime_error("COMPUTATION ERROR! Function *operator/");
}

Value* Function::operator%(const Value *rhs) const
{
	throw std::runtime_error("ERROR!!! Function operator%");
}

Value* Function::operator^(const Value *rhs) const
{
	throw std::runtime_error("ERROR!!! Function operator^");
}

Value* Function::matrix_miltiple(const Value *rhs) const
{
	throw std::runtime_error("ERROR!!! Function matrix_miltiple");
}
