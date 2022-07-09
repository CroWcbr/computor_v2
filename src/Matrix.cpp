#include "../include/Matrix.hpp"

Matrix::Matrix(Lexer const &lex):Value(value_type::MATRIX, lex.getVarName())
{
//	_rational = std::stod(lex.getTokens()[0].getLexem());
		int znak = 1;
		_col = 0;

		for (int i = 1, len = lex.getTokens().size() - 1; i < len; i++)
		{
			token_type type_i = lex.getTokens()[i].getType();
			std::string lexem_i = lex.getTokens()[i].getLexem();
			if (lexem_i == "[")
				_row++;
			else if (lexem_i == "]")
				;
			else if (lexem_i == ";")
				;
			else if (lexem_i == ",")
				;
			else if (lexem_i == "-")
				znak *= -1;
			else if (lexem_i == "+")
				;
			else if (type_i == token_type::DIGIT)
			{
				_mat.push_back(std::stod(lex.getTokens()[i].getLexem()) * znak);
				znak = 1;
				_col++;
			}
			else
				throw std::runtime_error("PARSE MATRIX ERROR! Unknown Token");
		}
		_col /= _row;
};

Matrix::Matrix(double rat):Value(value_type::RATIONAL, "tmp")
{
	//_rational = rat;
};

Matrix::~Matrix() {};

void Matrix::print() const 
{
	for (int r = 0; r < _row; r++)
	{
		std::cout << "[ ";
		for (int c = 0; c < _col; c++)
		{
			std::cout << _mat[c + r * _col] << " ";
			if (c != _col - 1)
				std::cout << ", ";	
		}
		std::cout << "]" << std::endl;
	}
}

std::string Matrix::to_string() const 
{
	return "MATRIX " + std::to_string(_row) + "x" + std::to_string(_col);
}

Value* Matrix::operator+(const Value *rhs) const
{
	std::cout << "Matrix *operator+" << std::endl;
	// if (rhs->GetType() == value_type::RATIONAL)
	// {
	// 	const Matrix	*r_var = static_cast<const Matrix*>(rhs);
	// 	return(new Matrix(_rational + r_var->_rational));
	// }
	// else if (rhs->GetType() == value_type::COMPLEX)
	// {
	// 	const Complex	*c_var = static_cast<const Complex*>(rhs);
	// 	return (*c_var + this);
	// }
	// else
		throw std::runtime_error("COMPUTATION ERROR! Matrix *operator+");
}

Value* Matrix::operator-(const Value *rhs) const
{
	std::cout << "Matrix *operator-" << std::endl;
	// if (rhs->GetType() == value_type::RATIONAL)
	// {
	// 	const Matrix	*r_var = static_cast<const Matrix*>(rhs);
	// 	return(new Matrix(_rational - r_var->_rational));
	// }
	// else
		throw std::runtime_error("COMPUTATION ERROR! Matrix *operator-");
}

Value* Matrix::operator*(const Value *rhs) const
{
	std::cout << "Matrix *operator*" << std::endl;
	// if (rhs->GetType() == value_type::RATIONAL)
	// {
	// 	const Matrix	*r_var = static_cast<const Matrix*>(rhs);
	// 	return(new Matrix(_rational * r_var->_rational));
	// }
	// else
		throw std::runtime_error("COMPUTATION ERROR! Matrix *operator*");
}

Value* Matrix::operator/(const Value *rhs) const
{
	// std::cout << "Matrix *operator/" << std::endl;
	// if (rhs->GetType() == value_type::RATIONAL)
	// {
	// 	const Matrix	*r_var = static_cast<const Matrix*>(rhs);
	// 	return(new Matrix(_rational / r_var->_rational));
	// }
	// else
		throw std::runtime_error("COMPUTATION ERROR! Matrix *operator/");
}

Value* Matrix::operator%(const Value *rhs) const
{
	throw std::runtime_error("ERROR!!! Matrix operator%");
}

Value* Matrix::operator^(const Value *rhs) const
{
	throw std::runtime_error("ERROR!!! Matrix operator^");
}

Value* Matrix::matrix_miltiple(const Value *rhs) const
{
	throw std::runtime_error("ERROR!!! Matrix matrix_miltiple");
}
