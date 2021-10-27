#define _USE_MATH_DEFINES
#include "stdafx.h"
#include "MeanShift.h"
#include <string>
#include <fstream>
#include <set>
#include <algorithm>
#include <cmath>

double  MeanShiftPoint::dist(vector<double> &a, vector<double> &b) // ���������� ���������� ����� ����� �������
{
	if (a.size() != b.size()) return -1; // �� ��������� ����������� ����������� ��� �����
	double D = 0;
	for (vector<double>::iterator ua = a.begin(), ub = b.begin(); ua != a.end(); ua++, ub++)
		D += (*ua - *ub) * (*ua - *ub);
}

void MeanShiftPoint::ProgFU(int MK, LoadPoint Load) // ��������� ����� �������� ������������
{
	switch (MK)
	{
	case 100: // Gen
		// ������ �����, ����������� � ������� ������ ������ �����
		vector<int>eps_t(eps); // ������� ������ �������� ��� ������ ����� �� ��������� ����������� �����
		N.clear();
		for (;;) // ���� �� ���������� ������ ���������� ����������� �����
		{
			MeanShift* MANAGER = (MeanShift*)Manager;
		//	for (vector<MeanShiftPoint>::iterator uFU = (eps_t[0] < IdXY[0] ? (&Manager->VXY[IdXY[0]] - eps_t[0])) : &Manager->VXY[IdXY[0]];
			for (auto uFU = MANAGER->VXY[0].begin() + ((eps_t[0] > Coodinate[0]) ? 0 : Coodinate[0] - eps_t[0]);
				uFU != MANAGER->VXY[0].end() && distance(MANAGER->VXY[0].begin(), uFU) <= Coodinate[0] + eps_t[0]; uFU++)
			{
				if ((*uFU)->ID==ID) continue; // ���������� ������ ��
				int i_dim;
				for (i_dim = 0; i_dim < NDim && \
						(*uFU)->IdXY[i_dim]<=IdXY[i_dim]+eps_t[i_dim] &&\
						(*uFU)->IdXY[i_dim] >= IdXY[i_dim] - eps_t[i_dim]; i_dim++);
				if (i_dim == NDim) // ���� ��������� �� ����� �������
					N.push_back(*uFU); // ������������ ��������� ����������� ����� N
			}

			if (N.size() >= NV)
				break;
			// ��� ���� �������� � ������������ � 2 ���� ���������
			for (auto& i : eps_t)
					i += i;
			N.clear();
			//break; // ��������!!!!
		}
		// ��������� ��������� �����
		multimap<double, MeanShiftPoint*> Distance; // ������ ����������� ������, ������������� �� ���������� �� �����
		multimap<double, MeanShiftPoint*> Angle; // ����� ������ ����������� ������, ������������� �� ����
		for (auto i : N)
			Distance.insert({ dist(this->Coodinate,i->Coodinate),i });// ������ �� �� �����������
//		cout << this->Coodinate[0] << " " << this->Coodinate[1] << endl;
//		for (auto i : Distance)
//			cout << i.first << " " << i.second->Coodinate[0]<<" "<< i.second->Coodinate[1] << endl;
//		cout << "-----\n";

		for (auto &k:Distance)
		{		
			Angle.insert(pair<double, MeanShiftPoint*>
				(atan2(k.second->Coodinate[0] - Coodinate[0],
				k.second->Coodinate[1] - Coodinate[1]),k.second)); // ���������� ���������
			if (Angle.size() < 3)continue;
			auto i = Angle.begin();
			auto st = Angle.begin();
			auto fin = Angle.begin();
			for (; i->second != k.second; i++);
			if (i == Angle.begin()) //���� ����� � ������ ������ �� �����
			{
				fin = (--Angle.end());
				st = i; st++;
			}
			else if (i == --Angle.end()) // ���� ����� � ����� ������ �� �����
			{
				fin = Angle.begin();
				st = i; st--;
			}
			else
			{
				st = fin = i;
				st--;
				fin++;
			}
			double dSt = (abs(i->first - st->first)) <= M_PI ? abs(i->first - st->first):abs(i->first + st->first);
			double dFin = (abs(i->first - fin->first)) <= M_PI ? abs(i->first - fin->first) : abs(i->first + fin->first);
			double dStFin = (abs(st->first - fin->first)) <= M_PI ? abs(st->first - fin->first) : abs(st->first + fin->first);
			
			if (dSt + dFin == dStFin && // ���� ����� ��������� � ������ ���� ����� ����� ��������� �������
				k.first > dist(st->second->Coodinate, fin->second->Coodinate))// ���������� ����� ��������� ������� ������ ���������� �� ������ ����� �� ������� �����
				Angle.erase(i); // ������� ������� ����� �� ������ ����������� �����, �.�. ��� �� �������� ���������� �����
		}
		// ������ � �������� ��-����������� ������ �� ����������� ������� ������
		N.clear();
		for (auto i : Angle)
			N.push_back(i.second);
	}
}

void MeanShift::ProgFU(int MK, LoadPoint Load) // ��������� �� MeanShift
{
	switch (MK)
	{
	case 0: // Reset
		break;
	case 3: // NDimSet ���������� ���������� ��������� �������� ������������
		NDim = Load.ToInt();
		EpsFaze = 0; // ����� ���� ���������� eps
		eps.resize(NDim);
		ProbMaxMin.resize(NDim);
		for (auto& i : ProbMaxMin)
			i.resize(2);
		break;
	case 5: // Start
		//...
		if ((Load.Type >> 1) == Dstring)
			FileRead(Load);
		NetGen();
		break;
	case 8: // NVSet ���������� ��������� ���������� ����������� ����� ��� ������ ���������� ��������� ����� ������ ����
		NV = Load.ToInt();
		break;
	case 15: // PointsGen ��������� ��������� ����� (�������: ���� � ��� ���������� �� ���� � ���������� ������������ �����)
	case 16: // PointsGenStart ��������� ��������� ����� (��������: ������� ����� ���� ����, ������ ������ ���� ����, ���������� �����)
		if (ProbFaze < NDim + NDim)
			ProbMaxMin[ProbFaze / 2][ProbFaze % 2] = Load.ToDouble();
		else
		{
			NProb = Load.ToInt();
			PointsGen(); // ��������� ����� ����
			NetGen(); // ��������� �����
			if (MK == 16)
				Start(); // ������ �������������
			ProbFaze = -1; // ����� ���� �� � ���� ����� ������ ProbFaze++
		}
		ProbFaze++;
		break;
	case 20: // PointsOutMk ������ ����� �������� ������������
	{
		
		for (auto& i : VXY[0])
		{
			MkExec(Load, { CdoubleArray,&i->Coodinate });
		}
		break;
	}
	case 30: //ArcsOutMk ������ ������ ���
	{
		set<pair< MeanShiftPoint*, MeanShiftPoint*> >ArksOut;// ������ ���������
		for (auto& i : VXY[0])
		{
			pair<MeanShiftPoint*, MeanShiftPoint*> p;
			for (auto j : i->N) {
				if (i->ID < j->ID)
				{
					p.first = i; p.second = j;
				}
				else
				{
					p.first = j; p.second = i;
				}
				ArksOut.insert(p);
			}
		}
		
		for (auto &i : ArksOut)
		{
			MkExec(Load, { CdoubleArray, &i.first->Coodinate });
			MkExec(Load, { CdoubleArray, &i.second->Coodinate });
		}
		break;
	}
	case 40: // NVPointErrProgSet ���������� ��������� ������� �� ������� ���������� ���������� ��������� ��� ����������� ����� ��� ����������� ����� � �������
		NVPointErrProg = Load.Point;
		break;
	case 51: // epsSet ���������� ���������� ������������� ����� �� ��� (�� ��������� 20)
		eps[EpsFaze] = Load.ToInt(20)/2;
		EpsFaze = (EpsFaze + 1) % NDim;
		break;
	case 52: // epsAllSet ���������� ���������� ���������� ������������� ����� ��� ���� ���� (�� ��������� 20)
	{	int t = Load.ToInt(20) / 2;
		for (auto& i : eps)
			i = t;
		break;
	}
	default:
		CommonMk(MK, Load);
		break;
	}
}

void MeanShift::Start() // ������ �������������
{
}

void MeanShift::PointsGen()
{
	for (auto& i : VXY) // ������� ������������ ����
	{
		for (auto& j : i)
			delete j;
	}
	VXY.clear();
	VXY.resize(NDim);
	for (int i = 0; i < NProb; i++)
	{
		MeanShiftPoint* t = new MeanShiftPoint;
		t->Coodinate.resize(NDim);
		t->Manager = this;
		t->eps = eps;
		t->NV = NV;
		t->ID = i; // ���������� ������������� ��-�����������
		for (auto& l : t->Coodinate) // ��������� �����
			l = (double) rand() / RAND_MAX * (ProbMaxMin[l][1] - ProbMaxMin[l][0]) + ProbMaxMin[l][0];
		for (auto& k : VXY)
			k.push_back(t); // ������ ���������� �� �������������� �� � ������� ���� ���������
	}
	// �������������� ����� �� ������ �� ���������
	int i = 0;
	for (auto& k : VXY)
	{
		sort(k.begin(), k.end(), [i](MeanShiftPoint* a, MeanShiftPoint* b) {return a->Coodinate[i] < b->Coodinate[i]; });
		i++;
	}
	// ����������� ������ � ������ �� �� �������� � VX,VY
	for (auto& k : VXY) {// ������� ���� �����
		for (auto& uFU : k)
		{
			int i = 0;
			uFU->refXY.push_back(&uFU);
			uFU->IdXY.push_back(i); // ������ ������� �� �� ������� ���������
			i++;
		}
	}

}

void MeanShift::FileRead(LoadPoint Load)
{
/*	ifstream f; // ���� ��� ���������� �������� ������
	string FName;
	ifstream fin;
	f.open(Load.ToStr());
	if (!f) return;
	vector<pair<double, MeanShiftPoint*>> VXt, VYt;
	while (!f.eof())
	{
		double x, y;
		f >> x >> y;
		MeanShiftPoint* MP = new MeanShiftPoint();
		VXt.push_back({ x, MP });
		VYt.push_back({ y, MP });
		MP->epsX = epsX;
		MP->epsY = epsY;
		MP->NV = NV;
		MP->Manager = this;
		MP->Coodinate.push_back(x);
		MP->Coodinate.push_back(y);
		MP->VX = &VX; // ������ �� ������ ������������� ������ �� ���������� X
		MP->VY = &VY; // ������ �� ������ ������������� ������ �� ���������� Y
	}
	// �������������� �������� VXt, VYt
	sort(VXt.begin(), VXt.end());
	sort(VYt.begin(), VYt.end());
	// ������������ �������� VX, VY
	for (auto uk = VXt.begin(); uk != VXt.end(); uk++)
		VX.push_back(uk->second);
	for (auto uk = VYt.begin(); uk != VYt.end(); uk++)
		VY.push_back(uk->second);
*/
}

void  MeanShift::NetGen() // ��������� �����
{
	// ��������������� ��������� �����
	// ����������� ��������� ����������� ����� ��� ���������� ����� (��������� N)
	if (NV > VXY[0].size()) // ���� ���������� ����� � ������� ������,
	{						// ��� ��������� ��� �����������, �� ���������� ����� �����������
		ProgExec(NVPointErrProg); // ����� ����������� ��������� �� ������
		return;
	}
	for (auto FUuk : VXY[0])
	{
		FUuk->ProgFU(100, {0,nullptr});// ������������ ��������� ����������� �����
	}

}
