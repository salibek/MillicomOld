// StrGen.cpp: ���������� ����� ����� ��� ����������� ����������.

#include "stdafx.h"
#include "Consts.h"
#include "Bus.h"
#include "Console.h"
#include "StrGen.h"
#include "Lex.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	LoadPoint LP = LoadPoint();
	BusFU Bus;
//	STR = "LexTest.ind";
//	string STR = "InOut.ind";
	string STR = "Neuro.ind";
	//	STR = "ALE.ind";
	LP.Type = Tstring;
	LP.Point = &STR;
	Bus.ProgFU(10, LP);
//	int temp = 8; // ��� �� 8 - �� InOut
//	Bus.ProgFU(1, {Cint,&temp});
	system("pause");
	return 0;
}