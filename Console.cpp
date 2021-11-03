// ФУ Консоль
#include "stdafx.h"
#include "Console.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

void Console::ProgFU(int MK, LoadPoint Load)
{
	switch (MK)
	{
	case 0: break;// Reset
	case 1: // Out Вывод
	case 2: // OutLn Вывод и перевод строки
	case 3: // LnOut Перевод строки и вывод
	case 4: // LnOutLn Перевод строки, вывод и снова перевод строки
		cout << prefix;
		if (MK == 3 || MK == 4) cout << endl;
		if (Load.Point != nullptr)
			Load.print(nullptr,"",Sep,End,ArrayBracketStart,ArrayBracketFin);
		if (MK == 2 || MK == 4) cout << endl;
		break;
	case 10: // LN Перевод строки
		cout << endl;
		break;
	case 15: //SepSet Установить строку-разделитель
		Sep = Load.ToStr();
		break;
	case 16: //EndSet Установить строку в конце вывода
		End = Load.ToStr();
		break;
	case 17: // ArrayBracketStartSet Установить строку, обозначающую открывающуюся скобку при вывод вектора
		ArrayBracketStart = Load.ToStr();
		break;
	case 18: // ArrayBracketStartSet Установить строку, обозначающую закрывающуюся скобку при вывод вектора
		ArrayBracketFin = Load.ToStr();
		break;
	case 20: // PrefixSet Установить префикс перед выводом
		if ((Load.Type) >> 1 == Dstring)
			prefix = *(string*)Load.Point;
		break;
	case 25: // FileNameSet
		filename = Load.ToStr();
		break;
	case 30: // OutFileSet Установить файл для вывода
		if(Load.Point==nullptr)
			ostream& out = cout;
		else
			freopen_s(&streamOut, Load.ToStr().c_str(), "w", stdout);
		break;

	case 31: // StdOutFileAppend Установить файл для дополнения
		if (Load.Point == nullptr)
			ostream& out = cout;
		else
			freopen_s(&streamOut, Load.ToStr().c_str(), "a", stdout);
		break;

	case 35: // StdInFileSet Установить файл для ввода
		if (Load.Point == nullptr)
//			std::istream& in == cin;
			;
		else
			freopen_s(&streamIn, Load.ToStr().c_str(), "r", stdin);
		break;
	default:
		CommonMk(MK, Load);
		break;
	}
}

