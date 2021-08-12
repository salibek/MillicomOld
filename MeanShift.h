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
	vector<MeanShiftPoint*>* VX, * VY; // ”казатели на точки, упор€доченные по координате X и Y
	vector<MeanShiftPoint*>::iterator vx, vy; //указатели на описание ‘” в векторах VX, VY
	vector<double> Coodinate; // ???
	int NV=0; //  оличество точек в множестве близлажищих точек?
	void* Manager; // ”казатель на менеджера
	vector<MeanShiftPoint*> NN;
	map<double,MeanShiftPoint*> N; // ћножество близлежащих точек (атрибут - рассто€ние до точки)
	map<double, MeanShiftPoint*> N_Alph; // Ѕлизлежащие точки в сетке, упор€доченные по углу от текущей точки
	double Lmax = -1;
	int epsX, epsY; // »значальна€ ширина коридора дл€ выбора точек во множество близлежащих точек
	int epsX_t, epsY_t; // “екуща€ ширина коридора дл€ выбора точек во множество близлежащих точек
};

class MeanShift : public FU {
public:
	void ProgFU(int MK, LoadPoint Load) override;
	MeanShift(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; };
	MeanShift() : FU() { Bus = nullptr; };
private:
	vector<MeanShiftPoint*> VX, VY;
	int NV; //  оличество точек, необходимое дл€ начала генерации вычислительной сетки
	int epsX, epsY; //  оличество анализируемых точек по X и Y
	int epsX_t, epsY_t; // ‘актическое количество анализируемых точек по X и Y
	double ProbX1=0, ProbX2=1, ProbY1=0, ProbY2=1; //  оррдинаты углов пол€ дл€ генерации случайных точек фазового пространства
	int ProbN = 10; //  оличество генерируемых случайных точек
	int ProbFaze = 0; // ‘аза считывани€ параметров дл€ генерации множества случайных точек
	void  NetGen(); // √енераци€ сетки
	void FileRead(LoadPoint Load); // —читывание точек пространства из файла
	void PointsGen(); // √енеаци€ случайных точек пространства
};