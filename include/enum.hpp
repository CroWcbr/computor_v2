#pragma once

enum class lexer_type
{
	SOLVE,					// a = ? : len 3 
	POLINOM,				// a = 1 ? : len 4
	FUNCTION,				// f(a) = a : len 6
	MATRIX,					// a = [[1]] : MATRIX input
	RAT_COM_MAT				// RATIONAL, COMPLEX, MATRIX
};

enum class token_type
{
	OPERATION,		// + - * / % ** ^
	VARIABLE,		// x
	DIGIT,			// 1.1
	COMPLEX,		// i
	FUNCTION,		// f(x)
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

// enum class token_type
// {
// 	PLUS,					// +
// 	MINUS,					// -
// 	MULTIPLICATION,			// *
// 	MATRIX_MULTIPLICATION,	// **
// 	DIVISION,				// /
// 	DIVISION_MOD,			// %
// 	POWER,					// ^
// 	ROUND_BRACET_OPEN,		// (
// 	ROUND_BRACET_CLOSE,		// )
// 	SQUARE_BRACET_OPEN,		// [
// 	SQUARE_BRACET_CLOSE,	// ]
// 	COMMA,					// ,
// 	SEMICOLON,				// ;
// 	COMPLEX,				// i
// 	DIGIT,					// arguments
// 	VARIABLE				// unknown string may be - function, unknown, matrix, error....
// };
