#pragma once
#include "Consts.h"
#include <vector>
#include <map>
#include <fstream>

class MeanShiftPoint : public FU {
public:
	void ProgFU(int MK, LoadPoint Load) override;
	MeanShiftPoint(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; };
	MeanShiftPoint() : FU() { Bus = nullptr; };
//private:
	vector<MeanShiftPoint*>* VX, * VY;
	vector<MeanShiftPoint*>::iterator vx, vy; //указатели на описание ФУ в векторах VX, VY
	vector<double> Coodinate;
	int NV=0;
	void* Manager;
	vector<MeanShiftPoint*> NN;
	map<double,MeanShiftPoint*> N;
	double Lmax = -1;
	int epsX, epsY;
	int epsX_t, epsY_t;
};

class MeanShift : public FU {
public:
	void ProgFU(int MK, LoadPoint Load) override;
	MeanShift(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; };
	MeanShift() : FU() { Bus = nullptr; };
private:
	ifstream f; // файл для считывания исходных данных
	vector<MeanShiftPoint*> VX, VY;
	void  NetGen(LoadPoint Load);
	int NV; // Количество точек, необходимое для начала генерации вычислительной сетки
	int epsX, epsY; // Количество анализируемых точек по X и Y
	int epsX_t, epsY_t; // Фактическое количество анализируемых точек по X и Y 
};