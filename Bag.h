#pragma once
#include "Consts.h"
#include <fstream>
#include <vector>

class BagPoint : public FU {
public:
	void ProgFU(int MK, LoadPoint Load) override;
	BagPoint(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; };
	BagPoint() : FU() { Bus = nullptr; };
	double p = 0; // = max (s_Up, s_Diagonal)
	double p_Up=-1;
	double p_Diag=-1;

	// —сылки на нижнего соседа и соседа по диагонали в нижнем р¤ду. ќбоим передаем значение s
	BagPoint* Down = nullptr;
	BagPoint* Diagonal = nullptr;
	BagPoint* Next = nullptr;
private:
//	const double p, w; // вес и стоимость предмета
};

class Bag : public FU {
public:
	void ProgFU(int MK, LoadPoint Load) override;
	Bag(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; };
	Bag() : FU() { Bus = nullptr; };
private:
	vector< vector<BagPoint> > Field;
	int WMax = 0;
	vector<double> P; // Вектор стоимостей предметов
	vector<int> W; // Вектор объемов предметов
};

