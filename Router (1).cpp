#include "stdafx.h"
#include "consts.h"
#include "Router.h"
#include "FUini.h"

using namespace std;

void Router::ProgFU(int MK, LoadPoint Load)
{

	switch (MK)
	{
	case 200: // Route ���������� �������������
		if (Load.Point != nullptr)
		{
			bool findDiap = false;
			ip ipInfo;
			ipInfo.Load.Point = Load.Point;

			for (int i = 0; i < Channels.size(); i++)// ����� ���������
				if ((ipInfo.atr > Channels[i].down) && (ipInfo.atr < Channels[i].Up))
					findDiap = true;
			//(ip*)Load.Point->atr - ������������, �� ������� ��������������...
			if (!findDiap)
				ProgExec(ErrRoutingProg);
		}
		break;
	case 0: // �����
		Channels.clear();
		break;
	case 1: // ChCreate ������� ����� ����� (�� ����� �� ��� ���������)
		Channels.push_back({0,0,nullptr,Load.ToInt(-1) });
		break;
	case 5: // DelayTimeSet ���������� ����� �������� ��
		DelayTime = Load.ToDouble();
		break;
	case 8: // ErrRoutingProgset ������ �� ��������� ��������� ������ "�� ������ �������"
		ErrRoutingProg = Load.Point;
		break;
	case 10: // ReceiverSet ���������� ����� ��-���������
		Channels.back().Receiver = Load.Point;
		break;
	case 11: // ReceiverMkSet ���������� �� ��-���������
		Channels.back().ReceiverMk = Load.ToInt(-1);
		break;
	case 15: // ���������� ������� �������� �������
		Channels.back().Up= Load.ToInt(-1);
		break;
	case 20: // ���������� ������ �������� �������
		Channels.back().down = Load.ToInt(-1);
		break;
	case 25: // ������ ���������� ���������� ��
		Load.Write(int(MKCount));
		break;
	case 30: // ������ �� � ����������� ���������� ��
		Load.Write(MKCount);
		break;
	case 35: // ������ ���� ����� ������� ��
		Load.Write(MaxMKQueue);
		break;
	case 40: // ������ �� � ���� ������ ������� ��
	{
		MkExec(Load, { Cint,&MKCount });
		break;
	}
	case 45: // ������ ������� ����� ������� ��
		Load.Write(double(AverageMKQueue));
		break;
	case 50:// ������ �� �� ������� ������ ������� ��
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