#include "stdafx.h"
#include "StrGen.h"
#include <ctime>
#include <string>
#include <iostream>
using namespace std;

void StrGenContext::ProgFU(int MK, LoadPoint Load)
{
/*	switch (MK)
	{
	case 0: //Reset
//		str_buf.clear();
//		str_buf.push_back("");
		Receiver = nullptr;
		ReceiverMK = 0;
		str_buf_size = 1;
		LineCount = 0;
		Source.close();
		Receiver = Bus;
		str_bufCount = 0;
		break;
	case 20: //ReceiverSet ���������� ������ �� �������� �����
		Receiver = Load.Point;
	case 21: //ReceiverMkSet ���������� �� ��� ��������� �����
		if (Load.Type >> 1 == Dint) ReceiverMK = *(int*)Load.Point; break;
	case 1: // SourceSet
		break;
	case 2: // SourceSetStart
		break;
	case 3: // Start ������ ���������
		work = true;
		ProgExec(StartProg,Bus);// ��������� ��������� ���������
//		TimeStart = clock();
		TimeLong = 0;
		if (Load.Point != nullptr)
		{
			Filename = *((std::string*)(Load.Point));
			Source.open(Filename);
			LineCount = 0;
		}
		while (Source && work)
		{
			string str;
			getline(Source, str, '\n');
			LineCount++;
			if (str == "") continue;
			str_bufCount = (str_bufCount+1)%str_buf_size;
			str_buf[str_bufCount] = str;

			LoadPoint Point;
			Point.Type = 2;
			Point.Point = &str;

			((FU*)Receiver)->ProgFU(ReceiverMK, Point);
			system("pause");
		}
		if (work) // ������ ����������� �������
		{
			LoadPoint Point;
			Point.Type = 2;
			Point.Point = &finStr;
			((FU*)Receiver)->ProgFU(ReceiverMK, Point);
		}
		Source.close();
		TimeLong = clock() - TimeStart;
		ProgExec(FinProg, Bus);// ��������� ����������� ���������
		break;
	case 4: // Stop	
		work = false;
		ProgExec(StopProg, Bus);// ��������� ��������� �� ���������� ��������� �����
		break;
	case 5: // Pause
		work = false;
		break;
	case 6: // Continue
	{work = true;
	ProgFU(3, { 0, nullptr }); }
	break;
	case 9: // ModeSet

		break;
	case 10: // SourceReset

		break;

	case 11: // LogMkOut
		break;

	case 15: // TimeOut	������ ����� ���������� � ��������
		if (Load.Type == Tdouble)
			*(double*)Load.Point = (double) TimeLong/ CLOCKS_PER_SEC;
		if (Load.Type == Tfloat)
			*(float*)Load.Point = (float) TimeLong / CLOCKS_PER_SEC;
		break;
	case 30: // TimeMkOut ������ �� �� ������ ���������� � ��������
		MkExec(*(int*)(Load.Point), { Cdouble , new double((double)TimeLong / CLOCKS_PER_SEC) });
		break;
	case 35: // LineBufSizeSet ���������� ������ ������ �����
		str_buf_size = *(int*)Load.Point;
		str_bufCount = 0;
		str_buf.resize(str_buf_size);
		break;
	case 40: // LogOut
		break;
	case 50: // LineCountOutMk
		MkExec(*(int*)Load.Point, { Tint, &LineCount });
		break;
	case 51: // LastLineBufOutMk ������ �� � ��������� ������� �� ������
		MkExec(*(int*)Load.Point, { Tstring, &str_buf[str_bufCount] });
		break;
	case 52: // LineBufOutMk // ������ �� �� �������� �� ������
		for (int i = 0; i < str_buf_size; i++)
		{
			MkExec(*(int*)Load.Point, { Tstring, &str_buf[str_bufCount] });
			str_bufCount = (str_bufCount + 1) % str_buf_size;
		}
		break;

	case 60: // StartProgSet // ���������� ��������� �� ���������, ����������� ��� ������� ������� ����� �� �����
		StartProg = Load.Point;
		break;
	case 61: // FinProgSet // ���������� ��������� �� ���������, ����������� �� ���������� ��������� ����� �� �����
		FinProg = Load.Point;
		break;
	case 62: // StopProgSet // ���������� ��������� �� ���������, ����������� ��� ���������� ��������� ����� �� �����
		StopProg = Load.Point;
		break;
	default:
		CommonMk(MK, Load);
		break;
	}
	*/
}