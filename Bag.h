#pragma once
#include "Consts.h"
#include <fstream>
#include <vector>

class BagPoint : public FU {
public:
	void ProgFU(int MK, LoadPoint Load) override;
	BagPoint(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; };
	BagPoint() : FU() { Bus = nullptr; };
	double p = 0; // = max (p_Up, p_Diagonal)
	double p_Up = -1;
	double p_Diag = -1;

	double w_i = 0;   // ������� ����� ( = ������ ������� �������)
	double w_a = 0;   // ����� �������� w[i]

	// ������ �� ������� ������ � ������ �� ��������� � ������ ����. ����� �������� �������� p
	BagPoint* Down = nullptr;
	BagPoint* Diagonal = nullptr;
	BagPoint* Next = nullptr;

	double CalcTime = 0; // ����� ����������
	double SendTime = 0; // ����� ��������� ������
};

class Bag : public FU {
public:
	void ProgFU(int MK, LoadPoint Load) override;
	Bag(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; };
	Bag() : FU() { Bus = nullptr; };
private:
	vector< vector<BagPoint> > Field;
	int WMax = 0;			// ������ �������
	int NItem = 10; // ���������� ��������� ��� ������� � ������
	double  PMaxOfItem = 10; // ������������ ������ ����� ���� � �� ������������ ����
	int WMaxOfItem = 10; //  ������������ ���� ����
	vector<double> P;		// ������ ���������� ���������
	vector<int> W;			// ������ ������� ���������

	double CalcTime = 0;	// ����� ����������
	double SendTime = 0;	// ����� ��������� ������
};

