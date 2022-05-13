// �� �������
#pragma once
#include "Consts.h"
#include <fstream>
#include <string>
#include <map>
class Console : public FU
{
private:
	map<int, string> AtrMnemo; // �������� ��������
	string prefix;
	string filename = "";
	ofstream fout; // ??
	ofstream fin; // ??
	FILE* streamOut, *streamIn; // �������/�������� �����
	string Sep = " ", VectSep=",", End = "\n"; // ������-����������� � ������ � ����� ������
	string FloatPoint = "."; // ����������� ������� �����
	string ArrayBracketStart = "[", ArrayBracketFin = "]"; // ��������� � �������� ������ ��� ������ �������
	vector<LoadPoint>VarBuf; // ����� ����������
	vector<int>MkOutBuf; // ����� �� ��� ������ �����������
	LoadPoint NewVar; // ��������� �� ����� ����������
//	vector<LoadPoint> *NewVect; // ��������� �� ������
	void* NoVarToOutProg = nullptr; // ����������� ������� �� ������ "��� ���������� ��� ������"
	void* WrongFormatProg = nullptr; // ����������� ������� �� ������ "������������ ������"
	void* WrongVectFormatProg = nullptr; // ����������� ������� �� ������ "������������ ������"
public:
	void ProgFU(int MK, LoadPoint Load) override;
	Console(FU *BusContext, FU *Templ) : FU(BusContext) { Bus = BusContext; };
	Console() : FU() { Bus = nullptr; };
private:
};
