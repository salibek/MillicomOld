#pragma once
#include <string>
#include <vector>
#include "Consts.h"

class ConfineSimple : public FU {
private:
	LoadPoint ini, step, end;
	double stepStatic = 0, endStatic = 0;
	bool Fpost = false;
	bool FStaic = false;
	double accum;
	string accumStr;
	vector<LoadPoint> accumVect;
	LoadPoint in, out;
public:
	void ProgFU(int MK, LoadPoint Load) override;
	ConfineSimple(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; };
	ConfineSimple() : FU() { Bus = nullptr; };

};