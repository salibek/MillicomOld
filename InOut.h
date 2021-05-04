#pragma once
#include "Consts.h"
#include <map>

class AutomatManager : public FU
{
private:
	bool TemplAutoClear = true; // ���� ��������������� ������ ������� ������ ��� ��������� �� ��� ���������� ������ �������
	int ReceiverMk = -1; // �� ��� �������� ��-���������
	void* Template = nullptr;// ������ �� ��������� �� ic *
	void* Var = nullptr; // ������ �� �� ���������� ic *
	ip IPout = { 0, {0,new double(0)} };// �� �������(������ � ��� �������) ip
	ip IPoutPrev = { 0, {0,new double(0)} };// �� ����������� �������(������ � ��� �������) ip
	map<int, void*> StageInProg; // ��������� �� ���������� �������� (������ ��������� �� �������� ��� receiver-�)
	map<int, void*> StageOutProg; // ��������� �� ���������� �������� (������ ��������� �� �������� ��� receiver-�)
	int StageProgMk = -1; // �� ��� ��������� ��������� ��� ���������
public:
	void ProgFU(int MK, LoadPoint Load) override;
	AutomatManager(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; ProgFU(0, { 0,0 }); };
	AutomatManager() : FU() { Bus = nullptr; };
};

class border
{
public:
	FU Parent = nullptr;
	bool Start = true; // ���� ���������� ���������
	double OldVal = 0;
	vector<double> borders;
	vector<void*> UpProg;
	vector<void*> DownProg;
	void Run(LoadPoint Load);
	void Reset() { Start = true; borders.clear(); UpProg.clear(); DownProg.clear(); };
	int* MK; // ������ �� �� ��� �����������
	border(FU Pr) { Parent = Pr; };
	border() { Parent = nullptr; };
};

class Channel
{
public:
	string Name; //��� ������
	int Ind = -1; // ������ ������
	int Mode = 0; // ����� ������ ��: 0 - ����, 1 - �����, 2 - ������� ...
	// ������� ������� �������������� �������???
	// �������� ������� �������������� �������???
	int Atr = 0, Mk = -1; // ������� � �� ��� ��������� �������
	double Tact = 0; // ������ ������
	double PrevSignal = 0, Signal = 0; // ���������� � ������� ������ (����� ������� ��������)
	double Sensit = 0; // ����������������
	border Border; // �������
	bool Active = true;
	ip OutIP;
	int* CurrentCh = nullptr;// ������ �� �����, � �������� ������ ������
	FU Parent=nullptr;
	Channel(FU Pr) { Parent = Pr;};
};

class InOut : public FU
{
private:
	string prefix;
	vector <Channel*> Channels; // ������ �������
	int Ind = -1; // ����� �������� ������
	int AutoInc = 0; // �������������
	int Nch = 0; // ���������� �������
public:
	int CurrentCh = -1; // ����� �������� ������ (�.�. ������, �� ������� ������ ������)
	void ProgFU(int MK, LoadPoint Load) override;
	InOut(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; ProgFU(0, { 0,0 }); };
	InOut() : FU() { Bus = nullptr; };
};