#pragma once
#include "Consts.h"
#include "LocationTable.h"
#include "Search.h"
#include "Navigator.h"

class GraphTransf : public FU
{
private:
	LocatTable *LTable; // ������� �������������� �������
	deletedIC delIC; //����� ��������� ��
	Search Searcher;  //���������
	Navigator navigator; //�������
	void ProgFU(int MK, LoadPoint Load) override;
	vector<vector<ip>*> Accum; // ����������� ��� �������� (������ �������)
public:
	GraphTransf(FU *BusContext, FU *Templ) : FU(BusContext) { 
		Bus = BusContext; 
		LTable = new LocatTable(); 
		navigator.currentPos = new vector<Position>(); 
		ProgFU(0, { 0,nullptr }); 
	};
	GraphTransf() : FU() {
		Bus = nullptr; 
	};
};