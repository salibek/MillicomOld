// �� �������������
#pragma once

#include "FUini.h"

class Chanel // ����� �������� ������
{
public:
	int Up = -1, Down = -1; // ������� � ������ ���������
	void* Receiver = nullptr; // �������� ������
	int ReceiverMk = -1; // �� ��� ��������� ������
};

class Router : public FU
{
	vector<Chanel> Channels; // ������ �������
	void* ErrRoutingProg = nullptr; // ������ �� ��������� ��������� ������ "�� ������ �������"
	int DelayTime = 0; // ����� ��������
//	vector<FU*>Queue; // ������� ��
	int MKCount = 0; // ���������� ���������� ��
	int MaxMKQueue = 0; // ������������ ����� �������
	double AverageMKQueue = 0; // ������� ����� �������
	double CurrentTime = 0; // ������� ����� �������������
	bool WorkMode = false; // ����� ������
	int ReceiverMkDefault = -1; // �� �� ��������� ��� ��������� ���������

public:
	void ProgFU(int MK, LoadPoint Load) override;
	Router(FU* BusContext, FU* Templ)
	{
		Bus = BusContext; ProgFU(0, { 0, nullptr });
	};

};