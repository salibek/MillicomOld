#include "stdafx.h"
#include "consts.h"
#include "Router.h"
#include "FUini.h"

using namespace std;

void Router::ProgFU(int MK, LoadPoint Load)
{
	switch (MK)
	{
	case 200: // Routing ���������� ������������� MK
		if (Load.Point != nullptr)
		{
			// ����� ���������
			auto i = Channels.begin();
			for (; i != Channels.end(); i++)
				if (Load.Type >> 1 == DIP)
				{
					if (((ip*)Load.Point)->atr >= i->Down && ((ip*)Load.Point)->atr < i->Up)
					{
						if(i->ReceiverMk<0)
							((FU*)i->Receiver)->ProgFU(((ip*)Load.Point)->atr, ((ip*)Load.Point)->Load); // ��������� �������� ��� ����������� ��
						else
							((FU*)i->Receiver)->ProgFU(i->ReceiverMk, Load); // ��������� ��������
						MKCount++;
						break;						
					}
				}
				else if (Load.Type >> 1 == DIC)
					if (((IC_type)Load.Point)->begin()->atr >= i->Down && ((IC_type)Load.Point)->begin()->atr < i->Up)
						{
						if (i->ReceiverMk < 0)
							((FU*)i->Receiver)->ProgFU(((IC_type)Load.Point)->begin()->atr, ((IC_type)Load.Point)->begin()->Load); // ��������� �������� ��� ����������� ��
						else
							((FU*)i->Receiver)->ProgFU(i->ReceiverMk, Load); // ��������� ��������
						MKCount++;
						break;
						}
			if (i == Channels.end())
				ProgExec(ErrRoutingProg); // ������ �������������
		}
		break;
	case 0: // �����
		Channels.clear();
		MKCount = 0;
		break;
	case 1: // ChCreate ������� ����� ����� (�� ����� �� ������ ������� ���������)
		Channels.push_back({0,Load.ToInt(-1),Bus,-1});
		if (Channels.back().Down >= 0)
			Channels.back().Up = Channels.back().Down + FUMkRange; // ��������� ������� ������� �� ���������
		break;
	case 3: //ChClear �������� ��������� �������
		Channels.clear();
		break;
	case 5: // DelayTimeSet ���������� ����� �������� ��
		DelayTime = Load.ToDouble();
		break;
	case 6: // MkCounterSet ���������� �������� �������� ��
		MKCount = Load.ToInt();
		break;
	case 8: // ErrRoutingProgset ������ �� ��������� ��������� ������ "�� ������ �������"
		ErrRoutingProg = Load.Point;
		break;
	case 9: // ReceiverMkDefaultSet ���������� �������� �� ��� ��������� �� ���������
		ReceiverMkDefault = Load.ToInt(-1);
		break;
	case 10: // ReceiverSet ���������� ����� ��-���������
		Channels.back().Receiver = Load.Point;
		break;
	case 11: // ReceiverMkSet ���������� �� ��-���������
		Channels.back().ReceiverMk = Load.ToInt(-1);
		break;
	case 15: // RangeUpSet ���������� ������� �������� �������
		Channels.back().Up= Load.ToInt(-1);
		break;
	case 20: // RangeDownSet ���������� ������ �������� �������
		Channels.back().Down = Load.ToInt(-1);
		if (Channels.back().Up < 0)
			Channels.back().Up = Channels.back().Down + FUMkRange; // �������������� ��������� �������� ������� ��������� ������� ��-��������� �� ���������
		break;
	case 25: // MkCountOut ������ ���������� ���������� ��
		Load.Write(int(MKCount));
		break;
	case 30: // MkCountOutMk ������ �� � ����������� ���������� ��
		Load.Write(MKCount);
		break;
	case 35: // MaxMkQeueOut ������ ���� ����� ������� ��
		Load.Write(MaxMKQueue);
		break;
	case 40: // MaxMkQeueOutMk ������ �� � ���� ������ ������� ��
	{
		MkExec(Load, { Cint,&MKCount });
		break;
	}
	case 45: // EverageMkQeueOut ������ ������� ����� ������� ��
		Load.Write(double(AverageMKQueue));
		break;
	case 50:// EverageMkQeueOutMk ������ �� �� ������� ������ ������� ��
	{
		double t;
		if (CurrentTime > 0)
			t = AverageMKQueue / CurrentTime;
		else
			t = 0;
		MkExec(Load, { Cdouble,&t });

		break;
	}
	default:
		CommonMk(MK, Load);
		break;
	}
}