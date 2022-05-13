#include "stdafx.h"
#include "consts.h"
#include "Gateway.h"
#include "FUini.h"

using namespace std;

void Gateway::ProgFU(int MK, LoadPoint Load)
{

	switch (MK)
	{
	case 0: // �����
	{
		Index = 0;
		ChannelDim = 0;
		TransDelay = 0; // �������� �������� ������
		Direction = 0;
		SluceCPU = 0;
//		QReceiv = nullptr; QReceivTail = nullptr;
//			BackChennel.QReceiv = nullptr; BackChennel.QReceivTail = nullptr;
		TransCount = 0; 
//		BackChennel.TransCount = 0;

		Receiver = nullptr;
		N_Chanel = -1;
//			BackChennel.Receiver = nullptr;
//			BackChennel.N_Chanel = -1;

		BatchWidth = 0;
		ServiseLength = 0;
		ByteTime = 0;
		AcceptTime = 500;
		WaitTime = 500;

		ProbFunk = 0;
			// ��������� ���������� �������� ������������� �����
		alpha = 1; // ����� ��� ����������������� �������������
		k = 1; // �������� k ������������� �������
		o = 1; // �������� � ������������� �������
		mu = 1; // ���������� �� ����������� �������������
		sigma = 1; // ���������� ����� ��� ����������� �������������
		PFail = 0;
	}	break;

	case 1: // ������� ����� � ���������� ��������
		break;
	case 5: // ������ ������ �� ��������� �����
//		Load.Write(int());
		break;
	case 10: // ������ ������������ �� ������� �� ��������� �����
//		Load.Write(int(MKCount));
		break;
	case 15: // ���������� ������� ���������� ��������� ����� �����
		break;
	case 20: // ���������� ������ � ������ ����, � ������� ���������� ���������� ����������� �����
		break;
	case 25: // ���������� ������ � ������ ����, � ������� ���������� ���������� ����������� �����
		break;
	case 30: // ����� ���� ��� ����� �� ������� �������������� ���� (� �������� ����������� �������� 0 - ������, 1 - �����, 2 - �����, 3 - ����)
		break;
	case 35: // ���������� ����� �������� �������� ������������ ����� ����
		break;
	case 40: // ������ ����������� � ������ ���������� ����� ���� ����������� ���� (Farvard)
//		Load.Write(int(MKCount));
		break;
	case 45: // ������ ����������� � ������ ���������� ����� ���� ����������� ������� (Back)
//		Load.Write(int(MKCount));
		break;
	case 50:// ������ ����������� � ������ ���������� ����� ���� ����������� ���� � ������� (FarwardBack)
//		Load.Write(int(MKCount));
		break;
	case 55: // ������ ����� �����������, ���������� �������� ���� (Farvard)
//		Load.Write(int(MKCount));
		break;
	case 60: // ������ ����� �����������, ���������� �������� ���� (Back)
//		Load.Write(int(MKCount));
		break;
	case 65: // ������ ����� �����������, ���������� �������� ���� (FarwardBack)
//		Load.Write(int(MKCount));
		break;
	case 70: // ���������� ����� ���������� ��������� ������ �����
		break;
	case 75: // ���������� ����� �����
		break;
	case 80: // ���������� ����� ������������� �������� ������
		break;
	case 85: // ���������� ����� ������������� ��������
		break;
	case 90: // ���������� ����� �������� ������ ����� �� ����� �����
		break;
	case 95: // ���������� ����� ������������� ����� (0-��� 1 - �����������, 2- ����������������, 3 - ������, 4- ����������)
		break;
	case 100: // ����� ��� ����������������� �������������
		break;
	case 105: // �������� k ������������� �������
		break;
	case 110: // �������� � ������������� �������
		break;
	case 115: // ���������� �� ����������� �������������
		break;
	case 120: // ����������� ������ ��� ������������ ������������� ��� �������� ������ ���� ����������
		break;
	case 125: // �������� �������� ��� �� ������� ���������� �������
		break;

	default:
		CommonMk(MK, Load);
		break;
	}
}