#include "stdafx.h"
#include "MeanShift.h"
#include <string>
#include <fstream>
#include <set>
#include <algorithm>

void MeanShiftPoint::ProgFU(int MK, LoadPoint Load)
{
	switch (MK)
	{
	case 1: // Gen
		// Подбор точек, находящихся в области вокруг данной точки
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
		// Непосредственно генерация сетки

		break;
	}
}

void MeanShift::ProgFU(int MK, LoadPoint Load)
{
	switch (MK)
	{
	case 0: // Reset
		break;
	case 5: // Start
		//...
		NetGen(Load);
		break;
	case 8: // NVSet
		NV = Load.ToInt();
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

void  MeanShift::NetGen(LoadPoint Load)
{
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
	}
	// Упорядочивание векторов VXt, VYt
	sort(VXt.begin(), VXt.end());
	sort(VYt.begin(), VYt.end());
	// Формирование векторов VX, VY
	for (auto uk = VXt.begin(); uk != VXt.end(); uk++)
		VX.push_back(uk->second);
	for (auto uk = VYt.begin(); uk != VYt.end(); uk++)
		VY.push_back(uk->second);
	VYt.clear();
	VYt.clear();

	// Расстановка ссылок в точках на их описание в VX,VY
	for (auto uk = VX.begin(); uk != VX.end(); uk++)
	{
		(*uk)->vx = uk;
	}
	cout << endl;
	for (auto uk = VY.begin(); uk != VY.end(); uk++)
	{
		(*uk)->vy = uk;
	}
	// Генерация сетки
	for (auto uk = VX.begin(); uk != VX.end(); uk++)
		(*uk)->ProgFU(1, { 0,nullptr });
}
