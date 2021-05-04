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
	vector<MeanShiftPoint*>::iterator vx, vy; //��������� �� �������� �� � �������� VX, VY
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
	ifstream f; // ���� ��� ���������� �������� ������
	vector<MeanShiftPoint*> VX, VY;
	void  NetGen(LoadPoint Load);
	int NV; // ���������� �����, ����������� ��� ������ ��������� �������������� �����
	int epsX, epsY; // ���������� ������������� ����� �� X � Y
	int epsX_t, epsY_t; // ����������� ���������� ������������� ����� �� X � Y 
};