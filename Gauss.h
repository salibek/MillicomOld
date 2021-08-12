#pragma once
#include "Consts.h"
#include <fstream>
#include <vector>

class GaussPoint : public FU {
public:
	void ProgFU(int MK, LoadPoint Load) override;
	GaussPoint(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; };
	GaussPoint() : FU() { Bus = nullptr; };
	double a = 0;
	bool FreeF = false; //���� ���������� �����
	bool KeyF = false; // ���� �������� �� ������� ���������
	GaussPoint* Neighbours[4] = {nullptr, nullptr, nullptr, nullptr};

	double CalcTime = 0; // ����� ����������
	double SendTime = 0; // ����� ��������� ������

private:
	double UpBuf = 0;
	double S = 0;
};

class Gauss : public FU {
public:
	void ProgFU(int MK, LoadPoint Load) override;
	Gauss(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; };
	Gauss() : FU() { Bus = nullptr; };
	int Size = 10; // ����������� �������
	double Max = 10, Min = 10;// ������������ � ����������� �������� ������������� � ��������� ������
private:
		vector< vector<GaussPoint> > Field;
};

