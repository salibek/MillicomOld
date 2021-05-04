#pragma once


enum E_MK
{
	RESET,					// 0
	PROG,					// 1
	PROG_CYCLE,				// 2
	PROG_POST,				// 3
	PROG_BREAK,				// 4
	YES_PROG,				// 5	
	YES_PROG_CYCLE,			// 6
	YES_PROG_POST,			// 7
	YES_PROG_BREAK,			// 8
	NO_PROG,				// 9
	NO_PROG_CYCLE,			// 10
	NO_PROG_POST,			// 11
	NO_PROG_BREAK,			// 12
	BREAK,					// 13
	CONTINUE,				// 14
	CALC,					// 15
	DEEP_OUT,				// 16
	DEEP_OUT_MK,			// 17
	GO,						// 18
	YES_GO,					// 19
	NO_GO,					// 20
	OUT_SET,				// 21
	OUT_MK_SET,				// 22
	OUT,					// 23
	OUT_MK,					// 24
	
	// �������� � ������������� 
	RESET_A,
	SET,					// 25
	GET,					// 26
	GET_LOGIC,				// 27
	OUT_A,					// 28
	SUM,					// 29
	SUB,					// 30
	DIV,					// 31
	MULT,					// 32
	INC,					// 33
	DEC,					// 34
	MIN,					// 35
	MAX,					// 36
	COS,					// 37
	SIN,					// 38
	TAN,
	ASIN,					// 39
	ACOS,					// 40
	ATAN,					// 41
	MOD,					// 42
	SQRT,					// 43
	POW,					// 44
	ABS,					// 45
	CEIL,					// 46
	FLOOR,					// 47
	ROUND,					// 48
	LOG,					// 49
	RANDOM,					// 50
	INV,					// 51
	AND,					// 52
	OR,						// 53
	DIV_INT,				// 54
	XOR,					// 55
	INV_BIT,				// 56
	OR_BIT, 				// 57
	AND_BIT,				// 58
	MR_BIT,					// 59
	ML_BIT,					// 60
	EQ,						// 63
	NotEQ,					// 64
	Bigger,
	BiggerEQ,
	Smaller,
	SmallerEQ
};