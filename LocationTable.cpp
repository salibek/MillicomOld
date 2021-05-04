// ������� ����������� �������
#include "stdafx.h"
#include "LocationTable.h"

LocatTable::LocatTable() {  // ����������� ������, ���������� ��� �������� ������� �������
	ind = 0;
	Table = new vector<vector<void*>>();
}

vector<void*>* LocatTable::GetRow(void* Point)
{
	for (auto i = Table->begin(); i != Table->end(); i++) {
		for (auto j = i._Ptr->begin(); j != i._Ptr->end(); j++) {
			if (isIPinIC(Point, *j._Ptr))
				return i._Ptr;
		}
	}
	return nullptr;
}

void* LocatTable::EqLoacat(void* Point, int index) // ���������� �����, ��������������� �������������, index - ������ ��������� � ������, ��� index<0 ������������ ���� ������ ind
{
	int _index = (index < 0) ? ind : index;
	for (int _i = 0; _i < Table->size(); _i++) {
		if (Table->at(_i).at(_index) == Point)
			return Table->at(_i).at(1);
	}
	return nullptr;
}
int LocatTable::Index(void* Point) // ������������ ������ ���������� ��������� (���� ��������� �� ������, ������������ -1)
{
	for (int _i = 0; _i < Table->size(); _i++) {
		for (int _j = 0; _j < Table->at(_i).size(); _j++) {
			if (Table->at(_i).at(_j) == Point) return _j;
		}
	}
	return -1;
}
void LocatTable::AddLine(void* Point) // ��������� ����� ����� � ������� ������������ ������� � ���������� � ��� �����
{
	if (Table == nullptr) {
		Table = new vector<vector<void*>>();
	}
	vector<void*> _line;
	Table->push_back(_line);
	Table->back().push_back(Point);
	indVect.push_back(0);
}

void LocatTable::AddToLastLine(void* Point) // ��������� ����� � ��������� ����� ������� ������������ �������
{
	if (LineCount() > 0) {
		Table->back().push_back(Point);
	}
}

bool LocatTable::AddPoint(void* Point, void* HostPoint) // ������ ����� � ������� HostPoint � � ��� ����������� ����� Point
{
	for (int _i = 0; _i < Table->size(); _i++) {
		for (int _j = 0; _j < Table->at(_i).size(); _j++)
		if (Table->at(_i).at(_j) == HostPoint) {
			Table->at(_i).push_back(Point);
			return true;
		}
	}
	return false;
}

void LocatTable::Clear() // ����� ��������� �� ������� �������
{
	ind = 0;
	indVect.clear();
	Table = nullptr;
}

void LocatTable::TableClear() // �������� �������
{
	ind = 0;
	indVect.clear();
	Table->clear();
}


bool LocatTable::Empty() // �������� �� ������� �������
{
	return Table == nullptr || LineCount() == 0;
}
int  LocatTable::LineCount() // ���������� ���������� ����� � �������
{
	return Table->size();
}
void LocatTable::DelLastLine(int Count) // ������� Count ��������� ����� ������� 
{
	for (int _i = LineCount(), _j = 0; _j < Count; _i--, _j++) {
		Table[_i-1].clear();
		indVect[_i-1] = -1;
	}
}

bool LocatTable::DelLineWithPoint(void* Point) // �������� ������, � ������� ������� ����� Point, ���������� true, ���� �������� ����������
{
	for (int _i = 0; _i < LineCount(); _i++) {
		for (int _j = 0; _j < Table->at(_i).size(); _j++) {
			if (Table->at(_i).at(_j) == Point) {
				Table->at(_i).clear();
				indVect[_i] = -1;
				return true;
			}
		}
	}
	return false;
}

bool LocatTable::DelCopy(void* Point) //�������� ����� (������� ������, � ������� ������� ����� �����)
{
	for (int _i = 0; _i < Table->size(); _i++) {
		for (int _j = 0; _j < Table->at(_i).size(); _j++)
			if (Table->at(_i).at(_j) == Point) {
				delete Table->at(_i).at(_j);
				return true;
			}
	}
	return false;
}
