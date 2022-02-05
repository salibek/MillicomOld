	#pragma once
	#include "stdafx.h"
	#include "Threader.h"
	#include "Consts.h"

	// Контекст АЛУ
	class ALUContext
	{
	public:
		unsigned int accumType = 0; // Тип данных
		double		accum = 0;		// Скалярный аккумулятор
		string		accumStr;		// строковой аккулятор
		void* accumPoint = nullptr;	// Указатель на аккумулятор (вектор, матрица и т.п.)
		vector<int> MkOut; // вектор МК для резульатов
		vector<LoadPoint> OutAdr; // вектор адресов для записи результатов
	};

	class ALU: FU
	{
		void		sub(LoadPoint load);
		void		div(LoadPoint load);
		void		div_int(LoadPoint load);
		void		mult(LoadPoint load);
		void		inc(LoadPoint load);
		void		dec(LoadPoint load);
//		void		*Parent; // Ссылка на родительсний ФУ АЛУ
	public:
		unsigned int accumType = 0; // Тип данных
		double		accum = 0;		// Скалярный аккумулятор
		string		accumStr;		// строковой аккулятор
		void* accumPoint = nullptr;	// Указатель на аккумулятор (вектор, матрица и т.п.)
		vector<int> MkOut; // вектор МК для резульатов
		vector<LoadPoint> OutAdr; // вектор адресов для записи результатов

		vector<ALUContext> Stack = {};
		ALU(void* parent, FU* Templ) { Parent = parent; };
		void ProgFU(int MK, LoadPoint Load) override;
		void*		Parent = nullptr;

		void		add(LoadPoint load);
		void		Clear();
		void*		VarNew(LoadPoint load); // New value of accum
		void		set(LoadPoint load);
		void		error_msg(int error_code);
		void		calc(int MK, LoadPoint load);
		LoadPoint	get();
		bool		getLogic();
		bool		getSign(); // 0 - положительное число, 1 - отрицательное
		bool		getLogic(LoadPoint load);
		void		Out(LoadPoint); // ������ ������������ � ����������
		//	~Accumulator() { Clear(); };
		void		fu_min(LoadPoint load);
		void		fu_max(LoadPoint load);
		void		fu_cos(LoadPoint Load);
		void		fu_sin(LoadPoint Load);
		void		fu_tan(LoadPoint Load);
		void		fu_asin(LoadPoint Load);
		void		fu_acos(LoadPoint Load);
		void		fu_atan(LoadPoint Load);
		void		fu_mod(LoadPoint load);
		void		fu_sqrt(LoadPoint Load);
		void		fu_pow(LoadPoint load);
		void		fu_abs(LoadPoint Load);
		void		fu_ceil(LoadPoint Load);
		void		fu_floor(LoadPoint Load);
		void		fu_round(LoadPoint Load);
		void		fu_log(LoadPoint Load);
		void		fu_random();
		void		fu_inverse(LoadPoint load);
		void		fu_and(LoadPoint load);
		void		fu_or(LoadPoint load);
		void		fu_xor(LoadPoint load);
		void		fu_or_bit(LoadPoint load);
		void		fu_and_bit(LoadPoint load);
		void		fu_mr_bit(LoadPoint load);
		void		fu_ml_bit(LoadPoint load);
		void		fu_inv_bit(LoadPoint load);
		void		EQ(LoadPoint load);
		void		NotEQ(LoadPoint load);
		void		Bigger(LoadPoint load);
		void		BiggerEQ(LoadPoint load);
		void		Smaller(LoadPoint load);
		void		SmallerEQ(LoadPoint load);
		void		Remainder(LoadPoint load);
		void		XOR_BIT(LoadPoint load);
		void		Compar3Way(LoadPoint load);// Трехстороннее сравнение

		void	getCos(LoadPoint Load);
		void	getSin(LoadPoint Load);
		// Подрограммы сообщений об ошибках
		
	};