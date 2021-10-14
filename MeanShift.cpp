#include "stdafx.h"
#include "MeanShift.h"
#include <string>
#include <fstream>
#include <set>
#include <algorithm>
#include <stdio.h>

void MeanShiftPoint::ProgFU(int MK, LoadPoint Load) // Поведение точки фазового пространства
{
	switch (MK)
	{
	case 1: // Gen
		// Подбор точек, находящихся в области вокруг данной точки

		while (1)
		{
			//auto Xstart= 
		}

/*		auto ukXL = vx;
		auto ukXR = vx;
		auto ukYL = vy;
		auto ukYR = vy;
		do {
			ukXL -= (NV <= distance(VX->begin(), ukXL)) ? NV / 2 : distance(VX->begin(), ukXL);
			ukXR += (NV < distance(ukXR, VX->end())) ? NV / 2 : (distance(ukXR, VX->end()) - 1);
			ukYL -= (NV <= distance(VY->begin(), ukYL)) ? NV / 2 : distance(VY->begin(), ukYL);
			ukYR += (NV < distance(ukYR, VY->end())) ? NV / 2 : (distance(ukYR, VY->end()) - 1);
			//copy_if()
		} while (N.size() < NV);
		*/
		// Непосредственно генерация сетки

		break;
	}
}

void MeanShift::ProgFU(int MK, LoadPoint Load) // Поведение ФУ MeanShift
{
	switch (MK)
	{
	case 0: // Reset
		break;
	case 3: // NDimSet Установить количество измерений фазового пространства
		NDim = Load.ToInt();
		break;
	case 5: // Start
		//...
		if ((Load.Type >> 1) == Dstring)
			FileRead(Load);
		NetGen();
		break;
	case 8: // NVSet Установить требуемое количество близлежащих точек
		NV = Load.ToInt();
		break;
	case 15: // PointsGen Генерация случайных точек (праметры: верхний левый угол поля, правый нижний угол поля, количество точек)
	case 16: // PointsGenStart Генерация случайных точек (праметры: верхний левый угол поля, правый нижний угол поля, количество точек)
		if (ProbFaze == NDim + NDim)
		{
			NProb = Load.ToInt(); ProbFaze = 0; 
			NetGen(); // Начать генерацию сетки
			if (MK == 16)
				;// Start
			break;
		}
		if (ProbFaze % 2 == 0)
			ProbXY[ProbFaze / 2].first = Load.ToDouble();
		else
			ProbXY[ProbFaze / 2].second = Load.ToDouble();	
		break;
	case 30: //ArcsOutMk Выдать список дуг
	{
		set<pair<vector<double>, vector<double>>>ArksOut;// Список координат
		for (auto& i : VXY[0])
		{
			pair<vector<double>, vector<double>> p;
			for (auto j : i->N) {
				if (i->Coodinate < j->Coodinate)
				{
					p.first = i->Coodinate; p.second = i->Coodinate;
				}
				else
				{
					p.first = j->Coodinate; p.second = j->Coodinate;
				}
				ArksOut.insert(p);
			}
		}
		
		char cstr[100];
		for (auto &i : ArksOut)
		{
			sprintf_s(cstr,"%f %f\n", i.first, i.second);
			string str=cstr;
			MkExec(Load, { Cstring, &str });
		}
		break;
	}
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
}

void MeanShift::PointsGen()
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	vector < vector<pair<double, MeanShiftPoint*>>> VXYt;
	VXY.clear();
	VXY.resize(NDim);
	VXYt.resize(NDim);
	for (int i = 0; i < NProb; i++)
	{
		MeanShiftPoint* MP = new MeanShiftPoint();
		//for (auto& k : VXYt)
		for(int k=0;k<NDim;k++)
		{
			double xy = static_cast<double>(rand() * fraction * (ProbXY[k].second - ProbXY[k].first + 1) + ProbXY[k].first);
			MP->Coodinate.push_back(xy);
			VXYt[k].push_back({ xy, MP });
		}
		MP->epsX = epsX;
		MP->epsY = epsY;
		MP->NV = NV;
		MP->Manager = this;
		MP->VXY = &VXY; // Ссылка на список упорядоченных вершин по координатам
		MP->NDim = NDim;
	}
	auto kVXY = VXY.begin();
	for (auto& k : VXYt) {
		sort(k.begin(), k.end());
		for (auto uk = k.begin(); uk != k.end(); uk++, kVXY++)
			kVXY->push_back(uk->second);
	}
}

void MeanShift::FileRead(LoadPoint Load)
{
/*	ifstream f; // файл для считывания исходных данных
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
		MP->VX = &VX; // Ссылка на список упорядоченных вершин по координате X
		MP->VY = &VY; // Ссылка на список упорядоченных вершин по координате Y
	}
	// Упорядочивание векторов VXt, VYt
	sort(VXt.begin(), VXt.end());
	sort(VYt.begin(), VYt.end());
	// Формирование векторов VX, VY
	for (auto uk = VXt.begin(); uk != VXt.end(); uk++)
		VX.push_back(uk->second);
	for (auto uk = VYt.begin(); uk != VYt.end(); uk++)
		VY.push_back(uk->second);
*/
}

void  MeanShift::NetGen()
{
	// Расстановка ссылок в точках на их описание в VX,VY

	for (auto &k : VXY) {
		{int i = 0;
			for (auto uk=k.begin(); uk!=k.end();uk++)
			{
			((*uk)->vxy).push_back(k.begin()+i); // Установить указатель на описание точки в VX
			i++;
			}
		}
	}
}
