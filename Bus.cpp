#include "stdafx.h"
#include "consts.h"
#include "Bus.h"
#include "FUini.h"
#include <string>
#include <map>
#include <algorithm>
#include "IndFileConvertOld.h"

using namespace std;

void BusFU::FUTypesIni()
{
	FUs.push_back(nullptr);
	FUs.push_back(nullptr);
	FUTypeCorrect = 0;
}

void BusFU::ProgFU(int MK, LoadPoint Load)
{
	ICVect* ipVect; // ��������� �� ������ ��
	if (MK >= FUMkRange*2)
	{
		int FU_num = MK / FUMkRange;
		if(FU_num<FUs.size())
			FUs[FU_num]->ProgFU(MK%FUMkRange, Load);
	}
	else
		switch (MK%FUMkRange)
		{
		case 0: // �����
			break;

		case 1: // MakeFU ������� ��
			FUs.push_back(FUTypes[*(int *)Load.Point - FUTypeCorrect](this, FUTempl));
			break;
		case 5: // ProgExec ��������� ��������� �� ��
			ProgExec((vector<ip>*)Load.Point, Bus,nullptr);
			break;
		case 10: // FileOldProgExec ��������� ��������� �� �����
			ipVect = ConvIndOld(*(string*)Load.Point);
			if(ipVect->size()>0) ProgExec( (*ipVect)[0], this,nullptr);
			break;
		case 155:// FUTypeCorrectSet ���������� ��������� ������ ���� �� (��� �������� ��-��������� �� ������ ��-���������)
			FUTypeCorrect = *(int *)Load.Point;
			break;
		default:
			CommonMk(MK, Load);
			break;
		}
}