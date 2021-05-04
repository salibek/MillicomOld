#pragma once
#include "Consts.h"
#include <vector>

double LinF(double S, vector<double> Args); // ���������� �����������

double Porog(double S, vector<double> Args); // 1. x, ��� ������� ������� �� ����� ������� �������, 2. �������� �� ��������, 3. ����� ��������

class Neuro : public FU
{
private:
	vector<double> W;
	vector<double> X;
	vector<bool>XF;
	vector<int> MK_Out;
	double S = 0; // �������� ������
	double eps = 0; // �����������
	int FType = 0; // ������ ������� ���������
	//... ������ ������ �� ������� ���������
	vector<double> F_Arg;
	int Counter = 0;
	int WInd = 0, XInd = 0; // �������
	int WIndStep = 1, XIndStep = 1; // ��� ���������� �������� ���� � �������� �������

	double (*Activation[2])(double, vector<double>) = { LinF,Porog }; // ������ ������� ���������
	double delta = 0, Z=0, Y=0;
public:
	void ProgFU(int MK, LoadPoint Load) override;
	Neuro(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; ProgFU(0, { 0,nullptr }); };
	Neuro() : FU() { Bus = nullptr; };
private:
};