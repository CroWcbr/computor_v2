#include "../include/Matrix.hpp"

Matrix::Matrix(Lexer const &lex):Value(value_type::MATRIX, lex.getVarName())
{
	_col = 0;
	_row = 0;
	for (int i = 1, len = lex.getTokens().size() - 1; i < len; i++)
	{
		std::string	lexem_i = lex.getTokens()[i].getLexem();
		if (lex.getTokens()[i].getLexem() == "[")
			_row++;
		else if (lex.getTokens()[i].getType() == token_type::DIGIT)
		{
			int znak = 1;
			if (lex.getTokens()[i - 1].getLexem() == "-")
				znak = -1;
			_mat.push_back(std::stod(lex.getTokens()[i].getLexem()) * znak);
			_col++;
		}
		else if (lexem_i == "]" || lexem_i == ";" || lexem_i == "," || \
				lexem_i == "-" || lexem_i == "+")
			;
		else
			throw std::runtime_error("PARSE MATRIX ERROR! Unknown Token");
	}
	_col /= _row;
};

Matrix::Matrix(double rat):Value(value_type::MATRIX, "tmp")
{
	_col = 0;
	_row = 0;
	_mat.clear();
};

Matrix::Matrix(const Matrix &other):Value(value_type::MATRIX, "tmp")
{
	*this = other;
}

Matrix &Matrix::operator=(const Matrix &other)
{
	if (this == &other)
		return *this;
	_row = other._row;
	_col = other._col;
	_mat = other._mat;
	return *this;
}

Value* Matrix::clone() const
{
	Matrix *tmp = new Matrix(10);
	tmp->_col = _col;
	tmp->_row = _row;
	tmp->_mat = _mat;
	return tmp;
}

Matrix::~Matrix() {};

void Matrix::print() const 
{
	for (int r = 0; r < _row; r++)
	{
		std::cout << "\t[ ";
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
	return "MATRIX " + std::to_string(_row) + " x " + std::to_string(_col);
}

Value* Matrix::operator+(const Value *rhs) const
{
	std::cout << "Matrix *operator+" << std::endl;
	if (rhs->GetType() == value_type::MATRIX)
	{
		const Matrix	*tmp_mat = static_cast<const Matrix*>(rhs);
		if (_row != tmp_mat->getRow() && _col != tmp_mat->getCol())
			throw(std::runtime_error("COMPUTATION ERROR! Matrix *operator+ : different size"));
		Matrix *tmp = new Matrix(*tmp_mat);
		for (int i = 0, len = _mat.size(); i < len; ++i)
			tmp->_mat[i] += _mat[i];
		return (tmp);
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Matrix *operator+");
}

Value* Matrix::operator-(const Value *rhs) const
{
	std::cout << "Matrix *operator-" << std::endl;
	if (rhs->GetType() == value_type::MATRIX)
	{
		const Matrix	*tmp_mat = static_cast<const Matrix*>(rhs);
		if (_row != tmp_mat->getRow() && _col != tmp_mat->getCol())
			throw(std::runtime_error("COMPUTATION ERROR! Matrix *operator- : different size"));
		Matrix *tmp = new Matrix(*this);
		for (int i = 0, len = _mat.size(); i < len; ++i)
			tmp->_mat[i] -= tmp_mat->getMat()[i];
		return (tmp);
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Matrix *operator-");
}

Value* Matrix::operator*(const Value *rhs) const
{
	std::cout << "Matrix *operator*" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		Matrix *tmp = new Matrix(*this);
		double rat = tmp_rat->getRational();
		for (int i = 0, len = _mat.size(); i < len; ++i)
			tmp->_mat[i] *= rat;
		return (tmp);
	}
	else if (rhs->GetType() == value_type::MATRIX)
	{
		const Matrix	*tmp_mat = static_cast<const Matrix*>(rhs);
		if (_row != tmp_mat->getRow() && _col != tmp_mat->getCol())
			throw(std::runtime_error("COMPUTATION ERROR! Matrix *operator* : different size"));
		Matrix *tmp = new Matrix(*tmp_mat);
		for (int i = 0, len = _mat.size(); i < len; ++i)
			tmp->_mat[i] *= _mat[i];
		return (tmp);
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Matrix *operator*");
}

Value* Matrix::operator/(const Value *rhs) const
{
	std::cout << "Matrix *operator/" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		Matrix *tmp = new Matrix(*this);
		double rat = tmp_rat->getRational();
		for (int i = 0, len = _mat.size(); i < len; ++i)
			tmp->_mat[i] /= rat;
		return (tmp);
	}
	else if (rhs->GetType() == value_type::MATRIX)
	{
		const Matrix	*tmp_mat = static_cast<const Matrix*>(rhs);
		if (_row != tmp_mat->getRow() && _col != tmp_mat->getCol())
			throw(std::runtime_error("COMPUTATION ERROR! Matrix *operator/ : different size"));
		Matrix *tmp = new Matrix(*this);
		for (int i = 0, len = _mat.size(); i < len; ++i)
			tmp->_mat[i] /=tmp_mat->getMat()[i];
		return (tmp);
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Matrix *operator/");
}

Value* Matrix::operator%(const Value *rhs) const
{
	throw std::runtime_error("ERROR!!! Matrix operator%");
}

Value* Matrix::operator^(const Value *rhs) const
{
	std::cout << "Matrix *operator^" << std::endl;

	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		if (tmp_rat->getRational() < 0)
			throw std::runtime_error("COMPUTATION ERROR! Rational *operator^ : pow < 0");
		if (tmp_rat->getRational() != static_cast<int>(tmp_rat->getRational()))
			throw std::runtime_error("COMPUTATION ERROR! Rational *operator^ : pow is not int");
		Value *tmp = new Matrix(*this);
		for (int i = tmp_rat->getRational(); i > 1; i--)	
		{
			Value *tmp_save = tmp;
			tmp = this->matrix_miltiple(tmp);
			delete tmp_save;
		}
		return tmp;
	}
	else
		throw std::runtime_error("ERROR!!! Matrix operator^");
}

Value* Matrix::matrix_miltiple(const Value *rhs) const
{
	if (rhs->GetType() == value_type::MATRIX)
	{
		const Matrix	*tmp_mat = static_cast<const Matrix*>(rhs);
		if (_col != tmp_mat->getRow())
			throw(std::runtime_error("COMPUTATION ERROR! Matrix *operator** : wrong size"));
		Matrix *tmp = new Matrix(10);
		tmp->_row = this->_row;
		tmp->_col = tmp_mat->getCol();
		for (int i = 0, len = tmp->_col * tmp->_row; i < len; ++i)
			tmp->_mat.push_back(0);
		for (int i = 0; i < tmp->_row; ++i)
			for (int j = 0; j < tmp->_col; ++j)
				for (int k = 0; k < _col; ++k)
					tmp->_mat[i * tmp->_col + j] += _mat[i * _col + k] * tmp_mat->_mat[k * tmp_mat->_col + j];
		return (tmp);
	}
	else
		throw std::runtime_error("ERROR!!! Matrix matrix_miltiple");
}
