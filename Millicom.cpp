// StrGen.cpp: определяет точку входа для консольного приложения.

#include "stdafx.h"
#include "Consts.h"
#include "Bus.h"
#include "Console.h"
#include "StrGen.h"
#include "Lex.h"
#include <iostream>
#include <string>
#include <fstream>
#include "MeanShift.h"
#include "Bag.h"

using namespace std;

int main()
{
	LoadPoint LP = LoadPoint();
	BusFU Bus;
	MeanShift MSh;
	Bag B;
//	string STR = "NetTemperat.ind";
//	string STR = "MeanShift.txt";
//	string STR = "MeanShift.ind";
	//	string STR = "FSM.ind";
	//	STR = "ALE.ind";
//	LP.Type = Tstring;
//	LP.Point = &STR;

	//MSh.ProgFU(5, LP);
//	Bus.ProgFU(10, LP);

	string STR = "ALE2.ind";
//	string STR = "Bag.ind";
	//	string STR = "NetTemperat2.ind";
	Bus.ProgFU(10, {Cstring, &STR});

	string STR5 = "Bag5.txt"; // 5 предметов
	string STR6 = "Bag6.txt"; // 6 предметов
//	B.ProgFU(1, { Cstring, &STR5 });
//	B.ProgFU(10, { Cint, nullptr });

	//	int temp = 8; // Тип ФУ 8 - ФУ InOut
	//	Bus.ProgFU(1, {Cint,&temp});
//	string STR = "Gauss.txt";
//	FU* G=GaussIni(nullptr,nullptr);
//	G->ProgFU(1, { Cstring,&STR });
//	STR = "Bag.txt";
//	B.ProgFU(1, {Cstring, &STR});
	system("pause");
	return 0;
}