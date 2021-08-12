#include "stdafx.h"
#include "Bag.h"
#include <fstream>
#include "SchedulerEventser.h"

void BagPoint::ProgFU(int MK, LoadPoint Load)
{
	if (Modeling != nullptr && Modeling->ManualMode && Modeling->scheduler != nullptr && !Modeling->SchedulerFlag)
	{
		Modeling->SchedulerFlag = false;
		Modeling->qmk.push_back({ MK, Load });
		double SendAllTime = SendTime*((Down != nullptr) + (Diagonal != nullptr) + (Next != nullptr));
  		((Scheduler*)(Modeling->scheduler))->Scheduling(this, CalcTime+SendAllTime);
		return;
	}
	bool SchedulerFlag = false;
	if (Modeling != nullptr && Modeling->ManualMode && Modeling->SchedulerFlag)
	{
		Modeling->SchedulerFlag = false;
		SchedulerFlag = true;
	}
	switch (MK)
	{
	case 1: // Calc ��������� ��������
		// ��� ��������� ������ ������, ��� ���� ��� �� p_Diag, �� p_Up
		if ((p_Diag < 0) && (p_Up < 0))
		{
			if (w_i >= w_a)
				p = Load.ToDouble();
			else
				p = 0;
		}
		else // ��������� ������
		{
			if ((w_i > w_a) && (p_Diag >= 0))
			{
				p = max(p_Up, p_Diag + Load.ToDouble());
			}
			else if ((w_i == w_a) && (p_Diag < 0))
			{
				p = max(p_Up, Load.ToDouble());
			}
			else
				p = p_Up;
		}

		if (Down) Down->ProgFU(2, { Cdouble,&p }); // �������� ����
		if (Diagonal) Diagonal->ProgFU(3, { Cdouble,&p }); // �������� �� ���������
		if (Next) Next->ProgFU(1, Load); // �������� ������
		break;
	case 2: // Up ������� �������� ������
		p_Up = Load.ToDouble();
		break;
	case 3: // Diag ������� �������� �� ���������
		p_Diag = Load.ToDouble();
		break;
	}
	if (SchedulerFlag)
		((Scheduler*)Modeling->scheduler)->CoreFree();
}

void Bag::ProgFU(int MK, LoadPoint Load)
{
	if (Modeling != nullptr && Modeling->ManualMode && Modeling->scheduler != nullptr && !Modeling->SchedulerFlag)
	{
		Modeling->SchedulerFlag = false;
		Modeling->qmk.push_back({ MK, Load });
		((Scheduler*)(Modeling->scheduler))->Scheduling(this, SendTime);
		return;
	}
	bool SchedulerFlag = false;
	if (Modeling != nullptr && Modeling->ManualMode && Modeling->SchedulerFlag)
	{
		Modeling->SchedulerFlag = false;
		SchedulerFlag = true;
	}

	switch (MK)
	{
	case 0: // Reset
		for (auto& i : Field)
			i.resize(0);
		Field.resize(0);
		break;
	case 1: // Start
	{ 
		for (auto& i : Field) // ������� ������ ������
			i.resize(0);
		Field.resize(0);
		W.clear(); P.clear();

		if (!Load.Point)
		{ // ��������� ��������� �����
			W.push_back(0); // ������ �������
			P.push_back(0); // ������ �������
			for (int i = 0; i < NItem; i++)
				{W.push_back(rand() % WMaxOfItem+1); P.push_back(rand() % int(PMaxOfItem)+1);}
			for (int k = 0; k <= NItem; k++)
			{
				Field.push_back({ {} });
				for (int i = 0; i < WMax; i++)
					Field.back().push_back({});
			}
		}
		else
		{
			string str = Load.ToStr();
			ifstream in(str);
			if (!in)
				cout << "File error\n";
			in >> WMax;
			Field.push_back({ {} });
			for (int i = 0; i < WMax; i++)
				Field.back().push_back({});
			W.push_back(0); // ������ �������
			P.push_back(0); // ������ �������
			while (!in.eof())
			{
				int w;
				double p;
				in >> w >> p;
				W.push_back(w); P.push_back(p);
				Field.push_back(Field[0]); // ��������� �������������� �����
			}
			in.close();
		}

		// ���������� ������� ����� � ����� �������� (const) ��� ������� �������� �������
		// ����� �� ����������, ����� ��� � ��������� ����
		for (int i = 1; i < Field.size(); i++)
			for (int j = 1; j < Field[0].size(); j++)
			{
				Field[i][j].w_a = W[i];
				Field[i][j].w_i = j + 0.0; // int to double
				Field[i][j].CalcTime = CalcTime;
				Field[i][j].SendTime = SendTime;
				if (Modeling != nullptr)
				{
					Field[i][j].Modeling = new FUModeling();
					Field[i][j].Modeling->scheduler = (void*)Modeling->scheduler;
					Field[i][j].Modeling->ManualMode = true;
				}
			}


		// ������
		for (int i = 1; i < Field.size(); i++)
			for (int j = 1; j < Field[0].size()-1; j++)
			{
				Field[i][j].Next = &Field[i][j+1];
				if (i < Field.size() - 1) //���� �� ��������� ������
				{
					Field[i][j].Down = &Field[i+1][j];

					if (j == Field[0].size() - 2) // ����� ���������� ������ Down ��� ��������� ���������� �������
					{
						Field[i][j+1].Down = &Field[i + 1][j+1];
					}

					if (j + W[i+1] <= WMax) // ������������ ������
						Field[i][j].Diagonal = &Field[i+1][j+W[i+1]];
				}
			}
		// ������ ����������
		for (int i = 1; i < P.size(); i++)
			Field[i][1].ProgFU(1, { Cdouble, &P[i] }); // ������ ���������� �� ������ �����
		break;
	}
	case 10: // RezOut ������ ���������
	case 11: // RezOutMk ������ �� � �����������
	{
		double Rez = 0;
		for (auto i : Field[Field.size() - 1])
			if (i.p > 0)
				Rez = i.p;
		if (MK == 10)
			Load.Write(Rez);
		else
			MkExec(Load, { Cdouble,&Rez });
	break;
	}
	case 90: //WMaxSet ���������� ������������ ����� �������
		WMax = Load.ToInt();
		break;
	case 91: // WMaxOfItem ���������� ������������ ������ ����� ����
		WMaxOfItem = Load.ToInt();
		break;
	case 92: // PMaxOfItem ���������� ������������ ������ ����� ����
		PMaxOfItem = Load.ToDouble();
		break;
	case 93: //NItemSet ���������� ���������� ��������� ��� ������� � ������ ����������
		NItem = Load.ToInt();
		break;
	case 94: //NItemAdd
		NItem += Load.ToInt();
		break;
	case 95: //WMaxAdd
		WMax += Load.ToInt();
		break;

	case 100: // CalcTimeSet ���������� ����� ���������� ����������
		CalcTime = Load.ToDouble();
		break;
	case 101: // SendTimeSet ���������� ����� ��������� ������
		SendTime = Load.ToDouble();
		break;
	default:
		CommonMk(MK, Load);
		break;
	}
	if (SchedulerFlag)
		((Scheduler*)Modeling->scheduler)->CoreFree();
}