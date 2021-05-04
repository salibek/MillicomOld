#pragma once
#include <omp.h>
#include "Consts.h"

class TemperatEx : public FU  // �������������� ���������� ������� ��������� ����
{
public:
	~TemperatEx()
	{
		for (auto i : T_Neighbours)
			i.clear();
		T_Neighbours.clear();
		T.clear();
	};
	void ProgFU(int MK, LoadPoint Load) override;
	TemperatEx(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; ProgFU(0, { 0,nullptr }); };
	TemperatEx() : FU() { Bus = nullptr; };
	vector<double> T; // ������� �����������
	vector<vector<double>> T_Neighbours; // ����������� �������
	double a = 1; // ����������� � ���������
	vector<TemperatEx*> Neighbours; // ������ ������
	int X=-1, Y=-1; // ���������� ����
	double h2 = 0, tay = 0;
	bool FConst = false; // ���� ����������� �����������
	double ReadTime = 0, CalcTime = 0; // ����� ������ ��������� �������� � ���������� ������ ��������
	void* FiringProg = nullptr; // ���������, ����������� ��� ��������� ����
};

class NetManager: public FU // �������� ������� ��������
{
public:
	void ProgFU(int MK, LoadPoint Load) override;
	NetManager(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; ProgFU(0, { 0,nullptr }); };
	NetManager() : FU() { Bus = nullptr; };
private:
	double ManageTime = 0; // ����� ������ ��������� �������������� �����
	FU* NetScheduler = nullptr;
	vector<vector<TemperatEx*> > Items;
	int ConstTCounter = 0; // ������� ��� ConstTSet
	int X = 0, Y = 0, XC, YC;
	double h = 0, tay = 0;
	double a = 1; // ����������� � ���������
	int Ntay = 0, NtayCounter = 0; // ���������� ������ �������������
	double ReadTime = 0, CalcTime = 0; // ����� ������ ��������� �������� � ���������� ������ ��������
};