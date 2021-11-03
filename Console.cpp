// �� �������
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
	case 1: // Out �����
	case 2: // OutLn ����� � ������� ������
	case 3: // LnOut ������� ������ � �����
	case 4: // LnOutLn ������� ������, ����� � ����� ������� ������
		cout << prefix;
		if (MK == 3 || MK == 4) cout << endl;
		if (Load.Point != nullptr)
			Load.print(nullptr,"",Sep,End,ArrayBracketStart,ArrayBracketFin);
		if (MK == 2 || MK == 4) cout << endl;
		break;
	case 10: // LN ������� ������
		cout << endl;
		break;
	case 15: //SepSet ���������� ������-�����������
		Sep = Load.ToStr();
		break;
	case 16: //EndSet ���������� ������ � ����� ������
		End = Load.ToStr();
		break;
	case 17: // ArrayBracketStartSet ���������� ������, ������������ ������������� ������ ��� ����� �������
		ArrayBracketStart = Load.ToStr();
		break;
	case 18: // ArrayBracketStartSet ���������� ������, ������������ ������������� ������ ��� ����� �������
		ArrayBracketFin = Load.ToStr();
		break;
	case 20: // PrefixSet ���������� ������� ����� �������
		if ((Load.Type) >> 1 == Dstring)
			prefix = *(string*)Load.Point;
		break;
	case 25: // FileNameSet
		filename = Load.ToStr();
		break;
	case 30: // OutFileSet ���������� ���� ��� ������
		if(Load.Point==nullptr)
			ostream& out = cout;
		else
			freopen_s(&streamOut, Load.ToStr().c_str(), "w", stdout);
		break;

	case 31: // StdOutFileAppend ���������� ���� ��� ����������
		if (Load.Point == nullptr)
			ostream& out = cout;
		else
			freopen_s(&streamOut, Load.ToStr().c_str(), "a", stdout);
		break;

	case 35: // StdInFileSet ���������� ���� ��� �����
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

