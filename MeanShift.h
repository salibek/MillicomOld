#pragma once
#include "Consts.h"
#include <vector>
#include <map>
#include <fstream>

class MeanShiftPoint : public FU {
public:
	void ProgFU(int MK, LoadPoint Load) override;
	int NDim = 2; //  оличество изменений в фазовом пространстве
	MeanShiftPoint(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; };
	MeanShiftPoint() : FU() { Bus = nullptr; };
//private:
	vector < vector<MeanShiftPoint*>>* VXY; // ”казатели на точки, упор€доченные по координате X и Y
											//  аждое изменение - это отдельна€ лини€ в векторе
	vector<vector<MeanShiftPoint*>::iterator> vxy;  //указатели на описание ‘” в векторах VX, VY
													//  аждое изменение - это отдельна€ лини€ в векторе
	vector<double> Coodinate; // координата точки в фазовом прострастве
	int NV=0; //  оличество точек в множестве близлажищих точек?
	void* Manager; // ”казатель на менеджера
	vector<MeanShiftPoint*> N;
	map<double,MeanShiftPoint*> Nd; // ћножество близлежащих точек (атрибут - рассто€ние до точки)
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
	int NDim = 2; //  оличество изменений в фазовом пространстве
	vector<vector<MeanShiftPoint*>> VXY;// ”казатели на точки, упор€доченные по координате X и Y
											//  аждое изменение - это отдельна€ лини€ в векторе
	int NV; //  оличество точек, необходимое дл€ начала генерации вычислительной сетки
	int epsX, epsY; //  оличество анализируемых точек по X и Y
	int epsX_t, epsY_t; // ‘актическое количество анализируемых точек по X и Y
	vector<pair<double, double>> ProbXY; //  оррдинаты углов пол€ дл€ генерации случайных точек фазового пространства
	int NProb = 10; //  оличество генерируемых случайных точек
	int ProbFaze = 0; // ‘аза считывани€ параметров дл€ генерации множества случайных точек
	void  NetGen(); // √енераци€ сетки
	void FileRead(LoadPoint Load); // —читывание точек пространства из файла
	void PointsGen(); // √енеаци€ случайных точек пространства
};