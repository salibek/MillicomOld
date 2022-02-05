// �� �������
#pragma once
#include "Consts.h"
#include <fstream>
class Console : public FU
{
private:
	string prefix;
	string filename = "";
	ofstream fout; // ??
	ofstream fin; // ??
	FILE* streamOut, *streamIn; // �������/�������� �����
	string Sep = " ", End = "\n"; // ������-����������� � ������ � ����� ������
	string ArrayBracketStart = "[", ArrayBracketFin = "]"; // ��������� � �������� ������ ��� ������ �������
	vector<LoadPoint>VarBuf; // ����� ����������
	vector<int>MkOutBuf; // ����� �� ��� ������ �����������
	LoadPoint NewVar; // ��������� �� ����� ����������
	vector<LoadPoint>NewVect; // ��������� �� ������
	void* NoVarToOutProg = nullptr; // ����������� ������� �� ������ "��� ���������� ��� ������"

public:
	void ProgFU(int MK, LoadPoint Load) override;
	Console(FU *BusContext, FU *Templ) : FU(BusContext) { Bus = BusContext; };
	Console() : FU() { Bus = nullptr; };
private:
};
