#pragma once
#include "Consts.h"
#include "Search.h"
class Search
{
public:
	vector<ip>*Template; // ������ ��� ������
	vector<ip>*Obj; //�� ��� ������
	FU Bus;
	bool Rez; // ��������� ������
	vector<ip> *SuccessProg = nullptr, *FailProg = nullptr; // ��������� �� ��������� �� ������ � �������� ������
	ip *IPTemplPoint = nullptr, *IPPoint = nullptr; // ��������� �� ��������� �� � ������� � � ��
	int SuccessProgAtr = -1; // ������� ���������, ������������� ��� �������� ������ (<0 ������� �� �����������)
	bool Search::FindOr(vector<ip> *obj); // �����
	bool Search::FindXor(vector<ip> *obj); // �����
	bool Search::FindAnd(vector<ip> *obj); // �����
};