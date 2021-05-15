#include "stdafx.h"
#include "SchedulerEventser.h"

void Eventser::Eventsing(FU* Context, double tay) // ������������ ������� (tay - ����� �������� �������)
{
	if (Events.size() == 0)
	{
		Events.insert(pair<double, FU*>(CurrentTime+tay, Context));
		if (work && !start)// ProgFU(1, { 0,nullptr });
			start = true;
			while (Events.size()!=0 && work) {
				CurrentTime = Events.begin()->first;
				Events.begin()->second->Scheduling();
				Events.erase(Events.begin());
			}
			ProgExec(FinProg);
			EventCount++;
	}
	else
	{
		Events.insert(pair<double, FU*>(Events.begin()->first+tay, Context));
	}
}

void Eventser::ProgFU(int MK, LoadPoint Load)
{
	switch (MK)
	{
	case 0: // Reset
		Events.clear();
		work = true;
		start = false;
		CurrentTime = 0;
		FinProg = nullptr;
		break;
	case 1: //Start ������ �������������
		work = true;
		start = true;
		Events.clear();
		while (Events.size()!=0 && work) {
			CurrentTime = Events.begin()->first;
			Events.begin()->second->Scheduling();
			if (Events.size() != 0) Events.erase(Events.begin());
		}
		ProgExec(FinProg);
		break;
	case 5: // WorkSet ���������� ���� �������� ������
		work = Load.ToBool();
		break;
	case 45: //TimeSet ���������� ������� ��������� �����
		CurrentTime = Load.ToDouble();
		break;
	case 50: // TimeOut ������ ������� ��������� �����
		if(Load.Type==Tdouble)
		break;
	case 51: // TimeOutMk ������ �� � ������� ��������� ��������
	case 52: // TimeOutRefMk ������ �� �� ������� �� ���������� �������� ���������� �������
		if (MK == 51)
			MkExec(Load, { Cdouble,&CurrentTime });
		else
			MkExec(Load, { Tdouble,&CurrentTime });
		break;
	case 55: // EventCountOut
		Load.Write(EventCount);
		break;
	case 56: // EventCountOutMk
		MkExec(Load, { Cint, &EventCount });
		break;
	default:
		CommonMk(MK, Load);
		break;
	}
}

void Scheduler::CoreFree() // ���������� ����
{
	int MkQueuePrev = Queue.size();
	if (Queue.size() == 0)
		CoreCount--;
	else
	{
		FU* t = Queue.back();
		MkQueuePrev--;
		double tMK = MkTimeQueue.back();
		Queue.pop_back(); MkTimeQueue.pop_back();
		((Eventser*)eventser)->Eventsing(t, tMK + SchedulingTime);
	}
	if (CurrentTime != nullptr)
	{
		ParallelFactor += CoreCountPrev * (*CurrentTime - PrevTime);
		AverageMkQueue+= MkQueuePrev * (*CurrentTime - PrevTime);
		PrevTime = *CurrentTime;
		CoreCountPrev = CoreCount;
	}
	ProgExec(SchedulingProg);
}

void Scheduler::Scheduling(FU* Context, double DTime, bool CoreContinue)
{
	if (CoreContinue)
		((Eventser*)eventser)->Eventsing(Context, DTime);
	else
		if (CoreCount < NCores)
		{
			CoreCount++;
			((Eventser*)eventser)->Eventsing(Context, DTime + SchedulingTime);
		}
		else
		{
			Queue.push_back(Context);
			MkTimeQueue.push_back(DTime);
			MkQueuePrev++;
			if (Queue.size() > MaxMkQueue)MaxMkQueue = Queue.size();
		}
	ProgExec(SchedulingProg);
}

void Scheduler::ProgFU(int MK, LoadPoint Load)
{
	switch (MK)
	{
	case 0: // Reset
		eventser = nullptr;
		SchedulingTime = 0; RunTime = 0;
		CoreCountPrev = 0;
		MkQueuePrev = 0;
		CurrentTime = nullptr;
		NCores = 1; CoreCount = 0;
		MaxMkQueue = 0, AverageMkQueue = 0;
		PrevTime = 0; PrevCoreCount = 0;
		ParallelFactor = 0;
		SchedulingProg = nullptr;
		Queue.clear();
		break;
	case 1: // EventserSet
		eventser = (FU*)Load.Point;
		break;
	case 2: // Clear �������� ��������� �������������
		CoreCountPrev = 0;
		ParallelFactor = 0;
		SchedulingTime = 0; RunTime = 0;
		MkQueuePrev = 0;
		if(CurrentTime != nullptr)
			*CurrentTime = 0;
		CoreCount = 0;
		MaxMkQueue = 0, AverageMkQueue = 0;
		PrevTime = 0; PrevCoreCount = 0;
		Queue.clear();
		break;
	case 5: //SchedulingTimeSet
		SchedulingTime = Load.ToDouble();
		break;
	case 8: // NCoresSet
		NCores = Load.ToInt();
		break;
	case 10: // TimeOut
		Load.Write(*CurrentTime);
		break;
	case 11: // TimeOutMk
		MkExec(Load, { Cdouble, CurrentTime });
		break;
	case 15: // SchedulingProgSet ���������� ������ �� ���������, ����������� ��� ������������ ����������
		SchedulingProg = Load.Point;
		break;
	case 40: // CurrTimeRefSet ���������� ������ �� ���������� � ������� ��������� �������� 
		if(Load.Type==Tdouble)
			CurrentTime =(double*) Load.Point;
		break;
	case 50: // CoreCountOut ������ ����� ������� ����
		Load.Write(CoreCount);
		break;
	case 51: // CoreCountOutMk ������ �� � ������ ������� ����
		MkExec(Load, { Cint,&CoreCount });
		break;
	case 55: // MkQueueOut ������ ���������� �� � ������� �� ����������
		Load.Write(int(Queue.size()));
		break;
	case 56: // MkQueueOutMk ������ �� � ����������� �� � ������� �� ����������
	{
		int t = Queue.size();
		MkExec(Load, { Cint,&t });
		break;
	}
	case 60: // MkCountOut ������ ���������� �� �� ���������� � ��������
		Load.Write(int(Queue.size()) + CoreCount);
		break;
	case 61: // MkCountOutMk ������ �� � ����������� �� �� ���������� � ��������
	{
		int t = Queue.size() + CoreCount;
		MkExec(Load, { Cint,&t });
		break;
	}

	case 65: // ParallelFactorOut ������ ����������� ������������
		Load.Write(ParallelFactor / *CurrentTime);
		break;
	case 66: //  ParallelFactorOutMk ������ �� � ������������� ������������
//	if(Modeling!=nullptr)
	{
		double t;
		if (*CurrentTime > 0)
			t = ParallelFactor / *CurrentTime;
		else
			t = 0;
		MkExec(Load, { Cdouble,&t });
		break;
	}
	case 70: // AverageMkQueueOut ������ ������� ����� �������
//		if (Modeling != nullptr)
			Load.Write(AverageMkQueue);
		break;
	case 71: //  AverageMkQueueOutMk ������ �� �� ������� ������ �������
//		if (Modeling != nullptr)
		{
			double t;
		if (*CurrentTime > 0)
			t = AverageMkQueue / *CurrentTime;
		else
			t = 0;
		MkExec(Load, { Cdouble,&t });
		break;
	}
	case 75: // MaxMkQueueOut ������ ������������ ����� �������
		if (Modeling != nullptr)
			Load.Write(ParallelFactor / *CurrentTime);
		break;
	case 76: //  MaxMkQueueOutMk ������ �� � ������������ ������ �������
	{
//		if (Modeling != nullptr)
		{
			int t = MaxMkQueue;
			MkExec(Load, { Cint,&t });
			break;
		}
	}

	default:
		CommonMk(MK, Load);
		break;
	}
}