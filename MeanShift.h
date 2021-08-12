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
	vector<MeanShiftPoint*>* VX, * VY; // ��������� �� �����, ������������� �� ���������� X � Y
	vector<MeanShiftPoint*>::iterator vx, vy; //��������� �� �������� �� � �������� VX, VY
	vector<double> Coodinate; // ???
	int NV=0; // ���������� ����� � ��������� ����������� �����?
	void* Manager; // ��������� �� ���������
	vector<MeanShiftPoint*> NN;
	map<double,MeanShiftPoint*> N; // ��������� ����������� ����� (������� - ���������� �� �����)
	map<double, MeanShiftPoint*> N_Alph; // ����������� ����� � �����, ������������� �� ���� �� ������� �����
	double Lmax = -1;
	int epsX, epsY; // ����������� ������ �������� ��� ������ ����� �� ��������� ����������� �����
	int epsX_t, epsY_t; // ������� ������ �������� ��� ������ ����� �� ��������� ����������� �����
};

class MeanShift : public FU {
public:
	void ProgFU(int MK, LoadPoint Load) override;
	MeanShift(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; };
	MeanShift() : FU() { Bus = nullptr; };
private:
	vector<MeanShiftPoint*> VX, VY;
	int NV; // ���������� �����, ����������� ��� ������ ��������� �������������� �����
	int epsX, epsY; // ���������� ������������� ����� �� X � Y
	int epsX_t, epsY_t; // ����������� ���������� ������������� ����� �� X � Y
	double ProbX1=0, ProbX2=1, ProbY1=0, ProbY2=1; // ���������� ����� ���� ��� ��������� ��������� ����� �������� ������������
	int ProbN = 10; // ���������� ������������ ��������� �����
	int ProbFaze = 0; // ���� ���������� ���������� ��� ��������� ��������� ��������� �����
	void  NetGen(); // ��������� �����
	void FileRead(LoadPoint Load); // ���������� ����� ������������ �� �����
	void PointsGen(); // �������� ��������� ����� ������������
};