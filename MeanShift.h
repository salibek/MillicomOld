#pragma once
#include "Consts.h"
#include <vector>
#include <map>
#include <fstream>

class MeanShiftPoint : public FU {
public:
	void ProgFU(int MK, LoadPoint Load) override;
	int ID = 0; // ������������� ��-�����������
	int NDim = 2; // ���������� ��������� � ������� ������������
	MeanShiftPoint(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; };
	MeanShiftPoint() : FU() { Bus = nullptr; };
	vector<double> Coodinate; // ���������� ����� � ������� �����������
	int NV; // ���������� ����� � ��������� ����������� �����?
	void* Manager = nullptr; // ��������� �� ���������
	vector<int> eps; // ����������� ������ �������� ��� ������ ����� �� ��������� ����������� �����
					 // � ��������� �������� ������� �� 2, �.�. ��������������� �������, ����� ���� ������� �������� � ���������
	vector<int> eps_t; // ������� ������ �������� ��� ������ ����� �� ��������� ����������� �����
					 // � ��������� �������� ������� �� 2, �.�. ��������������� �������, ����� ���� ������� �������� � ���������
	vector<MeanShiftPoint**>refXY; // ��������� �� �������� ������ �� �� � �������� �������������� ������ �� ����
	vector<MeanShiftPoint*> N; // ��������� ����������� �����
	vector<int> IdXY; // ������� ��-����������� �� ���� ���� ���������
private:
//	vector < vector<MeanShiftPoint*>>* VXY; // ��������� �� �����, ������������� �� ���������� X � Y
//											// ������ ��������� - ��� ��������� ����� � �������
//	vector<vector<MeanShiftPoint*>::iterator> vxy;  //��������� �� �������� �� � �������� VX, VY  
//													// ������ ��������� - ��� ��������� ����� � �������
	multimap <double,MeanShiftPoint*> Nd; // ��������� ����������� ����� (������� - ���������� �� �����)
	multimap <double, MeanShiftPoint*> N_Alph; // ����������� ����� � �����, ������������� �� ���� �� ������� �����
	double Lmax = -1;
	double  dist(vector<double>& a, vector<double>& b); // ���������� ���������� ����� ����� �������
};

class MeanShift : public FU {
public:
	vector <vector<MeanShiftPoint*>> VXY; // ��������� �� �����, ������������� �� ���������� X � Y � �.�.
											// ������ ��������� - ��� ��������� ����� � �������
	void ProgFU(int MK, LoadPoint Load) override;
	MeanShift(FU* BusContext, FU* Templ) : FU(BusContext) { ProbMaxMin = { {0,1},{0,1} }; eps = { 15,15 }; eps.resize(2);  Bus = BusContext; };
	MeanShift() : FU() { ProbMaxMin = { {0,1},{0,1} }; eps = { 16,16 }; Bus = nullptr; };
private:
	int NDim = 2; // ���������� ��������� � ������� ������������
	int NV=15; // ��������� ���������� ����������� ����� ��� ������ ���������� ��������� ����� ������ ����
	vector<int> eps; // ���������� ������������� ����� �� ����
	vector<vector<double>> ProbMaxMin; // ������������ � ����������� ���������� �� ���� ������������� ��� ��������� �������������� �����
	int NProb = 10; // ���������� ������������ ��������� �����
	int ProbFaze = 0, EpsFaze=0; // ���� ���������� ���������� ��� ��������� ��������� ��������� ����� � ���� ���������� ������������ ���������� ����� �� ���� ��� ���������� �������������� �����

//	vector<vector<MeanShiftPoint*>::iterator> vxy;  //��������� �� �������� �� � �������� VX, VY
													// ������ ��������� - ��� ��������� ����� � �������

	void* NVPointErrProg = nullptr;  // ������������ ������ ��������� �� ������ ��� ���������� ���������� ����� 
								 //� ������� ��� ����������� ��������� ����� ��� ���������� ����� 
	void  NetGen(); // ��������� �����
	void FileRead(LoadPoint Load); // ���������� ����� ������������ �� �����
	void PointsGen(); // �������� ��������� ����� ������������
	void Start(); // ������ �������������
};