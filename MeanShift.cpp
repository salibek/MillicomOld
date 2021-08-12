#include "stdafx.h"
#include "MeanShift.h"
#include <string>
#include <fstream>
#include <set>
#include <algorithm>

void MeanShiftPoint::ProgFU(int MK, LoadPoint Load) // ѕоведение точки фазового пространства
{
	switch (MK)
	{
	case 1: // Gen
		// ѕодбор точек, наход€щихс€ в области вокруг данной точки
		auto ukXL = vx;
		auto ukXR = vx;
		auto ukYL = vy;
		auto ukYR = vy;
		do {
			ukXL -= (NV <= distance(VX->begin(), ukXL)) ? NV / 2 : distance(VX->begin(), ukXL);
			ukXR += (NV < distance(ukXR, VX->end())) ? NV / 2 : (distance(ukXR, VX->end()) - 1);
			ukYL -= (NV <= distance(VY->begin(), ukYL)) ? NV / 2 : distance(VY->begin(), ukYL);
			ukYR += (NV < distance(ukYR, VY->end())) ? NV / 2 : (distance(ukYR, VY->end()) - 1);
			//copy_if()
		} while (NN.size() < NV);
		// Ќепосредственно генераци€ сетки

		break;
	}
}

void MeanShift::ProgFU(int MK, LoadPoint Load) // ѕоведение ‘” MeanShift
{
	switch (MK)
	{
	case 0: // Reset
		break;
	case 5: // Start
		//...
		if((Load.Type>>1)==Dstring)
			FileRead(Load);
		NetGen();
		break;
	case 8: // NVSet ”становить требуемое количество близлежащих точек
		NV = Load.ToInt();
		break;
	case 15: // PointsGen √енераци€ случайных точек (праметры: верхний левый угол пол€, правый нижний угол пол€, количество точек)
	case 16: // PointsGenStart √енераци€ случайных точек (праметры: верхний левый угол пол€, правый нижний угол пол€, количество точек)
		switch (ProbFaze)
		{
		case 0: ProbX1 = Load.ToDouble(); ProbFaze =1; break;
		case 1: ProbY1 = Load.ToDouble(); ProbFaze =2; break;
		case 2: ProbX2 = Load.ToDouble(); ProbFaze =3; break;
		case 3: ProbY2 = Load.ToDouble(); ProbFaze =4; break;
		case 4: ProbN =  Load.ToInt();    ProbFaze =0; break;
		}
		if (ProbFaze == 0) {
			NetGen(); // Ќачать генерацию сетки
			if (MK == 16)
				;// Start				
		}
		break;
	case 51: // epsXSet
		epsX = Load.ToDouble();
		break;
	case 52: // epsYSet;
		epsY = Load.ToDouble();
		break;

	default:
		CommonMk(MK, Load);
		break;
	}
	//string str="sdgdfg.txt";
	//MeanShiftFU->ProgFU(5,{TString,&str});
}

void MeanShift::PointsGen()
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	vector<pair<double, MeanShiftPoint*>> VXt, VYt;
	double dX = ProbX2 - ProbX1;
	double dY = ProbY2 - ProbY1;
	for (int i = 0; i < ProbN; i++)
	{
		MeanShiftPoint* MP = new MeanShiftPoint();
		double x = static_cast<int>(rand() * fraction * (ProbX2 - ProbX1 + 1) + ProbX1);
		double y = static_cast<int>(rand() * fraction * (ProbY2 - ProbY1 + 1) + ProbY1);
		VXt.push_back({ x, MP });
		VYt.push_back({ y , MP });
		MP->epsX = epsX;
		MP->epsY = epsY;
		MP->NV = NV;
		MP->Manager = this;
		MP->Coodinate.push_back(x);
		MP->Coodinate.push_back(y);
		MP->VX = &VX; // —сылка на список упор€доченных вершин по координате X
		MP->VY = &VY; // —сылка на список упор€доченных вершин по координате Y
	}
	sort(VXt.begin(), VXt.end());
	sort(VYt.begin(), VYt.end());
	VX.clear();
	VX.clear();
	for (auto uk = VXt.begin(); uk != VXt.end(); uk++)
		VX.push_back(uk->second);
	for (auto uk = VYt.begin(); uk != VYt.end(); uk++)
		VY.push_back(uk->second);
}

void MeanShift::FileRead(LoadPoint Load)
{
	ifstream f; // файл дл€ считывани€ исходных данных
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
		MP->VX = &VX; // —сылка на список упор€доченных вершин по координате X
		MP->VY = &VY; // —сылка на список упор€доченных вершин по координате Y
	}
	// ”пор€дочивание векторов VXt, VYt
	sort(VXt.begin(), VXt.end());
	sort(VYt.begin(), VYt.end());
	// ‘ормирование векторов VX, VY
	for (auto uk = VXt.begin(); uk != VXt.end(); uk++)
		VX.push_back(uk->second);
	for (auto uk = VYt.begin(); uk != VYt.end(); uk++)
		VY.push_back(uk->second);
}

void  MeanShift::NetGen()
{
	// –асстановка ссылок в точках на их описание в VX,VY
	for (auto uk = VX.begin(); uk != VX.end(); uk++)
	{
		(*uk)->vx = uk;
	}
	cout << endl;
	for (auto uk = VY.begin(); uk != VY.end(); uk++)
	{
		(*uk)->vy = uk;
	}
	// √енераци€ сетки
	for (auto uk = VX.begin(); uk != VX.end(); uk++)
		(*uk)->ProgFU(1, { 0,nullptr });
}
