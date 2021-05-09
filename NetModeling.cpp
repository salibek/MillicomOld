#include "NetModeling.h"
#include "SchedulerEventser.h"

// ������ �������� ������:
void TemperatEx::ProgFU(int MK, LoadPoint Load)
{
	if (Modeling!=nullptr && Modeling->ManualMode && Modeling->scheduler != nullptr && !Modeling->SchedulerFlag)
	{
		Modeling->SchedulerFlag = false;
		Modeling->qmk.push_back({ MK, Load });
		if (Load.Type % 2 == 1) Load.Point=Load.VarCopy(); // ����������� ���������
		if(Load.Point!=nullptr)
			((Scheduler*)(Modeling->scheduler))->Scheduling(this, ReadTime);
		else
			((Scheduler*)(Modeling->scheduler))->Scheduling(this, CalcTime);
		return;
	}
	bool SchedulerFlag = false;
	if (Modeling != nullptr && Modeling->ManualMode && Modeling->SchedulerFlag)
	{
		Modeling->SchedulerFlag = false;
		SchedulerFlag = true;
	}
	int it = MK >> 2; // ����� ��������
	MK &= 3;


	if (T.size() >= it) // ���� ������ �� ����� ��������� � ����� ������� ��� �� ������������� ������ �������� 
	{
		T.resize(it + 1);
		T_Neighbours.resize(it + 1);
		T_Neighbours[it] = { 0,0,0,0 };
	}

	if(Load.Point!=nullptr)
		T_Neighbours[it][MK] = Load.ToDouble();
	else
	{
//		cout << Y << "," << X << " " << it << "|" << T_Neighbours[it-1][0] << " " << T_Neighbours[it-1][1] << " " << T_Neighbours[it-1][2] << " " << T_Neighbours[it-1][3] << " " << endl;
		if (FConst)
			T[it] = T[0];
		else // ����� ���������� ����������� � �������� ������ �������
		{
			T[it] = T[it - 1] + tay * a * (T_Neighbours[it - 1][0] + T_Neighbours[it - 1][1] + T_Neighbours[it - 1][2] + T_Neighbours[it - 1][3] - 4 * T[it - 1]) / h2;
		}
		//			cout << X << " " << Y << " " << T[it] << " " << T_Neighbours[it - 1][2] <<" "<< T_Neighbours[it - 1][3]<< endl;
		if (Neighbours[0] == nullptr)T_Neighbours[it][0] = T[it];
		if (Neighbours[1] == nullptr)T_Neighbours[it][1] = T[it];
		if (Neighbours[2] == nullptr)T_Neighbours[it][2] = T[it];
		if (Neighbours[3] == nullptr)T_Neighbours[it][3] = T[it];
		// �������� ���������� �������
		if(Neighbours[0] != nullptr) Neighbours[0]->ProgFU((it << 2)+ 2, { Cdouble,&T[it] });
		if(Neighbours[1] != nullptr) Neighbours[1]->ProgFU((it << 2)+ 3, { Cdouble,&T[it] });
		if(Neighbours[2] != nullptr) Neighbours[2]->ProgFU((it << 2) + 0, { Cdouble,&T[it] });
		if(Neighbours[3] != nullptr) Neighbours[3]->ProgFU((it << 2) + 1, { Cdouble,&T[it] });
		if(Neighbours[2] == nullptr && Neighbours[1]!=nullptr)
			Neighbours[1]->ProgFU(it << 2, { 0,nullptr });
		if (Neighbours[0] != nullptr)
			Neighbours[0]->ProgFU(it << 2, { 0,nullptr });
		if(FiringProg!=nullptr)
			ProgExec(FiringProg);
	}
	if(SchedulerFlag)
		((Scheduler*)Modeling->scheduler)->CoreFree();
}
void NetManager::ProgFU(int MK, LoadPoint Load)
{
	switch (MK)
	{
	case 0: //Reset
		ConstTCounter = 0; // ������� ��� ConstTSet
		X = 0; Y = 0;
		h = 0; tay = 0;
		a = 1; // ����������� � ���������
		Ntay = 0; NtayCounter = 0; // ���������� ������ �������������
		ManageTime = 0;
		break;
	case 1: // NtaySet ���������� ���������� �������� �� �������
		Ntay = Load.ToInt();
		break;
	case 2: // XSet ���������� ���������� ����� ����� �� X
		X = Load.ToInt();
		break;
	case 3: // XAdd ��������� ����������� X �� Load ������ (�� ���������� �� 1)
		X+= Load.ToInt();
		if (Load.ToInt() == 0) X++;
		break;
	case 4: // XOutMk
		MkExec(Load, { Cint,&X });
		break;
	case 5: // YSet ���������� ���������� ����� ����� �� Y
		Y = Load.ToInt();
		break;
	case 6: // YAdd ��������� ����������� Y �� Load ������ (�� ���������� �� 1)
		Y += Load.ToInt();
		if (Load.ToInt() == 0) Y++;
		break;
	case 7: // YOutMk
		MkExec(Load, { Cint,&Y });
		break;
	case 9: // ASet ���������� ����������� a � ���������
		a = Load.ToDouble();
		break;
	case 10: // hSet ���������� ���������� ����� �������
		h= Load.ToDouble();
		break;
	case 12: // taySet ���������� ��������� ��� �������������
		tay = Load.ToDouble();
		break;
	case 13: //	ManageTimeSet ���������� ����� ������ ���������
		ManageTime = Load.ToDouble();
		break;
	case 30: //NetGen ��������� �������������� �����
		if(Items.size()!=0)
			for (auto&& i : Items) // ������� ������� ����
				for (auto&& j : i)
				{
					j->Neighbours.clear();
					j->T_Neighbours.clear();
					delete j;
				}
		Items.resize(Y);
		for (int i = 0; i < Y; i++)
		{
			Items[i].resize(X);

			for (int j = 0; j < X; j++)
			{
				Items[i][j] = new TemperatEx();
				Items[i][j]->Neighbours.resize(4);
				Items[i][j]->T.push_back(0); // ��������� ����������� �����
				Items[i][j]->T_Neighbours.push_back({ 0,0,0,0 });
				Items[i][j]->h2 = h * h;
				Items[i][j]->tay = tay;
				Items[i][j]->a = a;
				Items[i][j]->Y = i;
				Items[i][j]->X = j;
				Items[i][j]->ReadTime = ReadTime;
				Items[i][j]->CalcTime = CalcTime;
				Items[i][j]->Bus = Bus;
				if(NetScheduler!=nullptr)
				 {
					Items[i][j]->Modeling = new FUModeling();
					Items[i][j]->Modeling->scheduler = (void*)NetScheduler;
					if (NetScheduler != nullptr)Items[i][j]->Modeling->ManualMode = true;
				}
			}
		}
		for (int i = 0; i < Y; i++) // ������ �� �������
		{			
			for (int j = 0; j < X; j++)
			{
				Items[i][j]->Neighbours[0] = (TemperatEx*)((j == X - 1) ? nullptr : Items[i][j + 1]);
				Items[i][j]->Neighbours[1] = (TemperatEx*)((i == Y-1) ?   nullptr : Items[i+1][j]);
				Items[i][j]->Neighbours[2] = (TemperatEx*)((j == 0) ?     nullptr : Items[i][j - 1]);
				Items[i][j]->Neighbours[3] = (TemperatEx*)((i == 0) ?     nullptr : Items[i-1][j]);
			}
		}
		break;
	case 35: //Start ������ ��������
	{
		bool SchedulerFlag = false;
		if (Modeling != nullptr && Modeling->ManualMode && Modeling->scheduler != nullptr && !Modeling->SchedulerFlag)
		{
			Modeling->SchedulerFlag = false;
			SchedulerFlag = true;
			Modeling->qmk.push_back({ MK, Load });
			if (Load.Type % 2 == 1) Load.Point = Load.VarCopy();
			((Scheduler*)(Modeling->scheduler))->Scheduling(this, ManageTime);
			return;
		}
		if (Modeling != nullptr && Modeling->ManualMode && Modeling->SchedulerFlag)
		{
			Modeling->SchedulerFlag = false;
			SchedulerFlag = true;
		}

		if (Load.Point != nullptr && Load.Type >> 1 == Dint) {
			Ntay = Load.ToInt(); NtayCounter = 0;
			Load = { 0,nullptr };
		}
		do
		{
			NtayCounter++; // ���������� ������ �������������
			if(NtayCounter<=Ntay)
				Items[0][0]->ProgFU(NtayCounter << 2, { 0,nullptr });
			if (SchedulerFlag)
				((Scheduler*)Modeling->scheduler)->CoreFree();
			if (Load.Point == nullptr || NtayCounter>=Ntay)
				break;
			else
			{
				ProgFU(MK, { 0, nullptr});
			}
		}
		while(true);
		break;
	}
	case 40: // ConstTSet ���������� ����������� ����������� � �����
		switch (ConstTCounter)
		{
		case 0:
			XC = Load.ToDouble();
			break;
		case 1:
			YC = Load.ToDouble();
			break;
		case 2:
			Items[YC][XC]->T[0] = Load.ToDouble();
			if (Items[YC][XC]->Neighbours[0] != nullptr) Items[YC][XC]->Neighbours[0]->T_Neighbours[0][2] = Items[YC][XC]->T[0];
			if (Items[YC][XC]->Neighbours[1] != nullptr) Items[YC][XC]->Neighbours[1]->T_Neighbours[0][3] = Items[YC][XC]->T[0];
			if (Items[YC][XC]->Neighbours[2] != nullptr) Items[YC][XC]->Neighbours[2]->T_Neighbours[0][0] = Items[YC][XC]->T[0];
			if (Items[YC][XC]->Neighbours[3] != nullptr) Items[YC][XC]->Neighbours[3]->T_Neighbours[0][1] = Items[YC][XC]->T[0];
			Items[YC][XC]->FConst = true;
			break;
		}
		ConstTCounter = (ConstTCounter + 1) % 3;
		break;
	case 43: // FiringProgSet ���������� ���������, ���������� �� ��������� �������
		switch (ConstTCounter)
		{
		case 0:
			XC = Load.ToDouble();
			break;
		case 1:
			YC = Load.ToDouble();
			break;
		case 2:
			Items[YC][XC]->FiringProg = Load.Point;
			break;
		}
		ConstTCounter = (ConstTCounter + 1) % 3;
		break;
	case 50: // RezOutCons
		for (int k = 0; k <= Ntay; k++)
		{
			if (k>=Items[0][0]->T.size()) break;
			for (int i = 0; i < Y; i++)
			{
				for (int j = 0; j < X; j++)
					cout << Items[i][j]->T[k]<<"\t";
				cout << endl;
			}
			cout << endl<<endl;
		}
		break;
	case 60: // ReadTimeSet
		ReadTime = Load.ToDouble();
		break;
	case 61: // CalcTimeSet
		CalcTime = Load.ToDouble();
		break;
	case 65: //NetSchedulerSet
		NetScheduler = (FU*)Load.Point;
		break;
	default:
		CommonMk(MK, Load);
		break;
	}
}