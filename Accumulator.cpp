#include "stdafx.h"
#include "AluGeneral.h"
#include "Accumulator.h"
#include "EnumMk.h"
#include <string>
#include <cmath>

bool		Accumulator::getSign() // 0 - положительное число, 1 - отрицательное
{
	switch (accumulatorOld.Type >> 1)
	{
	case Dint:
	{
	return *(int*)accumulatorOld.Point < 0;
	break; }
	case Dchar:
		return 0;
	case Dfloat:
		return *((float*)accumulatorOld.Point) < 0.0;
	case Ddouble:
		return *((double*)accumulatorOld.Point) < 0.0;
	default:
		return 0;
	}
}

void		Accumulator::EQ(LoadPoint load)
{
	sub(load);
	bool* t = new bool(!getLogic());
	set({Cbool,t});
};
void		Accumulator::NotEQ(LoadPoint load)
{
	sub(load);
	bool* t = new bool(getLogic());
	set({ Cbool,t });
};
void		Accumulator::Bigger(LoadPoint load)
{
	sub(load);
	bool* t = new bool(!getSign() && getLogic());

	set({ Cbool,t });
};
void		Accumulator::BiggerEQ(LoadPoint load)
{
	sub	(load);
	bool* t = new bool(!getSign());
	set({ Cbool,t });
};
void		Accumulator::Smaller(LoadPoint load)
{
	sub(load);
	bool* t = new bool(getSign());
	set({ Cbool,t });
};
void		Accumulator::SmallerEQ(LoadPoint load)
{
	sub(load);
	bool* t = new bool(getSign() || !getLogic());
	set({ Cbool,t });
};

void		Accumulator::Remainder(LoadPoint load)
{
	sub(load);
	bool* t = new bool(getSign() || !getLogic());
	set({ Cbool,t });
};


void		Accumulator::Clear() // ������� ������������
{
	if (accumulatorOld.Point == nullptr || accumulatorOld.Type == 0) return;
	switch (accumulatorOld.Type>>1)
	{
	case Dint:
		delete (int*)accumulatorOld.Point;	  break;
	case Dchar:
		delete (char*)accumulatorOld.Point;  break;
	case Dfloat:
		delete (float*)accumulatorOld.Point; break;
	case Ddouble:
		delete (double*)accumulatorOld.Point;break;
	case Dbool:
		delete (bool*)accumulatorOld.Point;  break;
	case Dstring:
		delete (string*)accumulatorOld.Point;break;
	}
	accumulatorOld.Type = 0;
}

void	Accumulator::error_msg(int error_code)
{
	switch (error_code)
	{
	case 1:
		cout << "Not registered operation!";
		break;
	case 2:
		cout << "Not allowed operation!";
		break;
	case 3:
		cout << "Divided by zero!";
		break;
	}
}

void	Accumulator::calc(int MK, LoadPoint load)
{
	switch (MK)
	{
	case E_MK::RESET_A: // Reset
		// ������� ������������
		accumulatorOld.Type = Cint;
		accumulatorOld.Point = new int(0);
		break;
	case E_MK::SET: // Set
		set(load);
		break;
	case E_MK::INC: // inc
		inc(load);
		set(load);
		break;
	case E_MK::DEC: // dec
		dec(load);
		set(load);
		break;
	case E_MK::SUM:
		add(load);
		break;
	case E_MK::SUB:
		sub(load);
		break;
	case E_MK::MULT:
		mult(load);
		break;
	case E_MK::DIV:
		div(load);
		break;
	case E_MK::MIN:
		fu_min(load);
		break;
	case E_MK::MAX:
		fu_max(load);
		break;
	case E_MK::COS:
		fu_cos();
		break;
	case E_MK::SIN:
		fu_sin();
		break;
	case E_MK::TAN:
		fu_tan();
		break;
	case E_MK::ACOS:
		fu_acos();
		break;
	case E_MK::ASIN:
		fu_asin();
		break;
	case E_MK::ATAN:
		fu_atan();
		break;
	case E_MK::MOD:
		fu_mod(load);
		break;
	case E_MK::SQRT:
		fu_sqrt();
		break;
	case E_MK::POW:
		fu_pow(load);
		break;
	case E_MK::ABS:
		fu_abs();
		break;
	case E_MK::CEIL:
		fu_ceil();
		break;
	case E_MK::FLOOR:
		fu_floor();
		break;
	case E_MK::ROUND:
		fu_round();
		break;
	case E_MK::LOG:
		fu_log();
		break;
	case E_MK::RANDOM:
		fu_random();
		break;
	case E_MK::AND:
		fu_and(load);
		break;
	case E_MK::OR:
		fu_or(load);
		break;
	case E_MK::INV:
		fu_inverse(load);
		break;
	case E_MK::DIV_INT:
		div_int(load);
		break;
	case E_MK::XOR:
		fu_xor(load);
		break;
	case E_MK::INV_BIT:
		fu_inv_bit(load);
		break;
	case E_MK::OR_BIT:
		fu_or_bit(load);
		break;
	case E_MK::AND_BIT:
		fu_and_bit(load);
		break;
	case E_MK::MR_BIT:
		fu_mr_bit(load);
		break;
	case E_MK::ML_BIT:
		fu_ml_bit(load);
		break;
	case E_MK::EQ:
		EQ(load);
		break;
	case E_MK::NotEQ:
		NotEQ(load);
		break;
	case E_MK::Bigger:
		Bigger(load);
		break;
	case E_MK::BiggerEQ:
		BiggerEQ(load);
		break;
	case E_MK::Smaller:
		Smaller(load);
		break;
	case E_MK::SmallerEQ:
		SmallerEQ(load);
		break;
	case E_MK::Remainder:
		Remainder(load);
		break;
	case E_MK::XOR_BIT:
		XOR_BIT(load);
	case E_MK::Compar3Way:
		Compar3Way(load);
	default:
		error_msg(1);
		break;
	}
}

void Accumulator::XOR_BIT(LoadPoint load)
{
	switch (accumulatorOld.Type >> 1)
	{
	case Dint :
		*(int*)accumulatorOld.Point^=load.ToInt();
		break;
	case Dchar:
		*(char*)accumulatorOld.Point ^= load.ToChar();
		break;
	}
}

void Accumulator::inc(LoadPoint load)
{
	switch (load.Type >> 1)
	{
	case Dint:
		(*(int*)load.Point)++;
		break;
	case Dchar:
		(*(char*)load.Point)++;
		break;
	case Dfloat:
		(*(float*)load.Point)++;
		break;
	case Ddouble:
		(*(double*)load.Point)++;
		break;
	}
}

void Accumulator::dec(LoadPoint load)
{
	switch (load.Type >> 1)
	{
	case Dint:
		(*(int*)load.Point)--;
		break;
	case Dchar:
		(*(char*)load.Point)--;
		break;
	case Dfloat:
		(*(float*)load.Point)--;
		break;
	case Ddouble:
		(*(double*)load.Point)--;
		break;
	}
}

void	Accumulator::add(LoadPoint load)
{
	char		tmp = accumulatorOld.Type;
	char		tmp2 = load.Type;
	char		r_tmp = w_type[tmp] > w_type[tmp2] ? tmp : tmp2;

	if (((tmp == Tstring || tmp == Cstring) && (tmp2 != Tstring || tmp2 != Cstring)))
		error_msg(2);
	switch (r_tmp>>1)
	{
	case Dint:
	{int *a=new int(accumulatorOld.ToInt());
//	*a = accumulator.ToInt();
	*a += load.ToInt();
	accumulatorOld.Clear();
	unsigned int t = accumulatorOld.Type;
	accumulatorOld = { t, (void*)a };
	break; }
	case Dchar:
	{char* a = (char*)load.Point, * b = (char*)accumulatorOld.Point;
	*a = *a + *b;
	accumulatorOld.Point = (void*)a;
	break; }
	case Dfloat:
	{float* a = (float*)load.Point, * b = (float*)accumulatorOld.Point;
	*a = *a + *b;
	accumulatorOld.Point = (void*)a;
	break; }
	case Ddouble:
	{double* a = (double*)load.Point, * b = (double*)accumulatorOld.Point;
	*a = *a + *b;
	accumulatorOld.Point = (void*)a;
	break; }
	}
	accumulatorOld.Type = r_tmp;
}

void	Accumulator::sub(LoadPoint load)
{
	char		tmp = accumulatorOld.Type;
	char		tmp2 = load.Type;
	char		r_tmp = tmp > tmp2 ? tmp : tmp2;

	if (((tmp == Tstring || tmp == Cstring || tmp2 == Tstring || tmp2 == Cstring)))
		error_msg(2);
	switch (r_tmp>>1)
	{
	case Dint:
	{int* b = (int*)load.Point, * a = (int*)accumulatorOld.Point;
	*a = *a - *b;
	accumulatorOld.Point = (void*)a;
	break; }
	case Dchar:
	{char* a = (char*)load.Point, * b = (char*)accumulatorOld.Point;
	*a = *a - *b;
	accumulatorOld.Point = (void*)a;
	break; }
	case Dfloat:
	{float* a = (float*)load.Point, * b = (float*)accumulatorOld.Point;
	*a = *a - *b;
	accumulatorOld.Point = (void*)a;
	break; }
	case Ddouble:
	{double* a = (double*)load.Point, * b = (double*)accumulatorOld.Point;
	*a = *a - *b;
	accumulatorOld.Point = (void*)a;
	break; }
	}
	accumulatorOld.Type = r_tmp;
}

void	Accumulator::mult(LoadPoint load)
{
	char		tmp = accumulatorOld.Type;
	char		tmp2 = load.Type;
	char		r_tmp = w_type[tmp] > w_type[tmp2] ? tmp : tmp2;

	if (((tmp == Tstring || tmp == Cstring || tmp2 == Tstring || tmp2 == Cstring)))
		error_msg(2);
	switch (r_tmp>>1)
	{
	case Dint:
	{int* b = (int*)load.Point, * a = (int*)accumulatorOld.Point;
	*a = *a * *b;
	accumulatorOld.Point = (void*)a;
	break; }
	case Dchar:
	{char* a = (char*)load.Point, * b = (char*)accumulatorOld.Point;
	*a = *a * *b;
	accumulatorOld.Point = (void*)a;
	break; }
	case Dfloat:
	{float* a = (float*)load.Point, * b = (float*)accumulatorOld.Point;
	*a = *a * *b;
	accumulatorOld.Point = (void*)a;
	break; }
	case Ddouble:
	{double* a = (double*)load.Point, * b = (double*)accumulatorOld.Point;
	*a = *a * *b;
	accumulatorOld.Point = (void*)a;
	break; }
	}
	accumulatorOld.Type = r_tmp;
}

void	Accumulator::div(LoadPoint load)
{
	if (!load.isDigit())
	{
		// Сообщение об ошибке...
		return;

	}
	char		tmp = accumulatorOld.Type;
//	char		tmp2 = w_type[load.Type];
//	char		r_tmp = w_type[tmp] > w_type[tmp2] ? tmp : tmp2;

//	if (((tmp == Tstring || tmp == Cstring || tmp2 == Tstring || tmp2 == Cstring)))
//		error_msg(2);
//	else if ((int)load.Point == 0)
//		error_msg(3);
	if (accumulatorOld.Type >> 1 != Ddouble)
	{
		double* t = new double();
		*t = accumulatorOld.ToDouble(0);
		accumulatorOld.VarDel();
		accumulatorOld.Type = Tdouble;
		accumulatorOld.Point = t;
	}
	*(double*)accumulatorOld.Point /= load.ToDouble();
//	cout << "Accum: "<<accumulator.ToDouble() << endl;;
	/*
	switch (r_tmp>>1)
	{
	case Dint:
	{int* b = (int*)load.Point, * a = (int*)accumulator.Point;

	*a = *a / *b;
	accumulator.Point = (void*)a;
	break; }
	case Dchar:
	{char* a = (char*)load.Point, * b = (char*)accumulator.Point;
	*a = *a / *b;
	accumulator.Point = (void*)a;
	break; }
	case Dfloat:
	{float* a = (float*)load.Point, * b = (float*)accumulator.Point;
	*a = *a / *b;
	accumulator.Point = (void*)a;
	break; }
	case Ddouble:
	{double* a = (double*)load.Point, * b = (double*)accumulator.Point;
	*a = *a / *b;
	accumulator.Point = (void*)a;
	break; }
	}
	accumulator.Type = r_tmp;
	*/
}

void	Accumulator::div_int(LoadPoint load)
{
	char		tmp = accumulatorOld.Type;
	char		tmp2 = w_type[load.Type];

	if (((tmp == Tstring || tmp == Cstring || tmp2 == Tstring || tmp2 == Cstring)))
		error_msg(2);
	else if (load.ToInt() == 0)
		error_msg(3);
	int* t = new int;
	int tt = accumulatorOld.ToInt() / load.ToInt();
	*t = tt;
	accumulatorOld = {Tint, (void*)t };
}

LoadPoint Accumulator::get()
{
	return accumulatorOld;
//	accumulator.print();
}

void Accumulator::Out(LoadPoint Load) // �������� ����������� � ����������
{
	if (Load.Point == nullptr) return;
	switch (Load.Type>>1)
	{
		case Dint:
			if ((accumulatorOld.Type >> 1) == Dint)
				*(int*) Load.Point = *(int*)accumulatorOld.Point;
			break;
	}
}

void* Accumulator::VarNew(LoadPoint load)
{
	switch (load.Type>>1)
	{
	case Dint:
		return new int(*(int*)load.Point);
	case Dfloat:
		return new float(*(float*)load.Point);
	case Ddouble:
		return new double(*(double*)load.Point);
	case Dchar:
		return new char(*(char*)load.Point);
	case Dbool:
		return new bool(*(bool*)load.Point);
	case Dstring:
		return new string(*(string*)load.Point);
	}
}

void		Accumulator::set(LoadPoint load)
{
	if (load.Point==nullptr)
		{accumulatorOld = { Tbool, new int(0) }; return;}
	accumulatorOld.Clear();
	accumulatorOld.Type = load.Type;
	accumulatorOld.Point = VarNew(load);
}

bool		Accumulator::getLogic() // ����������� ����������� ����
{
	int		type = accumulatorOld.Type;

	switch (type>>1)
	{
	case Dint:
		return *(int*)accumulatorOld.Point;
	case Dfloat:
		return *(float*)accumulatorOld.Point;
	case Ddouble:
		return *(double*)accumulatorOld.Point;
	case Dchar:
		return *(char*)accumulatorOld.Point;
	case Dbool:
		return *(bool*)accumulatorOld.Point;
	case Dstring:
		return *(string*)accumulatorOld.Point!="";
	}
}

bool		Accumulator::getLogic(LoadPoint load) // ����������� ����������� ����
{
	int		type = load.Type;

	switch (type >> 1)
	{
	case Dint:
		return *(int*)accumulatorOld.Point;
	case Dfloat:
		return *(float*)accumulatorOld.Point;
	case Ddouble:
		return *(double*)accumulatorOld.Point;
	case Dchar:
		return *(char*)accumulatorOld.Point;
	case Dbool:
		return *(bool*)accumulatorOld.Point;
	case Dstring:
		return *(string*)accumulatorOld.Point != "";
	}
}

void	Accumulator::fu_max(LoadPoint load)
{
	char		tmp1 = accumulatorOld.Type;
	char		tmp2 = load.Type;
	char		r_tmp = 0;
	if (tmp2 >> 1 == Ddouble || tmp1 >> 1 == Ddouble)
		r_tmp = Cdouble;
	else if(tmp2 >> 1 == Dfloat || tmp1 >> 1 == Dfloat)
		r_tmp = Cfloat;
	else if (tmp2 >> 1 == Dint || tmp1 >> 1 == Dint)
		r_tmp = Cint;
	else if (tmp2 >> 1 == Dstring && tmp1 >> 1 == Dstring)
		r_tmp = Dstring;
	else
		error_msg(2);
//	else if ((int)load.Point == 0)
//		error_msg(3);

//	char		tmp2 = w_type[load.Type];
	//	char		r_tmp = w_type[tmp] > w_type[tmp2] ? tmp : tmp2;

	double a_old = accumulatorOld.ToDouble(); // Старое значение аккумулятора

//	if (((tmp == Tstring || tmp == Cstring || tmp2 == Tstring || tmp2 == Cstring)))
//		error_msg(2);
//	else if ((int)load.Point == 0)
//		error_msg(3);

	switch (r_tmp >> 1)
	{
	case Dint:
	{//int b = load.ToInt(), a = accumulator.Point;
	int b = load.ToInt();
	if (b > accumulatorOld.ToInt())
	{
		accumulatorOld.Clear();
		int* a = new int(b);
		accumulatorOld = { Cint,(void*)a };
	}
	break; }
	case Dchar:
	{char* a = (char*)load.Point, * b = (char*)accumulatorOld.Point;
	*a = *a > * b ? *a : *b;
	accumulatorOld.Point = (void*)a;
	break; }
	case Dfloat:
	{float* a = (float*)load.Point, * b = (float*)accumulatorOld.Point;
	*a = *a > * b ? *a : *b;
	accumulatorOld.Point = (void*)a;
	break; }
	case Ddouble:
	{double* a = (double*)load.Point, * b = (double*)accumulatorOld.Point;
	*a = *a > * b ? *a : *b;
	accumulatorOld.Point = (void*)a;
	break; 
	}
	case Dstring:
		string* s1 = (string*)load.Point, * s2 = (string*)accumulatorOld.Point;
		*s1 = *s1 > * s2 ? *s1 : *s2;
		accumulatorOld.Point = (string*)s1;
	}
	accumulatorOld.Type = r_tmp;
	if(accumulatorOld.ToDouble()> a_old)
		((FU*)((FU*)Parent))->ProgExec(((AluGeneral*)Parent)->ThreadStack.back().MaxProg);
}

void	Accumulator::fu_min(LoadPoint load)
{
	char		tmp = accumulatorOld.Type;
	char		tmp2 = w_type[load.Type];
	char		r_tmp = w_type[tmp] > w_type[tmp2] ? tmp : tmp2;

	double a_old = accumulatorOld.ToDouble(); // Старое значение аккумулятора

	if (((tmp == Tstring || tmp == Cstring || tmp2 == Tstring || tmp2 == Cstring)))
		error_msg(2);
	else if (*(int*)load.Point == 0)
		error_msg(3);
	switch (r_tmp >> 1)
	{
	case Dint:
	{int* b = (int*)load.Point, * a = (int*)accumulatorOld.Point;
	*a = *a < * b ? *a : *b;
	accumulatorOld.Point = (void*)a;
	break; }
	case Dchar:
	{char* a = (char*)load.Point, * b = (char*)accumulatorOld.Point;
	*a = *a < * b ? *a : *b;
	accumulatorOld.Point = (void*)a;
	break; }
	case Dfloat:
	{float* a = (float*)load.Point, * b = (float*)accumulatorOld.Point;
	*a = *a < * b ? *a : *b;
	accumulatorOld.Point = (void*)a;
	break; }
	case Ddouble:
	{double* a = (double*)load.Point, * b = (double*)accumulatorOld.Point;
	*a = *a < * b ? *a : *b;
	accumulatorOld.Point = (void*)a;
	break;
	}
	case Dstring:
		string* s1 = (string*)load.Point, * s2 = (string*)accumulatorOld.Point;
		*s1 = *s1 < * s2 ? *s1 : *s2;
		accumulatorOld.Point = (string*)s1;
	}
	accumulatorOld.Type = r_tmp;
	if (accumulatorOld.ToDouble() > a_old)
		((FU*)((FU*)Parent))->ProgExec(((AluGeneral*)Parent)->ThreadStack.back().MaxProg);
}

void	Accumulator::fu_cos()
{
	char		tmp = accumulatorOld.Type;

	if ((tmp >> 1) == Dstring)
		error_msg(2);

	double* a = (double*)accumulatorOld.Point;
	*a = cos(*a);
	accumulatorOld.Point = (void *)a;
	accumulatorOld.Type = Tdouble;
}

void	Accumulator::fu_sin()
{
	char		tmp = accumulatorOld.Type;

	if ((tmp >> 1) == Dstring)
		error_msg(2);

	double* a = (double*)accumulatorOld.Point;
	*a = sin(*a);
	accumulatorOld.Point = (void*)a;
	accumulatorOld.Type = Tdouble;
}

void	Accumulator::fu_acos()
{
	char		tmp = accumulatorOld.Type;

	if ((tmp >> 1) == Dstring)
		error_msg(2);

	double* a = (double*)accumulatorOld.Point;
	*a = acos(*a);
	accumulatorOld.Point = (void*)a;
	accumulatorOld.Type = Tdouble;
}

void	Accumulator::fu_asin()
{
	char		tmp = accumulatorOld.Type;

	if ((tmp >> 1) == Dstring)
		error_msg(2);

	double* a = (double*)accumulatorOld.Point;
	*a = asin(*a);
	accumulatorOld.Point = (void*)a;
	accumulatorOld.Type = Tdouble;
}

void	Accumulator::fu_tan()
{
	char		tmp = accumulatorOld.Type;

	if ((tmp >> 1) == Dstring)
		error_msg(2);

	double* a = (double*)accumulatorOld.Point;
	*a = tan(*a);
	accumulatorOld.Point = (void*)a;
	accumulatorOld.Type = Tdouble;
}

void	Accumulator::fu_atan()
{
	char		tmp = accumulatorOld.Type;

	if ((tmp >> 1) == Dstring)
		error_msg(2);

	double* a = (double*)accumulatorOld.Point;
	*a = cos(*a);
	accumulatorOld.Point = (void*)a;
	accumulatorOld.Type = Tdouble;
}

void	Accumulator::fu_mod(LoadPoint load)
{
	char		tmp = accumulatorOld.Type;
	char		tmp2 = load.Type;

	if ((tmp >> 1) != Dint || (tmp2 >> 1) != Dint)
		error_msg(2);
	
	int* b = (int*)load.Point;
	int* a = (int*)accumulatorOld.Point;
	*a = *a % *b;
	accumulatorOld.Point = (void*)a;
	accumulatorOld.Type = Tint;
}

void	Accumulator::fu_sqrt()
{
	char		tmp = accumulatorOld.Type;

	if ((tmp >> 1) == Dstring)
		error_msg(2);

	double* a = (double*)accumulatorOld.Point;
	*a = sqrt(*a);
	accumulatorOld.Point = (void*)a;
	accumulatorOld.Type = Tdouble;
}

void	Accumulator::fu_pow(LoadPoint load)
{
	char		tmp = accumulatorOld.Type;
	char		tmp2 = load.Type;

	if ((tmp >> 1) == Dstring || (tmp2 >> 1) == Dstring)
		error_msg(2);

	double* a = (double*)accumulatorOld.Point;
	double* b = (double*)load.Point;
	*a = pow(*a, *b);
	accumulatorOld.Point = (void*)a;
	accumulatorOld.Type = Tdouble;
}

void	Accumulator::fu_abs()
{
	char		tmp = accumulatorOld.Type;

	if ((tmp >> 1) == Dstring)
		error_msg(2);

	double* a = (double*)accumulatorOld.Point;
	*a = abs(*a);
	accumulatorOld.Point = (void*)a;
	accumulatorOld.Type = tmp;
}

void	Accumulator::fu_ceil()
{
	char		tmp = accumulatorOld.Type;

	if ((tmp >> 1) == Dstring)
		error_msg(2);

	double* a = (double*)accumulatorOld.Point;
	*a = ceil(*a);
	accumulatorOld.Point = (void*)a;
	accumulatorOld.Type = tmp;
}

void	Accumulator::fu_floor()
{
	char		tmp = accumulatorOld.Type;

	if ((tmp >> 1) == Dstring)
		error_msg(2);

	double* a = (double*)accumulatorOld.Point;
	*a = floor(*a);
	accumulatorOld.Point = (void*)a;
	accumulatorOld.Type = tmp;
}

void	Accumulator::fu_round()
{
	char		tmp = accumulatorOld.Type;

	if ((tmp >> 1) == Dstring)
		error_msg(2);

	double* a = (double*)accumulatorOld.Point;
	*a = round(*a);
	accumulatorOld.Point = (void*)a;
	accumulatorOld.Type = tmp;
}

void	Accumulator::fu_log()
{
	char		tmp = accumulatorOld.Type;

	if ((tmp >> 1) == Dstring)
		error_msg(2);

	double* a = (double*)accumulatorOld.Point;
	*a = log(*a);
	accumulatorOld.Point = (void*)a;
	accumulatorOld.Type = Tdouble;
}

void	Accumulator::fu_random()
{
	char		tmp = accumulatorOld.Type;

	if ((tmp >> 1) == Dstring)
		error_msg(2);

	double* a = (double*)accumulatorOld.Point;
	*a = rand();
	accumulatorOld.Point = (void*)a;
	accumulatorOld.Type = tmp;
}

LoadPoint	Accumulator::getCos()
{
	char		tmp = accumulatorOld.Type;
	LoadPoint   load;

	if ((tmp >> 1) == Dstring)
		error_msg(2);

	double* a = (double*)accumulatorOld.Point;
	*a = cos(*a);
	load.Type = Ddouble;
	load.Point = (void*)a;
	return load;
}

LoadPoint	Accumulator::getSin()
{
	char		tmp = accumulatorOld.Type;
	LoadPoint   load;

	if ((tmp >> 1) == Dstring)
		error_msg(2);

	double* a = (double*)accumulatorOld.Point;
	*a = sin(*a);
	load.Type = Ddouble;
	load.Point = (void*)a;
	return load;
}


void		Accumulator::fu_inverse(LoadPoint load)
{
	bool		t = !getLogic();
	accumulatorOld.Point = new bool(*(bool*)load.Point);
	accumulatorOld.Type = Tbool;

	bool		*val = (bool *)accumulatorOld.Point;
	*val = t;
}

void		Accumulator::fu_and(LoadPoint load)
{
	bool t1 = getLogic();
	bool t2 = getLogic(load);

	accumulatorOld.Point = new bool(*(bool*)load.Point);
	accumulatorOld.Type = Tbool;
	*(bool*)accumulatorOld.Point = t1 && t2;
}

void		Accumulator::fu_or(LoadPoint load)
{
	bool t1 = getLogic();
	bool t2 = getLogic(load);

	accumulatorOld.Point = new bool(*(bool*)load.Point);
	accumulatorOld.Type = Tbool;
	*(bool*)accumulatorOld.Point = t1 || t2;
}

void		Accumulator::fu_xor(LoadPoint load)
{
	bool t1 = getLogic();
	bool t2 = getLogic(load);

	accumulatorOld.Point = new bool(*(bool*)load.Point);
	accumulatorOld.Type = Tbool;
	*(bool*)accumulatorOld.Point = (!t1 || !t2) && (t1 || t2);
}

void		Accumulator::fu_or_bit(LoadPoint load)
{
	char t1 = load.Type >> 1;
	char t2 = accumulatorOld.Type >> 1;

	if (t1 == Dstring || t2 == Dstring || t1 == Ddouble || t2 == Ddouble
		|| t1 == Dfloat || t2 == Dfloat)
		error_msg(2);
	else
	{
		int		*a = (int *)accumulatorOld.Point;
		int		*b = (int *)load.Point;

		*a = *a | *b;
	}
}

void		Accumulator::fu_and_bit(LoadPoint load)
{
	char t1 = load.Type >> 1;
	char t2 = accumulatorOld.Type >> 1;

	if (t1 == Dstring || t2 == Dstring || t1 == Ddouble || t2 == Ddouble
		|| t1 == Dfloat || t2 == Dfloat)
		error_msg(2);
	else
	{
		int		*a = (int *)accumulatorOld.Point;
		int		*b = (int *)load.Point;

		*a = *a & *b;
	}
}

void		Accumulator::fu_mr_bit(LoadPoint load)
{
	char t1 = load.Type >> 1;
	char t2 = accumulatorOld.Type >> 1;

	if (t1 == Dstring || t2 == Dstring || t1 == Ddouble || t2 == Ddouble
		|| t1 == Dfloat || t2 == Dfloat)
		error_msg(2);
	else
	{
		int		*a = (int *)accumulatorOld.Point;
		int		*b = (int *)load.Point;

		*a = *a >> *b;
	}
}

void		Accumulator::fu_ml_bit(LoadPoint load)
{
	char t1 = load.Type >> 1;
	char t2 = accumulatorOld.Type >> 1;

	if (t1 == Dstring || t2 == Dstring || t1 == Ddouble || t2 == Ddouble
		|| t1 == Dfloat || t2 == Dfloat)
		error_msg(2);
	else
	{
		int		*a = (int *)accumulatorOld.Point;
		int		*b = (int *)load.Point;

		*a = *a << *b;
	}
}

void		Accumulator::fu_inv_bit(LoadPoint load)
{
	char t1 = load.Type >> 1;
	char t2 = accumulatorOld.Type >> 1;

	if (t1 == Dstring || t2 == Dstring || t1 == Ddouble || t2 == Ddouble
		|| t1 == Dfloat || t2 == Dfloat)
		error_msg(2);
	else
	{
		int		*a = (int *)accumulatorOld.Point;
		int		*b = (int *)load.Point;

		*a = ~*a;
	}
}
void		Accumulator::Compar3Way(LoadPoint load){// Трехстороннее сравнение
	double T1 = accumulatorOld.ToDouble();
	double T2 = load.ToDouble();
	accumulatorOld.Write((T1>0)? 1:((T1==T2)?0:-1) );
}