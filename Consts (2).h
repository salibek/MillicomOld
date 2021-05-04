// �������� �������� �������� � �������������� �����������
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>

using namespace std; 

// ���� ����������
const int Tvoid = 0, Tint = 2, Tfloat = 4, Tdouble = 6, Tchar = 8, Tstring = 10, TIP = 12, Tbool = 14, TIC = 16;
const int TPPoint = 18, TGraph=20, TFU=22;
// ���� ��������
const int Cvoid = 1, Cint = 3, Cfloat = 5, Cdouble = 7, Cchar = 9, Cstring = 11, CIP = 13, Cbool = 15, CIC = 17;
const int CPPoint = 19, CGraph = 21, CFU = 23;
// ����� ���� ������ (������� �� �������������� ������� �� 2 ���� ���������� ��� ���������)
const int Dvoid=0, Dint = 1, Dfloat = 2, Ddouble = 3, Dchar = 4, Dstring = 5, DIP = 6, Dbool = 7, DIC = 8;
const int DPPoint = 9, DGraph = 10, DFU = 11;

// ���� ��
const int FUBus = 0, FUCons = 1, FUStrGen = 2, FULex = 3, FUList = 4, FUFind = 5;

// ���� �����
const vector<int> w_type = { 10, 30, 40, 50, 60, 70, 20 };

// ����� ��������
const int ProgAtr = -100, Atr=-60;

bool isIPinIC(void* iP, void* iC); //��������, ��� �� ������ � ��

class LoadPoint
{
public:
	unsigned int Type = 0; // ����������� ���
	void *Point;
	bool IsConvert(unsigned int T) {}; // ���� �� ����������� ����������� �������� �� Point � ������������ ���
	int ToInt() {return Point==nullptr? 0 :  *(int*)Point; }; // ������� � integer
	double ToDouble() {
		switch (Type>>1)
		{
		case Ddouble: return *(double*)Point; break;
		case Dfloat: return *(float*)Point; break;
		case Dint: return *(int*)Point; break;
		case Dbool: return *(bool*)Point; break;
		default:
			return 0;
			break;
		}
	}; // ������� � integer
	bool ToBool() { return Point == nullptr ? 0 : *(bool*)Point; }; // ������� � integer
	char ToChar() { return Point == nullptr ? 0 : *(char*)Point; }; // ������� � integer
	string ToStr() { return Point == nullptr ? "" : *(string*)Point; }; // ������� � integer
	void Copy(LoadPoint *LP);
	void Clear(); // ����� �������� ��
	void VarClear(); // ����� �������� �� � ��� ����� � � ���������� (���������� ���������)
	void print(void* AtrMnemo=nullptr, string offset=""); // �������� - ��������� �� ����. �������� ���������
	LoadPoint Clone(); // ����������� ��������
	void ConstTypeSet(bool F = true) { if (F)Type |= 1; else VarTypeSet(); }; // ���������� ��� '���������'
    // ���������� ��� '����������'
	void VarTypeSet(bool F = true) {
		if (!F) { ConstTypeSet(); return; } Type |= 1; if (Type >= 0)Type -= 1; else Type += 1;}
	LoadPoint IpOut() // ������������ ��������� �� �� ��� �� ������ �� �� ��, ����� null
	{
		if (Type >> 1 == DIP) return *this;
//		if (Type >> 1 == DIC) return { DIP,((IC_type)Point)->begin()._Ptr};
//		return { 0,nullptr };
	};
	bool IpTest() { return (Type >> 1 == DIP || Type >> 1 == DIC); } // �������� �� �������� ��?

};

// struct TAtrMnrmo

class ip // �������������� ����
{
public:
	int atr = 0;
	LoadPoint Load = {0, nullptr }; // ��������� �� �������� � ����� �������
	~ip() { }//Load.Clear(); };
	void copy(ip *IP)// ����������� ��
	{
		atr = IP->atr;
		Load.Point = IP->Load.Point;
		Load.Type = IP->Load.Type;
	};
	void copy(void *IP) { copy(*(ip*)IP); }// ����������� ��
	void copy(ip &IP)// ����������� ��
	{
		atr = IP.atr;
		Load.Copy(&IP.Load);
	};
	void copy(LoadPoint &LP)// ����������� ��
	{
		switch (LP.Type >> 1)
		{
		case DIP:
			atr = ((ip*)LP.Point)->atr;
			Load.Copy(&((ip*)LP.Point)->Load);
			break;
		case DIC:
			atr = ((vector<ip>*)LP.Point)->begin()->atr;
			Load.Copy(&((vector<ip>*)LP.Point)->begin()->Load);
		}
	};
	ip* �lone()
	{
		ip* ip_new = new ip;
		ip_new->copy(*this);
		return ip_new;
	}

};

typedef  vector<vector<ip>*> ICVect;
typedef  vector<ip>* IC_type;

struct deletedIC //��������� ��
{
	vector<ip*>* IC; // �������������� �������, ���������� ��������� ��
	void* programm; // ��������� �� ������������� (��, ���������� ����� �����������)
};

class FUModeling
{
public:
	vector<ip> qmk; // ������� �� ��� �������������
	bool ManualMode = false; // ����� ������� ���������� (��� �������������)
	map<int, double> MkTime; // ����� ���������� �������� (��� �������������)
//	int CoreFreeMK; // �� ������������ ���� ��� ������������ ����������
	void* scheduler = nullptr; // ��������� �� �������� ������������ ����������
//	double Dtime = 0; // ����� ���������� ������� �������
};

class FU {  // ���� ��������������� ����������
public:
	virtual void ProgFU(int MK, LoadPoint Load) {}; // ���������� ������ ������ ��
	bool Active = true;

	FUModeling Modeling; // �������������

	FU() { Bus = nullptr; };
	FU(FU *BusContext) { Bus = BusContext; };
//	FU* Scheduler = nullptr; // �������� ������������ ����������

	void MkExec(int MK, LoadPoint Load, FU* BusContext = nullptr); // ��������� ���� ������������ 
	void MkExec(LoadPoint MK, LoadPoint Load, FU* BusContext); // ������ �� � ���������
    void ProgExec(void *Uk, FU* Bus=nullptr, vector<ip>::iterator *Start=nullptr); // ���������� ��������� �� ��

	FU *Bus; // ������ �� �������� ����
	int FUMkRange = 1000; // �������� �� ��� ������� ��
	bool ProgStop = false; // ���� ��������� ���������, ����������� ProgExec

	void CommonMk(int Mk, LoadPoint Uk); // ���������� ����� �� ��� ��
	IC_type PrefixProg = nullptr, PostfixProg = nullptr, Prog=nullptr; // ��������� ���������� � ������������ �� ����� ������� ��, ������ ���������
};

void ICDel(void* Uk);// �������� ��

void* ICCopy(LoadPoint uk);// ����������� ��

//void ProgExec(void *Uk, FU* Bus, vector<ip>::iterator *Start=nullptr); // ���������� ��������� �� ��

bool LoadCmp(LoadPoint x, LoadPoint y); // ��������� ���� �������� ��
bool IPCmp(ip* x, ip* y); // ��������� ����  ��
void AtrProgExec(vector<ip>* Prog, int Atr, FU* Bus=nullptr, bool AfterContinue = false); // ����� � �� �� � ��������� Atr � ��������� ��������� ���� �� ���. � ��������, ���� ����� ��������� ��
//void AddOrReplIPAtr(vector<ip>* UK, ip* IP); // 
ip* AtrFind(void* IC, int Atr); // ����� � �� �� � �������� ���������. �� ������ ��������� �� �� ��� NULLL
