// FU Find
#include "stdafx.h"
#include <string.h>
#include "Find.h"

using namespace std;

void Find::ProgFU(int MK, LoadPoint Load)
{
	switch (MK)
	{
	case 0: // Reset
		Searcher.Clear();
		break;
	case 1: // Set ���������� ��������� �� ������ ��� ������
		Searcher.Template = Load;
		break;
	case 2: // AllSet ���������� �������� ������ � ���� ������ ��������� �� ������ ��� ������
		if(Load.Type>>1==DIC)
		{
			IC_type vk = (IC_type)Load.Point;
			Searcher.Template = vk->at(0).Load;
			Searcher.SuccessProg =(IC_type) vk->at(1).Load.Point;
			Searcher.FailProg = (IC_type) vk->at(2).Load.Point;
		}
		break;
	case 7: // MkModeSet ����� ���������� ���� �� � ��-������� (��-�� ��������� ����� �������, ������ �������� ������ 0) ��� ������ �������� ����� ���������������
		if (Load.Point == nullptr)
			Searcher.MkMode = true;
		else
			switch (Load.Type >> 1)
			{
			case Dbool: 
				Searcher.MkMode = *(bool*)Load.Point;
			case Dint:
				Searcher.MkMode = *(int*)Load.Point;
			}
		break;
	case 10: // SuccessProgSet ���������� ��������� �� ���������, ����������� ��� ������� ������ � ����� ������
		Searcher.SuccessProg = (IC_type)Load.Point;
		break;
	case 11: // SuccessAfterProgSet ���������� ��������� �� ���������, ����������� ��� ������� ������ � ����� ������ ����� ���������� �������� �����
		Searcher.SuccessAfterProg = (IC_type)Load.Point;
		break;
	case 15: // FailProgSet ���������� ��������� �� ���������, ����������� � ������ ���������� ������ � ����� ������
		Searcher.FailProg = (IC_type)Load.Point;
		break;
	case 16: // FailAfterProgSet ���������� ��������� �� ���������, ����������� � ������ ���������� ������ � ����� ������ ����� ���������� �������� �����
		Searcher.FailAfterProg = (IC_type)Load.Point;
		break;
	case 20: // ProgAtrSet
		if (Load.Point != nullptr && Load.Type >> 1 == Dint)
			Searcher.Prog_atr = *(int *)Load.Point;
		break;
	case 25: // BackOut
		if (Load.Type == TPPoint)
			(*(LoadPoint*)Load.Point) = Searcher.Obj;
		break;
	case 30: // BackOutMK
		if (Load.Type >> 1 == Dint)
			MkExec(Load, Searcher.Obj);
		break;
	case 35: // AtrBackOutMK
		if (Load.Type >> 1 == Dint)
			MkExec(Load, Searcher.Obj);
		break;

	case 90: // ProgAtrSet
		if ((Load.Type >> 1) == Dint)
			Searcher.Prog_atr = *(int*)Load.Point;
		break;
	case 100: // RezOut ������ ���������� ���������
		if (Load.Type == Tbool)
			*(bool*)Load.Point = Searcher.Rez;
		break;
	case 101: // RezOutMK ������ �� � ����������� ���������
		MkExec(*(int*)(Load.Point), {Cbool , &Searcher.Rez });
		break;

	case 220: // FindOr		
		Searcher.FindOr(Load);
		break;
	case 225: // FindAnd
		Searcher.FindAnd(Load);
		break;
	case 230: // FindXor
		Searcher.FindXor(Load);
		break;
	case 235: // FindAndSource
		Searcher.FindAndSource(Load);
		break;
	default:
		CommonMk(MK, Load);
	}
}