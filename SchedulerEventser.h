#pragma once
#include "Consts.h"

class Eventser: public FU
{
	multimap<double, FU*> Events; // �������
	bool work = false; // ���� �������� �������������
	bool start = false; // ���� ������� �������� �������������
	double CurrentTime = 0; // ������� ����� �������������
	void* FinProg = nullptr; // ���������, ����������� �� ���������� �������������
	int EventCount = 0; // ������� �������
public:
	void ProgFU(int MK, LoadPoint Load) override;
	void Eventsing(FU* Context, double tay);
	Eventser(FU* BusContext, FU* Templ)
	{
		Bus = BusContext;
		ProgFU(0, { 0,nullptr });
	};
	Eventser() {};
};

class Scheduler : FU
{
	int NCores = 1, CoreCount = 0, CoreCountPrev = 0; // ���������� ���� � ������� ������� ����
	int MkQueuePrev = 0; // ���������� ����� ������� ��
	double SchedulingTime = 0, RunTime=0; // ����� ������������ ���������� � ������� �� ����������
	FU* eventser = nullptr; // ��������� �� ���������� �������
	vector<FU*>Queue; // ������� ���������� �� ��� ������ ������� ��� �������������
	vector<double> MkTimeQueue; // ������� ������ ���������� ��, ����������� � �������
	double* CurrentTime = 0; // ������� �����
	double PrevTime = 0, PrevCoreCount=0; // ��������� ����� ����������� ������� � ������� ������� ����
	double ParallelFactor = 0; // ����������� ������������
	double AverageMkQueue = 0; // ������� � ������������ ����� ������� ��
	int  MaxMkQueue = 0; // ������������ ����� ������� �� �� ���� ��, ������������ � ������� ������������
public:
	void* SchedulingProg = nullptr;
	void ProgFU(int MK, LoadPoint Load) override;
	void Scheduling(FU*, double DTime, bool CoreContinue=false); // CoreContinue - ���� ��������� ��������������� ����
	void CoreFree(); // ���������� ����
		Scheduler(FU* BusContext, FU* Templ)
	{
		Bus = BusContext;
		ProgFU(0, { 0,nullptr });
	};
};