#include "../include/Matrix.hpp"
#include "../include/Computation.hpp"

Matrix::Matrix(const Matrix &other):Value(other.GetType(), "_tmp") { *this = other; }

Matrix::Matrix(int const row, int const col):Value(value_type::MATRIX, "_tmp")
{
	_row = row;
	_col = col;
	_mat.insert(_mat.begin(), _row * _col, 0);
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

Matrix::Matrix(std::vector<Token>& mat, std::map<std::string, Value*> const &_val)
: Value(value_type::MATRIX, "_tmp")
{
if (is_debug)
{
	std::cout << "Matrix:" << std::endl;
	for (auto i : mat)
		std::cout << i.getLexem() << " ";
	std::cout << std::endl;
}

	_col = 0;
	_row = 0;
	for (int i = 1, len = mat.size() - 1; i < len; i++)
	{
		std::string	lexem_i = mat[i].getLexem();
		if (mat[i].getLexem() == "[")
			_row++;
		// else if (mat[i].getType() == token_type::DIGIT)
		// {
		// 	int znak = 1;
		// 	if (mat[i - 1].getLexem() == "-")
		// 		znak = -1;
		// 	_mat.push_back(std::stod(mat[i].getLexem()) * znak);
		// 	_col++;
		// }
		else if (lexem_i == "]" || lexem_i == ";" || lexem_i == "," || \
				lexem_i == "-" || lexem_i == "+")
			;
		else
		{
			std::vector<Token>	expr_in_matrix;
			while(mat[i].getLexem() != "," && mat[i].getLexem() != "]")
			{
				expr_in_matrix.push_back(mat[i]);
				i++;
			}
			Computation		result(expr_in_matrix, _val);
			_col++;
			Value	*tmp = result.getValue()->clone();
			if (tmp->GetType() == value_type::RATIONAL)
			{
				const Rational	*tmp_rat = static_cast<const Rational*>(tmp);
				_mat.push_back(tmp_rat->getReal());
				delete tmp;
			}
			else if (tmp->GetType() == value_type::COMPLEX)
			{
				delete tmp;
				throw std::runtime_error("PARSE MATRIX ERROR! Token is Matrix or Function or Complex");
			}
			else
			{
				delete tmp;
				throw std::runtime_error("PARSE MATRIX ERROR! Unknown Token");
			}
		}

	}
	_col /= _row;
};

int const &Matrix::getCol() const { return _col; }

int const &Matrix::getRow() const { return _row; }

std::vector<double> const &Matrix::getMat() const { return _mat; }

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
	std::string tmp;
	for (auto &tok : to_token())
		tmp.append(tok.getLexem() + " ");
	tmp.pop_back();
	return tmp; 
}

Value* Matrix::clone() const { return new Matrix(*this); }

std::vector<Token> Matrix::to_token() const 
{
	std::vector<Token> tmp;
	tmp.push_back(Token("[", token_type::MATRIX_PARSE));
	for (int r = 0; r < _row; r++)
	{
		tmp.push_back(Token("[", token_type::MATRIX_PARSE));
		for (int c = 0; c < _col; c++)
		{
			tmp.push_back(Token(std::to_string( _mat[c + r * _col]), token_type::DIGIT));
			if (c != _col - 1)
				tmp.push_back(Token(",", token_type::MATRIX_PARSE));
		}
		tmp.push_back(Token("]", token_type::MATRIX_PARSE));
		if (r < _row - 1)
			tmp.push_back(Token(";", token_type::MATRIX_PARSE));
	}
	tmp.push_back(Token("]", token_type::MATRIX_PARSE));
	return tmp;
}

bool Matrix::getSimple() const { return false; }

Value* Matrix::operator+(const Value *rhs) const
{
	if (is_debug)
		std::cout << "Matrix *operator+" << std::endl;
	if (rhs->GetType() == value_type::MATRIX)
	{
		const Matrix	*tmp_mat = static_cast<const Matrix*>(rhs);
		if (_row != tmp_mat->getRow() || _col != tmp_mat->getCol())
			throw(std::runtime_error("COMPUTATION ERROR! Matrix *operator+ : different size"));
		Matrix *tmp = new Matrix(*this);
		for (int i = 0, len = _mat.size(); i < len; ++i)
			tmp->_mat[i] += tmp_mat->getMat()[i];
		return (tmp);
	}
	else if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		Matrix *tmp = new Matrix(*this);
		double rat = tmp_rat->getReal();
		for (int i = 0, len = _mat.size(); i < len; ++i)
			tmp->_mat[i] += rat;
		return (tmp);
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		return (*tmp_fun + this);
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		throw std::runtime_error("COMPUTATION ERROR! Matrix *operator+ Complex - don't realized");
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Matrix *operator+");
}

Value* Matrix::operator-(const Value *rhs) const
{
	if (is_debug)
		std::cout << "Matrix *operator-" << std::endl;
	if (rhs->GetType() == value_type::MATRIX)
	{
		const Matrix	*tmp_mat = static_cast<const Matrix*>(rhs);
		if (_row != tmp_mat->getRow() || _col != tmp_mat->getCol())
			throw(std::runtime_error("COMPUTATION ERROR! Matrix *operator- : different size"));
		Matrix *tmp = new Matrix(*this);
		for (int i = 0, len = _mat.size(); i < len; ++i)
			tmp->_mat[i] -= tmp_mat->getMat()[i];
		return (tmp);
	}
	else if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		Matrix *tmp = new Matrix(*this);
		double rat = tmp_rat->getReal();
		for (int i = 0, len = _mat.size(); i < len; ++i)
			tmp->_mat[i] -= rat;
		return (tmp);
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		Rational		*tmp_rat_minus = new Rational(-1);
		Value			*tmp_fun_minus = NULL;
		Value			*tmp = NULL;
		tmp_fun_minus = *tmp_fun * tmp_rat_minus;
		tmp = *tmp_fun_minus + this;
		delete tmp_rat_minus;	
		delete tmp_fun_minus;
		return (tmp);
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		throw std::runtime_error("COMPUTATION ERROR! Matrix *operator- Complex - don't realized");
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Matrix *operator-");
}

Value* Matrix::operator*(const Value *rhs) const
{
	if (is_debug)
		std::cout << "Matrix *operator*" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		Matrix *tmp = new Matrix(*this);
		double rat = tmp_rat->getReal();
		for (int i = 0, len = _mat.size(); i < len; ++i)
			tmp->_mat[i] *= rat;
		return (tmp);
	}
	else if (rhs->GetType() == value_type::MATRIX)
	{
		const Matrix	*tmp_mat = static_cast<const Matrix*>(rhs);
		if (_col != tmp_mat->getRow())
			throw(std::runtime_error("COMPUTATION ERROR! Matrix *operator* : _col != tmp_mat->getRow()"));
		Matrix	*tmp = new Matrix(_row, tmp_mat->getCol());
			for (int r1 = 0; r1 < tmp->getRow(); r1++)
			{
				for (int c2 = 0; c2 < tmp->getCol(); c2++)
				{
					tmp->_mat[r1 * tmp->getCol() + c2] = 0;
					for (int cr = 0; cr < _col; cr++)
						tmp->_mat[r1 * tmp->getCol() + c2] += _mat[r1 * _col + cr] * tmp_mat->getMat()[cr * tmp_mat->getCol() + c2];
				}
			}
		return (tmp);
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		return (*tmp_fun * this);
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		throw std::runtime_error("COMPUTATION ERROR! Matrix *operator* Complex - don't realized");
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Matrix *operator*");
}

Value* Matrix::operator/(const Value *rhs) const
{
	if (is_debug)
		std::cout << "Matrix *operator/" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		if (tmp_rat->getReal() == 0)
			throw std::runtime_error("COMPUTATION ERROR! Matrix *operator/ : zero division");
		Matrix *tmp = new Matrix(*this);
		double rat = tmp_rat->getReal();
		for (int i = 0, len = _mat.size(); i < len; ++i)
			tmp->_mat[i] /= rat;
		return (tmp);
	}
	else if (rhs->GetType() == value_type::MATRIX)
	{
		const Matrix	*tmp_mat = static_cast<const Matrix*>(rhs);
		Matrix			*tmp_new_mat = new Matrix(*tmp_mat);
		Rational		*tmp_rat_minus = new Rational(-1);
		Value	*tmp_val;
		try
		{
			tmp_val = *tmp_new_mat ^ tmp_rat_minus;
			delete tmp_new_mat;
			delete tmp_rat_minus;
		}
		catch(const std::exception& e)
		{
			delete tmp_new_mat;
			delete tmp_rat_minus;
			throw std::runtime_error(e.what());
		}
		Value	*result = *tmp_val * this;
		delete tmp_val;
		return (result);
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		Function 		*tmp_new = new Function(*tmp_fun);
		Rational		*tmp_rat = new Rational(1);
		Value			*tmp_val = NULL;
		try
		{
			tmp_val = *tmp_rat / tmp_new;
			delete tmp_rat;
			delete tmp_new;
		}
		catch(const std::exception& e)
		{
			delete tmp_rat;
			delete tmp_new;
			throw std::runtime_error(e.what());
		}
		Value		*result = *tmp_val * this;
		delete tmp_val;
		return result;
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		throw std::runtime_error("COMPUTATION ERROR! Matrix *operator/ Complex - don't realized");
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Matrix *operator/");
}

Value* Matrix::operator%(const Value *rhs) const
{
	(void)rhs;
	if (is_debug)
		std::cout << "Matrix *operator%" << std::endl;
	throw std::runtime_error("COMPUTATION ERROR! Matrix *operator%% - don't realized");
}

Value* Matrix::operator^(const Value *rhs) const
{
	if (is_debug)
		std::cout << "Matrix *operator^" << std::endl;
	if (rhs->GetType() == value_type::RATIONAL)
	{
		const Rational	*tmp_rat = static_cast<const Rational*>(rhs);
		if (_row != _col)
			throw std::runtime_error("COMPUTATION ERROR! Matrix *operator^ : matrix is not squere");
		if (tmp_rat->getReal() == -1)
			return new Matrix(inverse());
		if (tmp_rat->getReal() < 0)
			throw std::runtime_error("COMPUTATION ERROR! Matrix *operator^ : pow < 0");
		if (tmp_rat->getReal() != static_cast<int>(tmp_rat->getReal()))
			throw std::runtime_error("COMPUTATION ERROR! Matrix *operator^ : pow is not int");
		if (tmp_rat->getReal() == 0)
		{
			Matrix *tmp = new Matrix(_row, _col);
			for (int i = 0; i < _row; i++)
				tmp->_mat[i * _row + i] = 1;
			return tmp;
		}
		else
		{
			Value *tmp = new Matrix(*this);
			for (int i = tmp_rat->getReal(); i > 1; i--)
			{
				Value *tmp_save = tmp;
				tmp = this->matrix_miltiple(tmp);
				delete tmp_save;
			}
			return tmp;
		}
	}
	else if (rhs->GetType() == value_type::FUNCTION)
	{
		// throw std::runtime_error("COMPUTATION ERROR! Matrix *operator^ Function - don't realized");
		const Function	*tmp_fun = static_cast<const Function*>(rhs);
		std::vector<Token> tmp_token = to_token();
		Function *tmp_new = new Function(*tmp_fun);
		tmp_new->_simple = false;
		tmp_new->_map.clear();
		tmp_new->_func.insert(tmp_new->_func.begin(), Token("(", token_type::BRACET));
		tmp_new->_func.push_back(Token(")", token_type::BRACET));
		tmp_new->_func.insert(tmp_new->_func.begin(), Token("^", token_type::OPERATION));
		tmp_new->_func.insert(tmp_new->_func.begin(), Token(")", token_type::BRACET));
		tmp_new->_func.insert(tmp_new->_func.begin(), tmp_token.begin(), tmp_token.end());
		tmp_new->_func.insert(tmp_new->_func.begin(), Token("(", token_type::BRACET));

		// tmp_new->_func.push_back(Token(")", token_type::BRACET));
		return tmp_new;
	}
	else if (rhs->GetType() == value_type::COMPLEX)
	{
		throw std::runtime_error("COMPUTATION ERROR! Matrix *operator^ Complex - don't realized");
	}
	else
		throw std::runtime_error("COMPUTATION ERROR! Matrix *operator^");
}

Value* Matrix::matrix_miltiple(const Value *rhs) const
{
	if (is_debug)
		std::cout << "Matrix *matrix_miltiple" << std::endl;
	if (rhs->GetType() == value_type::MATRIX)
	{
		const Matrix	*tmp_mat = static_cast<const Matrix*>(rhs);
		if (_col != tmp_mat->getRow())
			throw(std::runtime_error("COMPUTATION ERROR! Matrix *operator** : wrong size"));
		Matrix *tmp = new Matrix(_row, tmp_mat->getCol());
		for (int i = 0; i < tmp->_row; ++i)
			for (int j = 0; j < tmp->_col; ++j)
				for (int k = 0; k < _col; ++k)
					tmp->_mat[i * tmp->_col + j] += _mat[i * _col + k] * tmp_mat->_mat[k * tmp_mat->_col + j];
		return (tmp);
	}
	else
		throw std::runtime_error("COMPUTATION ERROR!!! Matrix matrix_miltiple");
}

//ctrl+c -> ctrl+v from project enter_the_matrix
double	Matrix::ft_abs_double(const double &tmp) const { return tmp < 0 ? -1 * tmp : tmp; }

Matrix	Matrix::upper_triangular_matrix_change_znak_when_swap_row(Matrix tmp) const
{
	for (int r = 0, c = 0; r < _row && c < _col; c++)
	{
		if (ft_abs_double(tmp._mat[r * _col + c]) < EPS)
			for (int i = r + 1; i < _row; i++)
				if (ft_abs_double(tmp._mat[i * _col + c]) > ft_abs_double(tmp._mat[r * _col + c]))
				{
					for (int j = 0; j < _col; j++)
					{
						double	ttt = tmp._mat[r * _col + j];
						tmp._mat[r * _col + j] = tmp._mat[i * _col + j];
						tmp._mat[i * _col + j] = -ttt;
					}
					break;
				}
		if (ft_abs_double(tmp._mat[r * _col + c]) > EPS)
		{
			
			for (int i = r + 1; i < _row; i++)
			{
				double	scale_tmp = tmp._mat[i * _col + c] / tmp._mat[r * _col + c];
				for (int j = 0; j < _col; j++)
					tmp._mat[i * _col + j] -= scale_tmp * tmp._mat[r * _col + j];
			}
			r++;
		}
	}
	return tmp;
}

double	Matrix::determinant() const
{
	if (!is_square())
		throw std::length_error("THROW MATRIX determinant: !is_square");
	if (_row == 0 || _col == 0 )
		throw std::length_error("THROW MATRIX determinant: An empty matrix cannot have a determinant");

	Matrix	tmp(upper_triangular_matrix_change_znak_when_swap_row(*this));
	double			det = 1;

	for (int i = 0; i < _row; i++)
		det *= tmp._mat[i * _col + i];
	return det;
}

bool	Matrix::is_square() const { return (getRow() == getCol()); }

Matrix	Matrix::transpose() const
{
	Matrix	tmp(_col, _row);
	for (int r = 0; r < _row; r++)
		for (int c = 0; c < _col; c++)
			tmp._mat[c * _row + r] = _mat[r * _col + c];
	return tmp;
}

Matrix	 Matrix::cofactor_matrix_T(void) const
{
	Matrix com(_row, _col);
	for (int r = 0; r < _row; r++) 
	{
		for (int c = 0; c < _col; c++) 
		{
			Matrix tmp(*this);
			for (int k = 0; k < this->_row; k++) 
			{
				if (k != r)
					tmp._mat[k * _col + c] = 0;
				else
					tmp._mat[k * _col + c] = 1;
			}
			com._mat[r * _col + c] = tmp.determinant();
		}
	}	
	return com.transpose();
}

Matrix	&Matrix::scl(const double &a)
{
	for (int i = 0; i < _row * _col; i++)
		_mat[i] = _mat[i] * a;
	return *this;
}

Matrix	 Matrix::inverse() const
{
	if (!is_square())
		throw std::length_error("THROW MATRIX inverse: !is_square");
	double det = determinant();
	if (det == 0)
		throw std::length_error("THROW MATRIX inverse: det == 0");
	Matrix com = cofactor_matrix_T().scl(1 / det);
	return com;
}
