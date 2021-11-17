#define _USE_MATH_DEFINES
#include "stdafx.h"
#include "MeanShift.h"
#include <string>
#include <fstream>NExUFCall
#include <algorithm>
#include <cmath>

int MeanShiftCluster::MassCenter(vector<double>&CenterNew, MeanShiftPoint* Point, set<MeanShiftPoint*> &Pass) // ���������� ������ ���� ������� (������������ ���������� �����)
// �� ����� ������ �� �� ��� ���������� � ������ ���������� ������
// ����������� ���������� ���������� �������������� ������
{
	if (Pass.count(Point)) return 0; // ���� ����� ��� ���� ��������
	if (Point->dist(Point->Coodinate, Center) > R*R)return 0;
	Pass.insert(Point); // �������� ������� � ������ ������������
	for (int i = 0; i < NDim; i++)
		CenterNew[i]+= Point->Coodinate[i];
	int NS = 1;
	for (auto &i : Point->N)
		NS += MassCenter(CenterNew,i,Pass);
	return NS;
}

void MeanShiftCluster::Migration() // ����� ������������ �����
{
	//	vector<double> CenterOld; // ������ ����� �������
	vector<double> CenterNew=Center;
	//NExUFCall = 0;
	do
	{
		Center = CenterNew;
		MigrationHistory.push_back(Center);//�������� ������� �����������
		MoveToPoint(CenterFU);
		// ���������� ������ ���� ������� (��������)
		set<MeanShiftPoint*> Pass;
		NPoints = MassCenter(CenterNew, CenterFU, Pass);
		if (!NPoints) return;
		NExUFCall+= NPoints; // ������������ ���������� ��������� ��
		for (auto& i : CenterNew)
			i /= NPoints;
	} while (CenterFU->dist(CenterNew, Center)>Eps);
	Mass = NPoints; // ��������
}

void MeanShiftCluster::MoveToPoint(MeanShiftPoint* CenterStart) // ����� ��������� ������� � ��������� �������
{
	CenterFU=CenterStart;
	MeanShiftPoint* MinDistFU = CenterFU;
	double MinDist = CenterFU->dist(Center, CenterFU->Coodinate);
	while(1)
	{
		for(auto &i: CenterFU->N)
			if (i->dist(Center, i->Coodinate) < MinDist)
			{
				MinDistFU = i;
				MinDist = i->dist(Center, i->Coodinate);
			}
		if (MinDist == CenterFU->dist(Center, CenterFU->Coodinate))
			break;
		CenterFU = MinDistFU;
	}	
}

void MeanShiftCluster::ProgFU(int MK, LoadPoint Load) // ������� ��� ������ ��������� ������������
{
	switch (MK)
	{
	case 0: // Reset
		break;
	case 1: // NDimSet
		NDim = Load.ToInt();
		Center.resize(NDim);
		break;
	case 5: //CenterSet ���������� ���������� ������ �������
		Center[CenterPhase] = Load.ToDouble();
		CenterPhase = (CenterPhase + 1) % NDim;
		break;
	case 10: //RSet ���������� ������ �������
		R = Load.ToDouble();
		break;
	case 20: // ToStartPoint ����������� ������ � ��������� ������� (� �������� ��������� �� ��-����������� �������������� �����)
		MoveToPoint((MeanShiftPoint*)Load.Point); // ����� ������ ��������� ������� � ��������� �������
		break;
	case 30:// Migration ����������� ������� ��� ������ ������������ �����
		Migration();
		break;
	case 50: // CenterOut ������ ���������� ������ �������
		Load.Write(Center);
		break;
	case 51: // CenterOutMk ������ �� � ������������ ������ �������
		MkExec(Load, { CdoubleArray,&Center });
		break;
	case 60: // HistoryOut ������ ������� ����������� �������
	//	Load.Write(MigrationHistory);
		break;
	case 61: // HistoryOutMk ������ �� � �������� ����������� �������
		MkExec(Load, {CintArray2,&MigrationHistory});
		break;
	}
}

double  MeanShiftPoint::dist(vector<double> &a, vector<double> &b) // ���������� ���������� ����� ����� �������
{
	if (a.size() != b.size()) 
		return -1; // �� ��������� ����������� ����������� ��� �����
	double D = 0;
	for (vector<double>::iterator ua = a.begin(), ub = b.begin(); ua != a.end(); ua++, ub++)
		D += (*ua - *ub) * (*ua - *ub);
	return D;
}

void MeanShiftPoint::ProgFU(int MK, LoadPoint Load) // ��������� ����� �������� ������������
{
	switch (MK)
	{
	case 100: // Gen
	{
		// ������ �����, ����������� � ������� ������ ������ �����
		vector<int>eps_t(eps); // ������� ������ �������� ��� ������ ����� �� ��������� ����������� �����
		N.clear();
		for (;;) // ���� �� ���������� ������ ���������� ����������� �����
		{
			MeanShift* MANAGER = (MeanShift*)Manager;
			for (auto uFU = MANAGER->VXY[0].begin() + ((eps_t[0] > IdXY[0]) ? 0 : IdXY[0] - eps_t[0]);
				uFU != MANAGER->VXY[0].end() && distance(MANAGER->VXY[0].begin(), uFU) <= IdXY[0] + eps_t[0]; uFU++)
			{
				if ((*uFU)->ID == ID) 
					continue; // ���������� ������ ��
				int i_dim;
				for (i_dim = 1; i_dim < NDim &&
					(*uFU)->IdXY[i_dim] <= IdXY[i_dim] + eps_t[i_dim] &&
					(*uFU)->IdXY[i_dim] >= IdXY[i_dim] - eps_t[i_dim]; i_dim++);
				if (i_dim == NDim) // ���� ��������� �� ����� �������
					N.insert(*uFU); // ������������ ��������� ����������� ����� N
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
		for (auto& i : N)
			Distance.insert({ dist(this->Coodinate,i->Coodinate),i });// ������ �� �� �����������

		for (auto& k : Distance)
		{
			Angle.insert(pair<double, MeanShiftPoint*>
				(atan2(k.second->Coodinate[0] - Coodinate[0],
					k.second->Coodinate[1] - Coodinate[1]), k.second)); // ���������� ���������
			if (Angle.size() < 3)continue;
			auto i = Angle.begin();
			auto st = Angle.begin();
			auto fin = Angle.begin();
			for (; i->second != k.second; i++);
			if (i == Angle.begin()) //���� ����� � ������ ������ �� �����
			{
				fin = (--Angle.end());
				st = ++Angle.begin();
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
			double dSt = (abs(i->first - st->first)) <= M_PI ? abs(i->first - st->first) : abs(i->first + st->first);
			double dFin = (abs(i->first - fin->first)) <= M_PI ? abs(i->first - fin->first) : abs(i->first + fin->first);
			double dStFin = (abs(st->first - fin->first)) <= M_PI ? abs(st->first - fin->first) : abs(st->first + fin->first);

			//			if (dSt + dFin != dStFin)
			//				cout << i->first << " " << st->first << " " << fin->first << endl;

			if (dSt + dFin == dStFin && // ���� ����� ��������� � ������ ���� ����� ����� ��������� �������
				k.first > dist(st->second->Coodinate, fin->second->Coodinate))// ���������� ����� ��������� ������� ������ ���������� �� ������ ����� �� ������� �����
			{
				Angle.erase(i); // ������� ������� ����� �� ������ ����������� �����, �.�. ��� �� �������� ���������� �����
//				cout << k.first << " " << dist(st->second->Coodinate, fin->second->Coodinate) << endl;
			}
			else
			{
				//		cout << i->first << " " << st->first << " " << fin->first << endl;
					//	cout<< k.first<<" " <<dist(st->second->Coodinate, fin->second->Coodinate) << endl;
			}

		}
		// ������ � �������� ��-����������� ������ �� ����������� ������� ������
		N.clear();
		//		cout << Angle.size() << endl;
		//		cout<<this->Coodinate[0]<<" " << this->Coodinate[1] << endl;
		for (auto i : Angle)
		{
			N.insert(i.second);
			//			cout << i.second->Coodinate[0]<<" " << i.second->Coodinate[1]<<endl;
		}
		break;
	}
	case 101: // Addition ���������� ������ �������� � �������
		for (auto i : N)
			i->N.insert(this);
		break;
/*
	case 102: // ArcsCorrect ������������� �������������� �����
	{	
		set <MeanShiftPoint*> ToDel; // ��������� ����� ��� ��������
		do
		{
		for (auto i : ToDel)
			N.erase(i);
		ToDel.clear();
		for(auto &k: N)
			for (auto &i : k->N)
				for (auto &j : k->N)
					if (i!=j && i->N.count(this) && j->N.count(this) && k!=this &&
						k->dist(this->Coodinate,k->Coodinate)>k->dist(i->Coodinate,j->Coodinate))
						ToDel.insert(k);
		}
		while (ToDel.size()!=0);
		break;
	}
	*/
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
		//NetGen();
		for (auto& R : Clusters) // ����� �������� �������� ��������
			R.Migration();
		break;
	case 8: // NVSet ���������� ��������� ���������� ����������� ����� ��� ������ ���������� ��������� ����� ������ ����
		NV = Load.ToInt();
		break;
	case 15: // PointsGen ��������� ��������� ����� (�������: ���� � ��� ���������� �� ���� � ���������� ������������ �����)
	case 16: // PointsGenStart ��������� ��������� ����� (��������: ������� ����� ���� ����, ������ ������ ���� ����, ���������� �����)
		if (ProbPhase < NDim + NDim)
			ProbMaxMin[ProbPhase / 2][ProbPhase % 2] = Load.ToDouble();
		else
		{
			NProb = Load.ToInt();
			PointsGen(); // ��������� ����� ����
			NetGen(); // ��������� �����
			if (MK == 16)
				Start(); // ������ �������������
			ProbPhase = -1; // ����� ���� �� � ���� ����� ������ ProbPhase++
		}
		ProbPhase++;
		break;
	case 20: // ClusterSet ������� � ���������� ��������� ������� ��� ������
		if (!ClusterPhase)
		{
			Clusters.push_back({});
			Clusters.back().NDim = NDim;
			Clusters.back().Manager = this;
			Clusters.back().ID = Clusters.size() - 1; // �������� ������������� ��-�������
			Clusters.back().Center.push_back(Load.ToDouble());
			Clusters.back().Eps = ClusterEps;
		}
		else if (ClusterPhase == NDim)
		{
			Clusters.back().R = Load.ToDouble();
			Clusters.back().MoveToPoint(VXY[0][0]);
		}
		else
			Clusters.back().Center.push_back(Load.ToDouble());
		ClusterPhase = (ClusterPhase + 1) % (NDim+1);
		break;
	case 21: //ClustersReset �������� ������ ��������
		Clusters.clear();
		break;
	case 23: // NRigionOut ������ ���������� ��������
		Load.Write(Clusters.size());
		break;
	case 24: // NRigionOutMk ������ �� � ����������� ��������
	{
		int t = Clusters.size();
		MkExec(Load, { Cint,&t });
		break;
	}
	case 25: // ClusterIDSet ���������� ����� �������� �������
		ClusterID = Load.ToInt();
		break;
	case 26: // ClusterCenterOut ������ ���������� �������
		if(Clusters.size() && ClusterID>=0 && ClusterID<Clusters.size())
				Load.Write(Clusters[ClusterID].Center);
		break;
	case 27: // ClusterCenterOutMk ������ �� � ������������ ������� (���� ������ <0, �� �������� ���������� ���� ��������)
		if (Clusters.size())
			if(ClusterID >= 0 && ClusterID < Clusters.size())
				MkExec(Load, {CdoubleArray, &Clusters[ClusterID].Center});
			else // ������ ��������� ������� ���� ��������
				for(auto &i:Clusters)
					MkExec(Load, { CdoubleArray, &i.Center });
		break;
	case 28: // ClusterNearestPointOut ������ ���������� �����, ��������� � ������ �������
		Load.Write(Clusters[ClusterID].CenterFU->Coodinate);
		break;
	case 29: // ClusterNearestPointOutMk ������ �� � ������������ �����, ��������� � ������ �������
		if(Clusters.size() > ClusterID && Clusters[ClusterID].CenterFU!=nullptr)
			MkExec(Load, { CdoubleArray, &Clusters[ClusterID].CenterFU->Coodinate });
		break;
	case 35: // MigrationHistoryOutMk ������ �� � �������� ����������� ������� (���� ������������� ������� < 0, �� ��������� ������� ����������� ���� ��������)
		if(Clusters.size())
			if(ClusterID>=0 && ClusterID<=Clusters.size())
				MkExec(Load, { CdoubleArray2,&Clusters[ClusterID].MigrationHistory });
			else
				for(auto &i:Clusters)
					MkExec(Load, { CdoubleArray2,&i.MigrationHistory });
		break;
	case 37: // ClusterNetSet  ���������� ����� ��������. ���������: ��� � ���� ���������� ������� �� ����� �� ����, ����������  ��������� �� ������� ���������, � ����� ������ ��������
	{
		if (!ClusterNetPhaze)
			ClusterNetParameters.clear();
		if (ClusterNetPhaze < 3 * NDim)
			ClusterNetParameters.push_back(Load.ToDouble());
		else // ���������� ����� ��������
		{
			Clusters.clear();
			int NPoints = 1;
			for (int i = 2; i < NDim * 3; i+=3)
				NPoints *= round(ClusterNetParameters[i]); // ������� ���������� ����� � ����� ��������
			Clusters.resize(NPoints);
			// �������� ��� 2-������� ������
			for (int i = 0; i < round(ClusterNetParameters[2]); i ++) // ������ ���������
				for (int j = 0; j < round(ClusterNetParameters[5]); j ++) // ������ ���������
				{
					MeanShiftCluster* Reg = &Clusters[i * round(ClusterNetParameters[5]) + j];
					Reg->Eps=ClusterEps;
					Reg->NDim = NDim;
					Reg->R = Load.ToDouble();
					Reg->ID = i * ClusterNetParameters[5] + j;
					Reg->Center.clear();
					Reg->Center = { ClusterNetParameters[0] + (ClusterNetParameters[1] - ClusterNetParameters[0]) / (ClusterNetParameters[2]-1) * i,
									ClusterNetParameters[3] + (ClusterNetParameters[4] - ClusterNetParameters[3]) / (ClusterNetParameters[5]-1) * j };
					Reg->Manager = this;
					Reg->MoveToPoint(VXY[0][0]);
				}
		}
		ClusterNetPhaze = (ClusterNetPhaze + 1) % (3 * NDim + 1);
	}
		break;
	case 40: // PointsOutMk ������ ����� �������� ������������
	{
		
		for (auto& i : VXY[0])
		{
			MkExec(Load, { CdoubleArray,&i->Coodinate });
		}
		break;
	}
	case 50: //ArcsOutMk ������ ������ ���
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
	case 60: // NVPointErrProgSet ���������� ��������� ������� �� ������� ���������� ���������� ��������� ��� ����������� ����� ��� ����������� ����� � �������
		NVPointErrProg = Load.Point;
		break;
	case 71: // epsSet ���������� ���������� ������������� ����� �� ��� (�� ��������� 20)
		eps[EpsFaze] = Load.ToInt(20)/2;
		EpsFaze = (EpsFaze + 1) % NDim;
		break;
	case 72: // epsAllSet ���������� ���������� ���������� ������������� ����� ��� ���� ���� (�� ��������� 20)
	{	int t = Load.ToInt(20) / 2;
		for (auto& i : eps)
			i = t;
		break;
	}
	case 75: //ClusterEpsSet ��������� ����������� ��� ����������� �������� ��������
		ClusterEps = Load.ToDouble();
		break;
	case 80://NClusterPointCallOut ������ ���������� ������������ �� ����� �������� �������������� ��������� ��� ������ �������� �� ����� ��������
		if (ClusterID >= 0 && ClusterID <= Clusters.size())
			Load.Write(Clusters[ClusterID].NExUFCall);
		break;
	case 81://NClusterPointCallOut ������ �� � ����������� ������������ �� ����� �������� �������������� ��������� ��� ������ �������� �� ����� ��������
		if (ClusterID >= 0 && ClusterID <= Clusters.size())
			MkExec(Load, { Cint,&Clusters[ClusterID].NExUFCall });
		break;
	case 85: // NAllClusterPointCallOut ������ ������� ����������� ���������� ����� ������������ ��� ���� ���������
	case 86: // NAllClusterPointCallOutMk ������ �� � ������������ �������� �������� ���� ���������
	case 87: // NAveragePointCallOut  ������ ������� ���������� �������� �� ���� �������
	case 88: // NAveragePointCallOutMk ������ �� �� ������� ����������� �������� �� ���� �������
	{
		int t = 0;
		for (auto & i : Clusters)
			t += i.NExUFCall;
		if(MK==85)
			Load.Write(Clusters[ClusterID].NExUFCall);
		else if(MK==86)
			MkExec(Load, { Cint,&Clusters[ClusterID].NExUFCall });
		else
		{
			double tt = (double)t / Clusters.size();
			if (MK == 87)
				Load.Write(&tt);
			else
				MkExec(Load, { Cdouble,&tt });
		}
		break;
	}
		
	case 90: // NClusterMovesOut ������ ����������� �������� �������� �������� � �������� ClusterID �� ����� ��������
		if (ClusterID >= 0 && ClusterID <= Clusters.size())
			Load.Write(Clusters[ClusterID].MigrationHistory.size());
		break;
	case 91: // NClusterMovesOutMk ������ �� � ������������ �������� �������� �������� � �������� ClusterID �� ����� ��������
		if (ClusterID >= 0 && ClusterID <= Clusters.size())
		{
			int t = Clusters[ClusterID].MigrationHistory.size();
			MkExec(Load, { Cint,&t });
		}
		break;
	case 92: // NAllClusterMovesOut ������ ����� ����������� �������� �������� ���������
	case 93: // NAllClusterMovesOutMk ������ �� � ������ ������������ �������� �������� ��������� 
	case 94: // NAverageClusterMovesOut ������ ������� ����������� �������� �������� ��������
	case 95: // NAverageClusterMovesOutMk ������ �� �� ������� ������������ �������� �������� ��������
	{
		int t = 0;
		for (auto i : Clusters)
			t += i.MigrationHistory.size();
		if(MK==92)
			Load.Write(t);
		else if(MK==93)
			MkExec(Load, { Cint,&t });
		else
		{
			double tt = (double)t / Clusters.size();
			if (MK == 94)
				Load.Write(tt);
			else
				MkExec(Load, { Cdouble,&tt });
		}
		break;
	}
	case 120: // NClusterPointsOut ������ ���������� ����� � ��������
		if (ClusterID >= 0 && ClusterID <= Clusters.size())
			Load.Write(Clusters[ClusterID].NPoints);
		break;
	case 121: // NClusterPointsOut ������ �� � ����������� ����� � ��������
		if (ClusterID >= 0 && ClusterID <= Clusters.size())
			MkExec(Load, { Cint,&Clusters[ClusterID].NPoints});
		break;
	case 125: // ClusterMassOut ������ ����� ����� ����� � ��������
		if (ClusterID >= 0 && ClusterID <= Clusters.size())
			Load.Write(Clusters[ClusterID].Mass);
		break;
	case 126: // ClusterMassOut ������ �� ����� ������ ����� ��������
		if (ClusterID >= 0 && ClusterID <= Clusters.size())
			MkExec(Load, { Cdouble,&Clusters[ClusterID].Mass });
		break;
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
		{
			int i = 0;
			for (auto& uFU : k)
			{
				uFU->refXY.push_back(&uFU);
				uFU->IdXY.push_back(i); // ������ ������� �� �� ������� ���������
				i++;
			}
		}
	}

}

void MeanShift::FileRead(LoadPoint Load)
{
	ifstream f; // ���� ��� ���������� �������� ������
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
	//	MP->epsX[0] = epsX;
	//	MP->epsY[0] = epsY;
		MP->NV = NV;
		MP->Manager = this;
		MP->Coodinate.push_back(x);
		MP->Coodinate.push_back(y);
	//	MP->VX = &VX; // ������ �� ������ ������������� ������ �� ���������� X
	//	MP->VY = &VY; // ������ �� ������ ������������� ������ �� ���������� Y
	}
	// �������������� �������� VXt, VYt
	sort(VXt.begin(), VXt.end());
	sort(VYt.begin(), VYt.end());
	// ������������ �������� VX, VY
	for (auto uk = VXt.begin(); uk != VXt.end(); uk++)
		VXY[0].push_back(uk->second);
	for (auto uk = VYt.begin(); uk != VYt.end(); uk++)
		VXY[1].push_back(uk->second);

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
		FUuk->ProgFU(100, { 0,nullptr });// ������������ ��������� ����������� �����
	for (auto FUuk : VXY[0])
		FUuk->ProgFU(101, { 0,nullptr });// ������������ ���������� ������
//	for (auto FUuk : VXY[0])
//		FUuk->ProgFU(102, { 0,nullptr });// ������������ ��������� ������ �����
}