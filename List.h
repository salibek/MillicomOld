// �� ������
#pragma once
#include "Consts.h"
#include "Search.h"

class ListContext
{
public:
	vector<ip>* ListHead = nullptr; // ��������� �� ������ ������
	ip* LineUk = nullptr; // ��������� �� ��������� ������ ������
	int LineNum = -1, LineNumOld = -1; // ����� ������ ����������� �����, ����� ���������� ����������� �����
	int LineCount = 0; // ���������� ��������� �����
	bool StopSearch = false; // ���� ����������� ������ � ������� ��������
};

class List : public FU
{
public:
	void ProgFU(int MK, LoadPoint Load) override;
	vector<ListContext> Stack;
	int MultiLineMode = 0; // 0 - ����� ������ ������� ����������, 1 - ����� ���� ����������
	int MultiLavelSearch = 0; // ����� ������ �� ���������� ������� ������
	// 0 - �� ������� ������, 1 - �� ���� �������, 2- ������ � ������� ��������
	int ReceiverMk = 0; // �� ��� ���������� �������
	int* ReceiverMkUk = &ReceiverMk; // ��������� �� �� ��� ���������� �������
	// �������� � ��������
/*	vector<ip>* ListHead = nullptr; // ��������� �� ������ ������
	ip* LineUk=nullptr; // ��������� �� ��������� ������ ������
	int LineNum = -1, LineNumOld = -1; // ����� ������ ����������� �����, ����� ���������� ����������� �����
	int MultiLineMode = 0; // 0 - ����� ������ ������� ����������, 1 - ����� ���� ����������
	int ReceiverMk = 0; // �� ��� ���������� �������
	int *ReceiverMkUk = &ReceiverMk; // ��������� �� �� ��� ���������� �������
	int LineCount = 0; // ���������� ��������� �����
*/	// -----
	bool MultyLineMode = false, MultyListMode = false, BackSearchMode = false; //  ������ ������ ��������� �����, �������������� ������ � ������ � �������� �����������
	bool BackListSerch = false; // ����� ����� �� ������ (�� ��������)
	int LineAtr = SubObj; // ������� ����� ������
	set<int> SubListAtrs = { LineAtr };
	void* LessProg = nullptr, * BibberProg = nullptr, *EQProg = nullptr, *LessEQProg = nullptr, *BibberEQProg = nullptr;
	vector<int> LineStack; // ���� ������� �����
	Search Searcher; // ���������� ������
	void *FailLineProg = nullptr; // ���������, ����������� � ������ ���������� ������ � ������� ����� ������
	void *FailProg = nullptr; // ���������, ����������� � ������ ���������� ������ �� ����  ������
	void* Su��essLineProg = nullptr, * Su��essProg = nullptr;
	vector<ip> *DefProg = nullptr;

	List(FU *BusContext, FU *Templ) : FU(BusContext) { ProgFU(0, { 0, nullptr }); Bus = BusContext; Searcher.MainFU = this; };
	List() : FU() { List(nullptr, nullptr); };
private:
};