#pragma once

enum class token_type
{
	EQUAL,					// =
	PLUS,					// +
	MINUS,					// -
	MULTIPLICATION,			// *
	MATRIX_MULTIPLICATION,	// **
	DIVISION,				// /
	DIVISION_MOD,			// %
	POWER,					// ^
	ROUND_BRACET_OPEN,		// (
	ROUND_BRACET_CLOSE,		// )
	SQUARE_BRACET_OPEN,		// [
	SQUARE_BRACET_CLOSE,	// ]
	COMMA,					// ,
	SEMICOLON,				// ;
	QUESTION,				// ?
	DIGIT_INT,				// arguments
	DIGIT_DOUBLE,			// arguments
	COMPLEX,				// i
	VARIABLE,				// unknown string may be - function, unknown, matrix, error....
};

enum class lexer_type
{
	VARIABLE,				// a = 1 : 3
	MATRIX,					// a = [[1]] : 7
	FUNCTION,				// f(a) = a : 6
	SOLVE,					// a = ? : 3 
	POLINOM,				// a = 1 ? : 4
};
