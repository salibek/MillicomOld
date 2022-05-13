#pragma once
#include <vector>
#include "Consts.h"
#include "ALU.h"

// ���������� ��������� ������� (���������� ��� ���������� �������� �������)
class CellularAutomat : public FU {
//private:
public:
	void ProgFU(int MK, LoadPoint Load) override;
	CellularAutomat(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; };
	CellularAutomat() : FU() { Bus = nullptr; };
	void* Manager = nullptr;// ������ �� ���������
	vector<CellularAutomat*> Neighbours;//������ �� �������
	vector<int> NeighboursMk;// �� ��� �������
	vector<double> Rez; //������ ����������� ����������
	vector<vector<LoadPoint>> Plys; // ������ ������� ������, ���������� �� �������
	vector<LoadPoint> parameters; // ������ ����������
//	vector<bool> parametersF; // ������ ������ ����������� ������� ����������
	vector<double> Vars; // ������ ��������� ���������� (������������ ��� �������� ������������� ������ ����������)
	bool AutoSend = false; // ���� �������������� ��������� ����������� ����������
	vector<bool> RezReady; // ���� ���������� ���������� (��� ������� ���� ��������)
	vector<vector<bool>> InComplectF; // ���� ����������� ���� ������� �����
	vector<int> InCounter; // ������� ���������� ����������� ������ (����� ���������� ���������� ������������)
	int PlyInd = -1; //������ ����
	int PlyCurrent = 0; //������ �������� ����
	int ParameterInd = -1;// ������ �������� ���������
	void* CalcProg = nullptr; // ��������� �� ���������, ��� ���������� ����������
	void* ReceiveProg = nullptr; // ��������� �� ���������, ����������� ��� ������� ��, ���� ��������� ����������, �� �� ��������� �������� �� 
	int Mode = 1; // ����� ������ �������� (0 - ���������, 1 - ������� �����)
	void* CollectorFU = nullptr; // �	������ �� �������� �� ��� ������ ����������
	int IndFuOffcet = 0; // �	�������� ������� �� (������ ����������� �� ��� �������� � � ���� ������������ ������ ����)
	int FUInd = 0; // ������ ��-��������
	int VarInd = -1; // ������ ���������� ��� ��������������� ��������� ����������
};

// �������� ����������� ���������� �������� (���������� ��� ���������� �������� �������)
class CellularAutomatManager : public FU {
	//private:
public:
	void ProgFU(int MK, LoadPoint Load) override;
	int NetType = 0;// ��� ���������� ����� 0 - �� ������, 1- ����������, 2 - �����������, 3 ��������������
	CellularAutomatManager(FU* BusContext, FU* Templ) : FU(BusContext) { Bus = BusContext; };
	CellularAutomatManager() : FU() { Bus = nullptr; };
	vector<CellularAutomat> Net; //������ �������� ���������
	vector<int> Dim; // ����������� ���� ��������� (���������� �� ��� ������� ���������)
	void* iniAutmataProg = nullptr; // ��������� ������������� ���������
};