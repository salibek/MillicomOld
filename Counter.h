#pragma once
#include "Consts.h"

class Counter : public FU {
private:
	int Accum = 0; // �����������
	int *AccumUk = &Accum; // ��������� �� �����������
	vector <int> Stack; // ���� �������������
	int AutoInc = 0; // ��� ������������� �������������
	int Compare = 0; // ������������� ��������
	int* CompareUk = &Compare; // ��������� �� ������������ ��������
	void* EmptyStackErrProg = nullptr; // ��������� ��������� ������ pop �� ������� �����
	void* BiggerProg=nullptr, * LessProg = nullptr, * EQProg = nullptr, * NEQProg = nullptr, * BiggerEQProg = nullptr, * LessEQProg = nullptr;
public:
	void ProgFU(int MK, LoadPoint Load);
	Counter(FU* BusContext, FU* Templ) : FU(BusContext) { ProgFU(0, { 0, nullptr }); Bus = BusContext; };
	Counter() : FU() { Counter(nullptr, nullptr); };
};