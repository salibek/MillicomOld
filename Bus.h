// �� ����
#pragma once
#include "FUini.h"
#include <vector>

const int NFUTypes = 18;

typedef FU*(*FUiniArr[NFUTypes])(FU*, FU*);

class BusFU : public FU {
public:
	BusFU(FU *BusContext, FU *Templ) : FU(BusContext) { Bus = BusContext; FUTypesIni();};
	BusFU() : FU() { Bus = this; FUTypesIni(); };
	void ProgFU(int MK, LoadPoint Load) override;
	FU* (*FUTypes[NFUTypes])(FU*, FU*) = {BusIni, ConsIni, StrGenIni, LexIni, FindIni, 
		ListIni, GraphTrasfIni, ThreaderIni, InOutIni, AutomatManagerIni, NeuroIni,
		NetManagerIni,SchedulerIni,EventserIni, MeanShiftIni, BagIni, GaussIni, ALUIni};
	vector <FU *> FUs; // ������ ���������� �� ��������� ��
	FU * FUTempl = nullptr; // ��������� �� �������� ������� ��
	int FUMkRange = 1000; // �������� �� ��� ������� ��
	int FUTypeCorrect; // ��������� ������ ���� �� (��� ������������ �� ������ ��-������)
private:
	void FUTypesIni();
};