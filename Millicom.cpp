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

using namespace std;

int main()
{
	LoadPoint LP = LoadPoint();
	BusFU Bus;
	MeanShift MSh;
	//	STR = "LexTest.ind";
	//	string STR = "InOut.ind";
//	string STR = "NetTemperat.ind";
//	string STR = "MeanShift.txt";
//	string STR = "MeanShift.ind";
	//	string STR = "FSM.ind";
	//	STR = "ALE.ind";
//	LP.Type = Tstring;
//	LP.Point = &STR;

	//MSh.ProgFU(5, LP);
//	Bus.ProgFU(10, LP);

	string STR = "temp.ind";
	Bus.ProgFU(10, {Cstring, &STR});
	//	int temp = 8; // Тип ФУ 8 - ФУ InOut
	//	Bus.ProgFU(1, {Cint,&temp});
//	string STR = "Gauss.txt";
//	FU* G=GaussIni(nullptr,nullptr);
//	G->ProgFU(1, { Cstring,&STR });
	system("pause");
	return 0;
}