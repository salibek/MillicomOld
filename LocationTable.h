// ������� ����������� �������
#pragma once
#include "Consts.h"
class LocatTable
{
private:
	vector<vector<void*>>* Table; // ������� ������������ �������
	int ind = -1; // ������ ������ � ������� ������� (��� -1 ������������ ������� ��������)
	vector<int> indVect; // ������ ������ � ������� �������
	void *HostPoint = nullptr; // ����� ��� ���������
public:
	LocatTable(); // ����������� ������, ���������� ��� �������� ������� �������
	void HostPointSet(void* Point) { HostPoint=Point;}; // ���������� �������� � ����� ��� ���������
	void* EqLoacat(void* Point, int index=-1); // ���������� �����, ��������������� �������������, index - ������ ��������� � ������, ��� index<0 ������������ ���� ������ ind
	int Index(void* Point); // ������������ ������ ���������� ��������� (���� ��������� �� ������, ������������ -1)
	void AddLine(void* Point); // ��������� ����� ����� � ������� ������������ ������� � ���������� � ��� �����
	void AddToLastLine(void* Point); // ��������� ����� � ��������� ����� ������� ������������ �������
	bool AddPoint(void* Point, void* HostPoint); // ������ ����� � ������� HostPoint � � ��� ����������� ����� Point
	void AddPointToHost(void* Point) { AddPoint(Point, HostPoint); }; // ������ ����� � ������� HostPoint (���� ������) � � ��� ����������� ����� Point
	void Clear(); // ����� ��������� ������� ����������� �������
	void TableClear(); // ������� ������� ����������� �������
	vector<void*>* GetRow(void* Point);

	bool Empty(); // �������� �� ������� �������
	int LineCount(); // ���������� ���������� ����� � �������
	void DelLastLine(int Count=1); // ������� Count ��������� ����� ������� 
	bool DelLineWithPoint(void* Point); // �������� ������, � ������� ������� ����� Point, ���������� true, ���� �������� ����������
	bool DelCopy(void* Point); //�������� ����� (������� ������, � ������� ������� ����� �����)
};