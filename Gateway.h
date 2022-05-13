// �� ����
#pragma once

#include "FUini.h"

class ForwardChannel : public FU
{
//	FUProgram: TFUProgram; // ������ �� ��������� ���������� ������ ������ ��
	FU* Receiver = nullptr; // �������� ������
	int ReceiverMk = -1; // ������������ ��� �����-���������
	FU* GatewayFU = nullptr; // ������ �� �� ����, � �������� ����������� �����
	int N = 0; // ����� ������
	// bool BackChannel; // ���� ��������� ����������� �������� ����������
	double ByteTime = 0; // ����� �������� ������ ����� ���������� �� �����
	int ServiseLength = 0; // ����� ���������� ��������� ������ �����
	int BatchWidth = 0; // ����� ����� ������������ ����������
	double AcceptTime = 0; // ����� ������������� �������� ������
	double WaitTime = 0; // ����� �������� �������������

};
//PSluceChannel = ^ TSluceChannel;

class BackChennel : public FU
{
	FU* ContextUk = nullptr; // ��������� �� �������� �� �����
	int N_Chanel = 0; // ����� ������, �� �������� ������ ������������
	FU* GatewayFU = nullptr; // ������ �� �� ����, � �������� ����������� �����
	int TransCount = 0; // �������� ������� ����������� � ���� � ������ �������
//	QReceiv, QReceivTail: PAtrData; // ������� ���������� ����������� �����������
};

class Gateway : public FU
{
	FU* ContextUk = nullptr; // ��������� �� �������� �� �����
	int N_Chanel = 0; // ����� ������, �� �������� ������ ������������
	FU* Receiver = nullptr; // ������ �� �����, �� �������� ������ ��
	int TransCount = 0; // �������� ������� ����������� � ���� � ������ �������
//	QReceiv, QReceivTail: PAtrData; // ������� ���������� ����������� �����������

	BackChennel BChennel; // �������� ��� ��������� ������

//	CurrentContext: PGatewaySimulator; // ��������� �� ������� �������� (�� ������������� �� �������� ���������� � ���� ��� � ������ �������)
	double TransDelay = 0; // �������� �������� ������
	int Index = 0, Direction = 0; // ������ �������� ������ �������� ������
	int ChannelDim = 0; // ����������� ������� �������
	vector<ForwardChannel> Chennels;
//	FU* Node1 = nullptr, Node2 = nullptr; // ��������� �� �������������� ��, ������� ���������� ���������
	double SluceCPU = 0; // ����� ������ �����

	int ProbFunk = 0; // ����� ������������� ����������� ����� ( 0 - �����������, 1- ����������������, 2 - ������, 3- ����������)
	// ��������� ���������� �������� ������������� �����
	double alpha = 0; // ����� ��� ����������������� �������������
	double k = 0; // �������� k ������������� �������
	double o = 0; // �������� � ������������� �������
	double mu = 0; // ���������� �� ����������� �������������
	double sigma = 0; // ���������� ����� ��� ����������� �������������
	double PFail = 0; // ����������� ������ ��� ������������ ������������� ��� �������� ������ ���� ����������

	double ByteTime = 0; // ����� �������� ������ ����� ���������� �� �����
	int ServiseLength = 0; // ����� ���������� ��������� ������ �����
	int BatchWidth = 0; // ����� ����� ������������ ����������
	double AcceptTime = 0; // ����� ������������� �������� ������
	double WaitTime = 0; // ����� �������� �������������

public:
	void ProgFU(int MK, LoadPoint Load) override;
	Gateway(FU* BusContext, FU* Templ)
	{
		Bus = BusContext;
	};
};