#pragma once
#include "Consts.h"
#include <vector>
#include <map>
#include <fstream>

class MeanShiftPoint : public FU {
public:
	void ProgFU(int MK, LoadPoint Load) override;
	int NDim = 2; // ���������� ��������� � ������� ������������
	MeanShiftPoint(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; };
	MeanShiftPoint() : FU() { Bus = nullptr; };
//private:
	vector < vector<MeanShiftPoint*>>* VXY; // ��������� �� �����, ������������� �� ���������� X � Y
											// ������ ��������� - ��� ��������� ����� � �������
	vector<vector<MeanShiftPoint*>::iterator> vxy;  //��������� �� �������� �� � �������� VX, VY
													// ������ ��������� - ��� ��������� ����� � �������
	vector<double> Coodinate; // ���������� ����� � ������� �����������
	int NV=0; // ���������� ����� � ��������� ����������� �����?
	void* Manager; // ��������� �� ���������
	vector<MeanShiftPoint*> N;
	map<double,MeanShiftPoint*> Nd; // ��������� ����������� ����� (������� - ���������� �� �����)
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
	int NDim = 2; // ���������� ��������� � ������� ������������
	vector<vector<MeanShiftPoint*>> VXY;// ��������� �� �����, ������������� �� ���������� X � Y
											// ������ ��������� - ��� ��������� ����� � �������
	int NV; // ���������� �����, ����������� ��� ������ ��������� �������������� �����
	int epsX, epsY; // ���������� ������������� ����� �� X � Y
	int epsX_t, epsY_t; // ����������� ���������� ������������� ����� �� X � Y
	vector<pair<double, double>> ProbXY; // ���������� ����� ���� ��� ��������� ��������� ����� �������� ������������
	int NProb = 10; // ���������� ������������ ��������� �����
	int ProbFaze = 0; // ���� ���������� ���������� ��� ��������� ��������� ��������� �����
	void  NetGen(); // ��������� �����
	void FileRead(LoadPoint Load); // ���������� ����� ������������ �� �����
	void PointsGen(); // �������� ��������� ����� ������������
};