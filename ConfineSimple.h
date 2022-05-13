#pragma once
#include <string>
#include <vector>
#include "Consts.h"

class ConfineSimple : public FU {
private:
	LoadPoint ini, step, end;
	double accum=0;
	string accumStr;
	vector<LoadPoint> accumVect;
	LoadPoint in, out;
	void* ElseProg = nullptr; // ���������, ����������� ��� ��������������� ������ �� �����
//	FU* Parent = nullptr;// ������������ ��
public:
	double stepStatic = 0, endStatic = 0;
	bool Fpost = false;
	bool FStaic = false;
	void ProgFU(int MK, LoadPoint Load) override;
	ConfineSimple(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; };
	ConfineSimple() : FU() { Bus = nullptr; };
};