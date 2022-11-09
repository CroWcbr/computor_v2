#pragma once

enum class lexer_type
{
	SOLVE,					// a = ? : len 3 
	POLINOM,				// a = 1 ? : len 4
	FUNCTION,				// f(a) = a : len 6
	MATRIX,					// a = [[1]] : MATRIX input
	RAT_COM_MAT,			// RATIONAL, COMPLEX, MATRIX
	COMMAND,				// help, show, history
};

enum class token_type
{
	OPERATION,		// + - * / % ** ^
	VARIABLE,		// x
	DIGIT,			// 1.1
	COMPLEX,		// i
	FUNCTION,		// f(x) and standart function
	BRACET,			// ( )
	MATRIX_PARSE	// [ ] , ;
};

enum class value_type
{
	RATIONAL,
	COMPLEX,
	MATRIX,
	FUNCTION
};
