#include "stdafx.h"
#include "Neuro.h"

void Neuro::ProgFU(int MK, LoadPoint Load)
{
	switch (MK)
	{
	case 0:// Reset
		W.clear(); X.clear();  XF.clear();
		WInd = 1; XInd = 1; // �������  

		break;
	case 1: // SizeSet ���������� ���������� ������ �������
		if(Load.Point==nullptr)
		{
			W.clear(); X.clear(); XF.clear();
		}
		else if (Load.Type >> 1 == Dint && *(int*)Load.Point >= 0)
		{
			W.resize(*(int*)Load.Point);
			X.resize(*(int*)Load.Point);
			XF.resize(*(int*)Load.Point);
			for (auto&& i : XF)
				i = false;
		}
		Counter = S = 0;
		break;
	case 2: // EpsSet ���������� ����������� ����������
		if (Load.Point == nullptr)
			eps = 0;
		else if (Load.Type>>1 == Ddouble)
			eps = *(double*)Load.Point;
		break;
	case 3: // FTypeSet ��������� ��� �������� �������
		if (Load.Point == 0)
			FType = 0;
		else
			if (Load.Type >> 1 == Dint)
				FType = *(int*)Load.Point;
		break;
	case 5: // OutMkAdd �������� �� ��� ��������� �������
		if(Load.Type >> 1 == Dint)
			MK_Out.push_back(*(int*)Load.Point);
		break;
	case 6: // OutMkClear �������� ����� �� ��� ��������� �������
		MK_Out.clear();
		break;

	case 7: // FArgAdd �������� �������� �������� �������
		if (Load.Type >> 1 == Ddouble || Load.Type >> 1 == Dfloat || Load.Type >> 1 == Dint)
			F_Arg.push_back(Load.ToDouble());
		break;
	case 8: // FArgClear �������� ����� ���������� �������� �������
			F_Arg.clear();
		break;
	case 10: // YOut ������ �������� ������
		if (Load.Type >> 1 == Ddouble)
			*(double*)(Load.Point) = Y;
		break;
	case 11: // YOutMk ������ �� � �������� ��������
		if(Load.Type >> 1 == Dint)
			MkExec(*(int*)Load.Point, { Cdouble,&Y });
		break;
	case 12:// DeltaSet ���������� ����������� ����������
		if (Load.Type >> 1 == Ddouble)
			delta = *(double*)Load.Point;
		break;
	case 14: //WIndSet ���������� ������ ����
		if (Load.Type >> 1 == Dint)
			WInd = Load.ToInt();
		break;
	case 15: //WIndStepSet ���������� ������ ����
		if (Load.Type >> 1 == Dint)
			WIndStep = Load.ToInt();
		break;
	case 17: //XIndStepSet ���������� ������ �������� �������
		if (Load.Type >> 1 == Dint)
			XInd = Load.ToInt();
		break;
	case 18: //XIndStepSet ���������� ������ �������� �������
		if (Load.Type >> 1 == Dint)
			XIndStep = Load.ToInt();
		break;
	case 19:// WSet
	case 20:// W1Set
	case 21:// W2Set
	case 22:// W3Set
	case 23:// W4Set
	case 24:// W5Set
	case 25:// W6Set
	case 26:// W7Set
	case 27:// W8Set
		if (W.size() > 0 && (Load.Type >> 1 == Ddouble||Load.Type >> 1 == Dfloat))
		{
			int i = 0;
			if (MK - 20 >= -1 && MK - 20 < W.size())
				i = MK - 20;
			else
				if (MK == 19){
					i = WInd; WInd += WIndStep;
				}
			W[i] = Load.ToDouble();
		}
		break;

	case 49:// XSet
	case 50:// X1Set
	case 51:// X2Set
	case 52:// X3Set
	case 53:// X4Set
	case 54:// X5Set
	case 55:// X6Set
	case 56:// X7Set
	case 57:// X8Set
		if (X.size() > 0 && (Load.Type >> 1 == Ddouble || Load.Type >> 1 == Dfloat || Load.Type >> 1 == Dint))
		{
			int i = 0;
			if (MK - 50 >= -1 && MK - 50 < X.size())
			{
				if (MK == 49)
				{
					i = XInd; XInd += XIndStep;
				}
				else
					i = MK - 50;
				if (XF[i])
					S -= W[i] * X[i];
				X[i] = Load.ToDouble();
				// �������� �������� ������� ������
				// ������ ������������
				S += W[i] * X[i];
				int k;
				Y = Activation[FType](S, F_Arg); // ����� ������� ���������
				if (Counter < X.size() - 1)
					Counter++;
				else if (Counter == X.size() && delta >= abs(Z - Y) || XF[i] == false)  // �������� ������ � �������� ���������� ������ ������� ������������
				{
					XF[i] = true;
					Z = Y;
					for (auto j : MK_Out)
						MkExec(j, { Cdouble,&Y });
				}
			}
			break;
		}
		break;
	default:
		CommonMk(MK, Load);
		break;
	}
}

// ������� ��������� �������
double LinF(double S, vector<double> Args) // ���������� �����������
{
	if (Args.size() < 1) return 0;
	else
		return S * Args[0];
};

double Porog(double S, vector<double> Args) // 1. x, ��� ������� ������� �� ����� ������� �������, 2. �������� �� ��������, 3. ����� ��������
{
	if (Args.size() < 3) return 0;
	else
		if (S < Args[0])
			return Args[1];
		else
			return Args[2];
};
